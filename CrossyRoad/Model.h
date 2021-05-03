#include <vector>
#include <string>
#include <assimp/scene.h>
#include "Texture.h"

struct Material {
    bool hasTexture;
    float red, green, blue;
    Texture *texture;
};

struct MeshEntry {
    unsigned int materialIndex;
    std::vector<float> pos;
    std::vector<float> texCoord;
    std::vector<float> normals;
    std::vector<unsigned int> indices;
};

class Model
{
    bool hasTexture, flipNormals;
    double orientation;
    std::vector<MeshEntry> entries;
    std::vector<Material> materials;
    
public:
    Model(bool flipNormals = false) ;
    void LoadMesh(const std::string& Filename);
    void Render();
    void Rotate(double value);
    
private:
    void InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    void InitMaterials(const aiScene* pScene, const std::string& filename);
};

