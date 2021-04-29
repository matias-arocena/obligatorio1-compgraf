#include <vector>
#include <assimp/scene.h>

struct Vertex
{
    float posX, posY, posZ, normalX, normalY, normalZ;
 
    Vertex(const float posX, const float posY, const float posZ,
        const float normalX, const float normalY, const float normalZ);
};

struct Material {
    bool hasTexture;
    float red, green, blue;
};

struct MeshEntry {
    MeshEntry();

    ~MeshEntry();

    void Init(const std::vector<Vertex>& Vertices,
        const std::vector<unsigned int>& Indices);

    unsigned int VertexBuffer;
    unsigned int IndexBuffer;
    unsigned int NumIndices;
    unsigned int materialIndex;
};

class Model
{
    bool onlyWireframe;
    double orientation;
    std::vector<MeshEntry> entries;
    std::vector<Material> materials;


public:
    Model();
    void LoadMesh(const std::string& Filename);
    void Render();
    void ShowOnlyWireframe(bool onlyWireframe);
    void Rotate(double value);
    
private:
    void InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    void InitMaterials(const aiScene* pScene);

};

