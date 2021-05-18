#pragma once
#include "Vector3.h"
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
	HitBox(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax);
	void rotate(Vector3 rot);
	void scale(Vector3 scale);
private:
	Vector3 upperRightFront;
	Vector3 upperRightBack;
	Vector3 upperLeftFront;
	Vector3 upperLeftBack;
	Vector3 lowerRightFront;
	Vector3 lowerRightBack;
	Vector3 lowerLeftFront;
	Vector3 lowerLeftBack;
	Vector3 rotateVertex(Vector3 vertex, Vector3 rot);
	Vector3 scaleVertex(Vector3 vertex, Vector3 scale);
	void recalculateBounds(Vector3 vertex);
};



class Game;

class GameObject
{
	public:
		GameObject() 
		{
			pos = Vector3();
			scale = Vector3(1, 1, 1);
			rot = Vector3();
			showHitbox = false;
		};

		virtual void update(); 
		virtual void render();
		virtual void destroy();

		void loadModel(const std::string& filename, bool flipNormals = false, bool showTexture = true);
		Vector3 getRot()
		{
			return rot;
		}

		void setRot(Vector3 aVector)
		{
			rot = aVector;
		}

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
		void setShowHitbox(bool showHitbox);
		void setCurrentCollisions(std::vector<GameObject*> collisions);
		void scaleHitbox(Vector3 scale);
	private:
		Vector3 accel;
		void initFromScene(const aiScene* scene, const std::string& filename);
		void initMesh(unsigned int index, const aiMesh* mesh);
		void initMaterials(const aiScene* scene, const std::string& filename);
		void drawHitbox();

	protected:
		Vector3 pos;
		Vector3 vel;
		Vector3 rot;
		Vector3 scale;
		HitBox* hitbox;
		bool hasTexture, hasModel, flipNormals, showTexture, showHitbox;
		std::vector<MeshEntry> entries;
		std::vector<Material> materials;
		std::vector<GameObject*> currentCollisions;

		void doScale(Vector3 scale);
		void doRotate(Vector3 rot);
};

