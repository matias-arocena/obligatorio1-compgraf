#include "Model.h"
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>


MeshEntry::MeshEntry()
{
    VertexBuffer = GL_INVALID_VALUE;
    IndexBuffer = GL_INVALID_VALUE;
    NumIndices = 0;
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
    rotation = 0.0;
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
    m_Entries.resize(pScene->mNumMeshes);
    
    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0; i < m_Entries.size(); i++) {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        InitMesh(i, paiMesh);
    }
}

void Model::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
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

    m_Entries[Index].Init(Vertices, Indices);
}


void Model::Render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    for (unsigned int i = 0; i < m_Entries.size(); i++) {
        glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IndexBuffer);

        if (onlyWireframe) {
            glDrawElements(GL_LINES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
        } else {
            glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
        }
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Model::showOnlyWireframe(bool onlyWireframe)
{
    this->onlyWireframe = onlyWireframe;
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
