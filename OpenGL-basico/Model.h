#pragma once
#include <vector>
#include <string>
#include <assimp/scene.h>

#include "Texture.h"

struct Material {
    bool hasTexture;
    float red, green, blue;
    Texture* texture;
};

struct MeshEntry {
    unsigned int materialIndex;
    std::vector<float> pos;
    std::vector<float> texCoord;
    std::vector<float> normals;
    std::vector<unsigned int> indices;
};

struct HitBox {
    double xMin, xMax, yMin, yMax, zMin, zMax;
};

class Model
{
    bool hasTexture, flipNormals;
    double orientation;
    std::vector<MeshEntry> entries;
    std::vector<Material> materials;
    HitBox* hitbox;
public:
    Model(bool flipNormals = false);
    ~Model();
    void loadMesh(const std::string& filename);
    void render();
    HitBox* getHitBox();
private:
    void initFromScene(const aiScene* scene, const std::string& filename);
    void initMesh(unsigned int index, const aiMesh* mesh);
    void initMaterials(const aiScene* scene, const std::string& filename);
};

