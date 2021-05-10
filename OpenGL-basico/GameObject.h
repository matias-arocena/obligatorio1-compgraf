#pragma once
#include "Vector3.h"
#include "Game.h"
#include "Texture.h"

#include <vector>
#include <assimp/scene.h>

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



class GameObject
{
	public:
		GameObject() 
		{
			pos = Vector3();
			scale = Vector3(1, 1, 1);
		};
		
		~GameObject();

		void GameObject::update()
		{
			vel += accel * Game::inst().getDeltaTime();
			pos += vel * Game::inst().getDeltaTime();
		}

		virtual void render();
		virtual void destroy() {}

		void loadModel(const std::string& filename, bool flipNormals = false, bool showTexture = true);

		Vector3 getPos()
		{
			return pos;
		}

		void setPos(Vector3 aVector)
		{
			pos = aVector;
		}

		void setVel(Vector3 aVector)
		{
			vel = aVector;
		}

		Vector3 getVel()
		{
			return vel;
		}
		
		HitBox* getHitBox();

		void setAccel(Vector3 aVector)
		{
			accel = aVector;
		}

		Vector3 getAccel()
		{
			return accel;
		}

		virtual void setShowTexture(bool showTexture);
		void setCurrentCollisions(std::vector<GameObject*> collisions);
	private:
		Vector3 accel;
		void initFromScene(const aiScene* scene, const std::string& filename);
		void initMesh(unsigned int index, const aiMesh* mesh);
		void initMaterials(const aiScene* scene, const std::string& filename);

	protected:
		Vector3 pos;
		Vector3 vel;
		Vector3 scale;
		HitBox* hitbox;
		bool hasTexture, hasModel, flipNormals, showTexture;
		std::vector<MeshEntry> entries;
		std::vector<Material> materials;
		std::vector<GameObject*> currentCollisions;

		void doScale(Vector3 scale);
};

