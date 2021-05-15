#include "GameObject.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "Game.h"
#include <iostream>

GameObject::~GameObject()
{
    if (hasModel) {
        if (hasTexture) {
            for (auto& m : materials) {
                if (m.hasTexture) delete m.texture;
            }
        }
        delete hitbox;
    }
}

void GameObject::update()
{
    vel += accel * Game::inst().getDeltaTime();
    pos += vel * Game::inst().getDeltaTime();
}

void GameObject::render()
{
    if (hasModel) {
        glPushMatrix();

        if(showHitbox)
            drawHitbox();

        glScalef(scale.x, scale.y, scale.z);
        glRotatef(rot.y, 0, 1, 0);

        
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
                else
                    glColor4f(0.7, 0.7, 0.7, 1);

                material.texture->bind();

                glDrawElements(GL_TRIANGLES, entries[i].indices.size(), GL_UNSIGNED_INT, entries[i].indices.data());

                if (showTexture)
                    glDisable(GL_TEXTURE_2D);

                glDisable(GL_COLOR_MATERIAL);
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            else if (!hasTexture) {
                
                if (showTexture) {
                    glEnable(GL_COLOR_MATERIAL);
                    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.f);
                    glColor3f(material.red, material.green, material.blue);
                }
                else {
                    glColor4f(0.7, 0.7, 0.7, 1);
                }
    
                glDrawElements(GL_TRIANGLES, entries[i].indices.size(), GL_UNSIGNED_INT, entries[i].indices.data());
                
                if(showTexture) 
                    glDisable(GL_COLOR_MATERIAL);
            }
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
        }

        glPopMatrix();
    }
}

void GameObject::initFromScene(const aiScene* scene, const std::string& filename)
{
    entries.resize(scene->mNumMeshes);
    materials.resize(scene->mNumMaterials);

    for (unsigned int i = 0; i < entries.size(); i++) {
        const aiMesh* mesh = scene->mMeshes[i];
        initMesh(i, mesh);
    }

    initMaterials(scene, filename);
}

void GameObject::initMesh(unsigned int index, const aiMesh* mesh)
{
    double xMin, xMax, yMin, yMax, zMin, zMax;
    xMin = xMax = yMin = yMax = zMin = zMax = 0;
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

    hitbox = new HitBox(xMin, xMax, yMin, yMax, zMin, zMax);

    pos.shrink_to_fit();
    texCoord.shrink_to_fit();
    normals.shrink_to_fit();
    indices.shrink_to_fit();

    entries[index].pos = pos;
    entries[index].texCoord = texCoord;
    entries[index].normals = normals;
    entries[index].indices = indices;
}

void GameObject::initMaterials(const aiScene* scene, const std::string& filename)
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
                materials[i].texture->load();
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

void GameObject::drawHitbox()
{
    double xMax = hitbox->xMax;
    double xMin = hitbox->xMin;
    double yMax = hitbox->yMax;
    double yMin = hitbox->yMin;
    double zMax = hitbox->zMax;
    double zMin = hitbox->zMin;
    
    glBegin(GL_LINES);
        glColor4f(1.0f, 1.0f, 0.0f, 1);
        glVertex3f(0, 5, 0); glVertex3f(0, -5, 0);
    glEnd();
        
    glBegin(GL_QUADS);

        glColor4f(1.0f, 0.0f, 0.0f, 1);

        glVertex3f(xMax, yMax, zMax);
        glVertex3f(xMax, yMax, zMin);
        glVertex3f(xMin, yMax, zMin);
        glVertex3f(xMin, yMax, zMax);

        glVertex3f(xMax, yMax, zMax);
        glVertex3f(xMin, yMax, zMax);
        glVertex3f(xMin, yMin, zMax);
        glVertex3f(xMax, yMin, zMax);


        glVertex3f(xMax, yMin, zMax);
        glVertex3f(xMax, yMin, zMin);
        glVertex3f(xMin, yMin, zMin);
        glVertex3f(xMin, yMin, zMax);

        glVertex3f(xMax, yMax, zMin);
        glVertex3f(xMin, yMax, zMin);
        glVertex3f(xMin, yMin, zMin);
        glVertex3f(xMax, yMin, zMin);

    glEnd();
}

void GameObject::loadModel(const std::string& filename, bool flipNormals, bool showTexture)
{
    this->flipNormals = flipNormals;
    this->showTexture = showTexture;
    hasTexture = false;
    hitbox = nullptr;
    hasModel = true;

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filename.c_str(),
        aiProcessPreset_TargetRealtime_Quality);

    if (scene) {
        initFromScene(scene, filename);
    }
}

HitBox* GameObject::getHitBox()
{
    return hitbox;
}

void GameObject::scaleHitbox(Vector3 scale)
{
    hitbox->scale(scale);
}

void GameObject::setShowTexture(bool showTexture)
{
    this->showTexture = showTexture;
}

void GameObject::setShowHitbox(bool showHitbox)
{
    this->showHitbox = showHitbox;
}

void GameObject::setCurrentCollisions(std::vector<GameObject*> collisions)
{
    currentCollisions = collisions;
}

void GameObject::update()
{
    vel += accel * Game::inst().getDeltaTime();
    pos += vel * Game::inst().getDeltaTime();
}

void GameObject::doScale(Vector3 scale)
{
    this->scale = scale;
    
    hitbox->scale(scale);
}

void GameObject::doRotate(Vector3 rot)
{
    this->rot = rot;

    hitbox->rotate(rot);
}

HitBox::HitBox(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax) :
    xMin{xMin}, xMax{xMax}, yMin{yMin}, yMax{yMax}, zMin{zMin}, zMax{zMax}
{
    upperRightFront = Vector3(xMax, yMax, zMax);
    upperRightBack = Vector3(xMax, yMax, zMin);
    upperLeftFront = Vector3(xMin, yMax, zMax);
    upperLeftBack = Vector3(xMin, yMax, zMin);
    lowerRightFront = Vector3(xMax, yMin, zMax);
    lowerRightBack = Vector3(xMax, yMin, zMin);
    lowerLeftFront = Vector3(xMin, yMin, zMax);
    lowerLeftBack = Vector3(xMin, yMin, zMin);
}

void HitBox::rotate(Vector3 rot)
{
    xMin = xMax = yMin = yMax = zMin = zMax = 0;

    upperRightFront = rotateVertex(upperRightFront, rot);
    recalculateBounds(upperRightFront);
    upperRightBack = rotateVertex(upperRightBack, rot);
    recalculateBounds(upperRightBack);
    upperLeftFront = rotateVertex(upperLeftFront, rot);
    recalculateBounds(upperLeftFront);
    upperLeftBack = rotateVertex(upperLeftBack, rot);
    recalculateBounds(upperLeftBack);
    lowerRightFront = rotateVertex(lowerRightFront, rot);
    recalculateBounds(lowerRightFront);
    lowerRightBack = rotateVertex(lowerRightBack, rot);
    recalculateBounds(lowerRightBack);
    lowerLeftFront = rotateVertex(lowerLeftFront, rot);
    recalculateBounds(lowerLeftFront);
    lowerLeftBack = rotateVertex(lowerLeftBack, rot);
    recalculateBounds(lowerLeftBack);
}

void HitBox::scale(Vector3 scale)
{
    xMin = xMax = yMin = yMax = zMin = zMax = 0;

    upperRightFront = scaleVertex(upperRightFront, scale);
    recalculateBounds(upperRightFront);
    upperRightBack = scaleVertex(upperRightBack, scale);
    recalculateBounds(upperRightBack);
    upperLeftFront = scaleVertex(upperLeftFront, scale);
    recalculateBounds(upperLeftFront);
    upperLeftBack = scaleVertex(upperLeftBack, scale);
    recalculateBounds(upperLeftBack);
    lowerRightFront = scaleVertex(lowerRightFront, scale);
    recalculateBounds(lowerRightFront);
    lowerRightBack = scaleVertex(lowerRightBack, scale);
    recalculateBounds(lowerRightBack);
    lowerLeftFront = scaleVertex(lowerLeftFront, scale);
    recalculateBounds(lowerLeftFront);
    lowerLeftBack = scaleVertex(lowerLeftBack, scale);
    recalculateBounds(lowerLeftBack);
}

Vector3 HitBox::rotateVertex(Vector3 vertex, Vector3 rot)
{
    float x = vertex.x * cos(rot.y) + vertex.z * sin(rot.y);
    float z = vertex.z * cos(rot.y) - vertex.x * sin(rot.y);
    return Vector3(x, vertex.y, z);
}

Vector3 HitBox::scaleVertex(Vector3 vertex, Vector3 scale)
{
    return Vector3(vertex.x * scale.x, vertex.y * scale.y, vertex.z * scale.z);
}

void HitBox::recalculateBounds(Vector3 vertex)
{
    xMin = vertex.x < xMin ? vertex.x : xMin;
    xMax = vertex.x > xMax ? vertex.x : xMax;
    yMin = vertex.y < yMin ? vertex.y : yMin;
    yMax = vertex.y > yMax ? vertex.y : yMax;
    zMin = vertex.z < zMin ? vertex.z : zMin;
    zMax = vertex.z > zMax ? vertex.z : zMax;
}

