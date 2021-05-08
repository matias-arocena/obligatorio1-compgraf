#include "Model.h"

#include "Game.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <cmath>
#include <vector>

Model::Model(bool flipNormals, bool showTexture) : flipNormals{ flipNormals }, showTexture {showTexture}
{
    orientation = 0.0;
    hasTexture = false;
    hitbox = nullptr;
}

void Model::loadMesh(const std::string& filename)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filename.c_str(),
        aiProcessPreset_TargetRealtime_Quality);

    if (scene) {
        initFromScene(scene, filename);
    }
}

void Model::initFromScene(const aiScene* scene, const std::string& filename)
{
    entries.resize(scene->mNumMeshes);
    materials.resize(scene->mNumMaterials);

    for (unsigned int i = 0; i < entries.size(); i++) {
        const aiMesh* mesh = scene->mMeshes[i];
        initMesh(i, mesh);
    }

    initMaterials(scene, filename);
}

void Model::initMesh(unsigned int index, const aiMesh* mesh)
{
    double xMin, xMax, yMin, yMax, zMin, zMax = 0;
    bool firstVertex = true;

    if (hitbox != nullptr) {
        firstVertex = false;
        xMin = hitbox->xMin;
        xMax = hitbox->xMax;
        yMin = hitbox->yMin;
        yMax = hitbox->yMax;
        zMin = hitbox->zMin;
        zMax = hitbox->zMax;
    }

    entries[index].materialIndex = mesh->mMaterialIndex;

    std::vector<float> pos;
    std::vector<float> normals;
    std::vector<float> texCoord;
    std::vector<unsigned int> indices;

    const aiVector3D zero(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        if (firstVertex) {
            xMin = xMax = mesh->mVertices[i][0];
            yMin = yMax = mesh->mVertices[i][1];
            zMin = zMax = mesh->mVertices[i][2];
            firstVertex = false;
        }
        else {
            xMax = mesh->mVertices[i][0] > xMax ? mesh->mVertices[i][0] : xMax;
            xMin = mesh->mVertices[i][0] < xMin ? mesh->mVertices[i][0] : xMin;
            yMax = mesh->mVertices[i][1] > yMax ? mesh->mVertices[i][1] : yMax;
            yMin = mesh->mVertices[i][1] < yMin ? mesh->mVertices[i][1] : yMin;
            zMax = mesh->mVertices[i][2] > zMax ? mesh->mVertices[i][2] : zMax;
            zMin = mesh->mVertices[i][2] < zMin ? mesh->mVertices[i][2] : zMin;

        }
        
        pos.push_back(mesh->mVertices[i][0]);
        pos.push_back(mesh->mVertices[i][1]);
        pos.push_back(mesh->mVertices[i][2]);

        if (flipNormals) {
            normals.push_back(mesh->mNormals[i][0] * -1);
            normals.push_back(mesh->mNormals[i][1] * -1);
            normals.push_back(mesh->mNormals[i][2] * -1);
        }
        else {
            normals.push_back(mesh->mNormals[i][0]);
            normals.push_back(mesh->mNormals[i][1]);
            normals.push_back(mesh->mNormals[i][2]);
        }

        if (mesh->HasTextureCoords(0)) {
            texCoord.push_back(mesh->mTextureCoords[0][i][0]);
            texCoord.push_back(mesh->mTextureCoords[0][i][1]);
        };
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        const aiFace& face = mesh->mFaces[i];
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }
    
    hitbox = new HitBox();
    hitbox->xMax = xMax;
    hitbox->xMin = xMin;
    hitbox->yMax = yMax;
    hitbox->yMin = yMin;
    hitbox->zMax = zMax;
    hitbox->zMin = zMin;

    pos.shrink_to_fit();
    texCoord.shrink_to_fit();
    normals.shrink_to_fit();
    indices.shrink_to_fit();

    entries[index].pos = pos;
    entries[index].texCoord = texCoord;
    entries[index].normals = normals;
    entries[index].indices = indices;
}

void Model::render()
{
    glPushMatrix();

    glRotatef(orientation, 0, 1, 0);

    for (unsigned int i = 0; i < entries.size(); i++) {

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(float) * 3, entries[i].pos.data());


        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(GL_FLOAT, sizeof(float) * 3, entries[i].normals.data());

        Material material = materials[entries[i].materialIndex];

        if (hasTexture && material.hasTexture) {
            glEnable(GL_COLOR_MATERIAL);
            glColor4f(1, 1, 1, 1);

            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2, GL_FLOAT, sizeof(float) * 2, entries[i].texCoord.data());

            if (showTexture)
                glEnable(GL_TEXTURE_2D);
    
            material.texture->bind();

            glDrawElements(GL_TRIANGLES, entries[i].indices.size(), GL_UNSIGNED_INT, entries[i].indices.data());

            if(showTexture)
                glDisable(GL_TEXTURE_2D);
    
            glDisable(GL_COLOR_MATERIAL);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        else if (!hasTexture) {
            glEnable(GL_COLOR_MATERIAL);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.f);

            glColor3f(material.red, material.green, material.blue);
            glDrawElements(GL_TRIANGLES, entries[i].indices.size(), GL_UNSIGNED_INT, entries[i].indices.data());
            glDisable(GL_COLOR_MATERIAL);
        }
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    glPopMatrix();
}

void Model::setShowTextrue(bool showTexture)
{
    this->showTexture = showTexture;
}

HitBox* Model::getHitBox()
{
    return hitbox;
}

Model::~Model()
{
    if (hasTexture) {
        for (auto& m : materials) {
            if(m.hasTexture) delete m.texture;
        }
    }
    delete hitbox;
} 


void Model::initMaterials(const aiScene* scene, const std::string& filename)
{
    std::string::size_type slashPos = filename.find_last_of("/");
    std::string Dir;

    if (slashPos == std::string::npos) {
        Dir = ".";
    }
    else if (slashPos == 0) {
        Dir = "/";
    }
    else {
        Dir = filename.substr(0, slashPos);
    }

    for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* material = scene->mMaterials[i];
        bool hasTexture = material->GetTextureCount(aiTextureType_DIFFUSE);
        if (hasTexture) {
            aiString path;

            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string FullPath = Dir + "/" + path.data;
                this->hasTexture = true;
                materials[i].hasTexture = true;
                materials[i].texture = new Texture(FullPath.c_str());

                if (!materials[i].texture->load()) {
                    materials[i].texture = nullptr;
                }
            }
        }
        else {
            aiColor3D color(0.f, 0.f, 0.f);
            materials[i].hasTexture = false;
            material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
            materials[i].red = color.r;
            materials[i].green = color.g;
            materials[i].blue = color.b;

            material->Get(AI_MATKEY_COLOR_AMBIENT, color);
            materials[i].red += color.r;
            materials[i].green += color.g;
            materials[i].blue += color.b;

        }
    }
}
