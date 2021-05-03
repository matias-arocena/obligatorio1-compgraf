#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <math.h>
#include <vector>

Model::Model(bool flipNormals) : flipNormals{flipNormals}
{
    orientation = 0.0;
    hasTexture = false;

}

void Model::LoadMesh(const std::string& Filename)
{
    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(Filename.c_str(), 
        aiProcessPreset_TargetRealtime_Quality);
    
    if (pScene) {
        InitFromScene(pScene, Filename);   
    }
    else {
        printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
    }
}

void Model::InitFromScene(const aiScene* pScene, const std::string& filename)
{
     entries.resize(pScene->mNumMeshes);
     materials.resize(pScene->mNumMaterials);
    
    for (unsigned int i = 0; i < entries.size(); i++) {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        InitMesh(i, paiMesh);
    }

    InitMaterials(pScene, filename);
}

void Model::InitMesh(unsigned int index, const aiMesh* paiMesh)
{
    entries[index].materialIndex = paiMesh->mMaterialIndex;

    std::vector<float> pos;
    std::vector<float> normals; 
    std::vector<float> texCoord;
    std::vector<unsigned int> indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
        pos.push_back(paiMesh->mVertices[i][0]);
        pos.push_back(paiMesh->mVertices[i][1]);
        pos.push_back(paiMesh->mVertices[i][2]);

        if (flipNormals) {
            normals.push_back(paiMesh->mNormals[i][0] * -1);
            normals.push_back(paiMesh->mNormals[i][1] * -1);
            normals.push_back(paiMesh->mNormals[i][2] * -1);
        }
        else {
            normals.push_back(paiMesh->mNormals[i][0]);
            normals.push_back(paiMesh->mNormals[i][1]);
            normals.push_back(paiMesh->mNormals[i][2]);
        }

        if (paiMesh->HasTextureCoords(0)) {
            texCoord.push_back(paiMesh->mTextureCoords[0][i][0]);
            texCoord.push_back(paiMesh->mTextureCoords[0][i][1]);
        };
    }

    for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        indices.push_back(Face.mIndices[0]);
        indices.push_back(Face.mIndices[1]);
        indices.push_back(Face.mIndices[2]);
    }

    pos.shrink_to_fit();
    texCoord.shrink_to_fit();
    normals.shrink_to_fit();
    indices.shrink_to_fit();

    entries[index].pos = pos;
    entries[index].texCoord = texCoord;
    entries[index].normals = normals;
    entries[index].indices = indices;
}

void Model::Render()
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
            
            glEnable(GL_TEXTURE_2D);
            material.texture->Bind(GL_TEXTURE_2D);
            
            glDrawElements(GL_TRIANGLES, entries[i].indices.size(), GL_UNSIGNED_INT, entries[i].indices.data());
            
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


void Model::Rotate(double value)
{
    orientation = fmod(orientation + value, 360);
}

void Model::InitMaterials(const aiScene* pScene, const std::string& filename)
{
    std::string::size_type SlashIndex = filename.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos) {
        Dir = ".";
    }
    else if (SlashIndex == 0) {
        Dir = "/";
    }
    else {
        Dir = filename.substr(0, SlashIndex);
    }

    for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
        aiMaterial* mat = pScene->mMaterials[i];
        bool hasTexture = mat->GetTextureCount(aiTextureType_DIFFUSE);
        if (hasTexture) {
            aiString path;

            if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string FullPath = Dir + "/" + path.data;
                this->hasTexture = true;
                materials[i].hasTexture = true;
                materials[i].texture = new Texture(FullPath.c_str());

                if (!materials[i].texture->Load()) {
                    materials[i].texture = nullptr;
                }
            }
        }
        else {
            aiColor3D color(0.f, 0.f, 0.f);
            materials[i].hasTexture = false;
            mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
            materials[i].red = color.r;
            materials[i].green = color.g;
            materials[i].blue = color.b;

            mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
            materials[i].red += color.r;
            materials[i].green += color.g;
            materials[i].blue += color.b;

        }
    }
}
