#include <vector>
#include <assimp/scene.h>
struct Vertex
{
    float posX, posY, posZ, normalX, normalY, normalZ;
 
    Vertex(const float posX, const float posY, const float posZ,
        const float normalX, const float normalY, const float normalZ);
};

struct MeshEntry {
    MeshEntry();

    ~MeshEntry();

    void Init(const std::vector<Vertex>& Vertices,
        const std::vector<unsigned int>& Indices);

    unsigned int VertexBuffer;
    unsigned int IndexBuffer;
    unsigned int NumIndices;
};

class Model
{
public:
    Model();
    void LoadMesh(const std::string& Filename);
    void Render();

private:
    void InitFromScene(const aiScene* pScene, const std::string& Filename);
    void InitMesh(unsigned int Index, const aiMesh* paiMesh);
    //bool InitMaterials(const aiScene* pScene, const std::string& Filename);

    std::vector<MeshEntry> m_Entries;
};

