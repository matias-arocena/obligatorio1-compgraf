#include "Model.h"
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <math.h>

MeshEntry::MeshEntry()
{
    VertexBuffer = GL_INVALID_VALUE;
    IndexBuffer = GL_INVALID_VALUE;
    NumIndices = 0;
    materialIndex = GL_INVALID_VALUE;
};

MeshEntry::~MeshEntry()
{
    if (VertexBuffer != GL_INVALID_VALUE) {
        glDeleteBuffers(1, &VertexBuffer);
    }

    if (IndexBuffer != 0) {
        glDeleteBuffers(1, &IndexBuffer);
    }
}

void MeshEntry::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    NumIndices = static_cast<unsigned int>(indices.size());

    glGenBuffers(1, &VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &indices[0], GL_STATIC_DRAW);
}


Model::Model()
{
    orientation = 0.0;
    onlyWireframe = false;
}


void Model::LoadMesh(const std::string& Filename)
{
    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(Filename.c_str(), 
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);
    
    if (pScene) {
        InitFromScene(pScene, Filename);   
    }
    else {
        printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
    }
}

void Model::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
     entries.resize(pScene->mNumMeshes);
     materials.resize(pScene->mNumMaterials);
    
    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0; i < entries.size(); i++) {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        InitMesh(i, paiMesh);
    }

    InitMaterials(pScene);
}

void Model::InitMesh(unsigned int index, const aiMesh* paiMesh)
{
    entries[index].materialIndex = paiMesh->mMaterialIndex;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
        const aiVector3D* pPos = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal = &(paiMesh->mNormals[i]);

        Vertex v(pPos->x, pPos->y, pPos->z, pNormal->x, pNormal->y, pNormal->z);

        Vertices.push_back(v);
    }

    for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        Indices.push_back(Face.mIndices[0]);
        Indices.push_back(Face.mIndices[1]);
        Indices.push_back(Face.mIndices[2]);
    }

    entries[index].Init(Vertices, Indices);
}

void Model::InitMaterials(const aiScene* pScene)
{
    for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
        aiMaterial* mat = pScene->mMaterials[i];
        bool hasTexture = mat->GetTextureCount(aiTextureType_DIFFUSE);
        if (!hasTexture) {
            aiColor3D color(0.f, 0.f, 0.f);
            mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
            materials[i].hasTexture = false;
            materials[i].red = color.r;
            materials[i].green = color.g;
            materials[i].blue = color.b;
        }
    }
}


void Model::Render()
{
    glPushMatrix();
    
    glRotatef(orientation, 0, 1, 0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    for (unsigned int i = 0; i < entries.size(); i++) {
        glBindBuffer(GL_ARRAY_BUFFER, entries[i].VertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entries[i].IndexBuffer);
        Material material = materials[entries[i].materialIndex];

        if (onlyWireframe) {
            glColor3f(0.2, 0.2, 1);
            glDrawElements(GL_LINES, entries[i].NumIndices, GL_UNSIGNED_INT, 0);
        }
        else if (!material.hasTexture) {
            glEnable(GL_COLOR_MATERIAL);
            glMaterialf(GL_FRONT, GL_SHININESS, 128.f);

            glColor3f(material.red, material.green, material.blue);
            glDrawElements(GL_TRIANGLES, entries[i].NumIndices, GL_UNSIGNED_INT, 0);
            glDisable(GL_COLOR_MATERIAL);
        }
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glPopMatrix();
}

void Model::ShowOnlyWireframe(bool onlyWireframe)
{
    this->onlyWireframe = onlyWireframe;
}

void Model::Rotate(double value)
{
    orientation = fmod(orientation + value, 360);
}

Vertex::Vertex(const float posX, const float posY, const float posZ, const float normalX, const float normalY, const float normalZ)
{
    this->posX = posX;
    this->posY = posY;
    this->posZ = posZ;
    this->normalX = normalX;
    this->normalY = normalY;
    this->normalZ = normalZ;
}
