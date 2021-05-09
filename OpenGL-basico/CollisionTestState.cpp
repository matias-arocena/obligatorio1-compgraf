#include "CollisionTestState.h"

#include <iostream>
#include <unordered_map>

#include "TreeObject.h"
#include "CubeObject.h"

CollisionTestState::CollisionTestState() {
	showWireframe = false;
	showTexture = true;
	updateWireframe = false;
	updateShowTexture = false;
}

void CollisionTestState::init()
{
	CubeObject* cube = new CubeObject();
	cube->setPos(Vector3(0.0, 0.0, 0.0));
	entities.push_back(cube);

	CubeObject* enemy = new CubeObject(true);
	enemy->setPos(Vector3(-2.3, 0.0, 0.0));
	entities.push_back(enemy);

	TreeObject* tree = new TreeObject();
	tree->setPos(Vector3(2.3, 0.0, 0.0));
	entities.push_back(tree);
}

void CollisionTestState::update()
{
    SDL_Event event;
    SDL_PollEvent(&event);


	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			showWireframe = !showWireframe;
			updateWireframe = true;
			break;
		case SDLK_t:
			showTexture = !showTexture;
			updateShowTexture = true;
			break;
		case SDLK_q:
			Game::inst()._fin = true;
			break;
		case SDLK_RIGHT:
			entities[0]->setVel(Vector3(1, 0, 0));
			break;
		case SDLK_LEFT:
			entities[0]->setVel(Vector3(-1, 0, 0));
			break;
		case SDLK_UP:
			entities[0]->setVel(Vector3(0, 1, 0));
			break;
		case SDLK_DOWN:
			entities[0]->setVel(Vector3(0, -1, 0));
			break;
		default:
			break;
		}
	}

	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
			entities[0]->setVel(Vector3(0, 0, 0));
			break;
		case SDLK_LEFT:
			entities[0]->setVel(Vector3(0, 0, 0));
			break;
		case SDLK_UP:
			entities[0]->setVel(Vector3(0, 0, 0));
			break;
		case SDLK_DOWN:
			entities[0]->setVel(Vector3(0, 0, 0));
			break;
		default:
			break;
		}
	}

	entities[0]->setCurrentCollisions(getCollisions(entities[0]));
	for (const auto& e : entities) {
<<<<<<< Updated upstream
		e->setCurrentCollisions(getCollisions(e));
		if (updateShowTexture) {
			e->setShowTexture(showTexture);
		}
			
=======
>>>>>>> Stashed changes
		e->update();
	}
}

void CollisionTestState::render()
{
	if (updateWireframe && showWireframe) {
		updateWireframe = false;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (updateWireframe && !showWireframe) {
		updateWireframe = false;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	for (const auto& e : entities) {
		e->render();
	}
}


std::vector<GameObject*> CollisionTestState::getCollisions(GameObject* object) {
	std::vector<GameObject*> collisions;
	for (auto& e : entities) {
		if (e != object && collides(object, e)) {
			collisions.push_back(e);
		}
	}
	return collisions;
}

bool CollisionTestState::collides(GameObject* o1, GameObject* o2)
{
	Vector3 pos1 = o1->getPos();
	Vector3 pos2 = o2->getPos();
	HitBox* h1 = o1->getHitBox();
	HitBox* h2 = o2->getHitBox();

	bool collisionX = pos1.x + h1->xMax >= pos2.x + h2->xMin && pos1.x + h1->xMin <= pos2.x + h2->xMax;
	bool collisionY = pos1.y + h1->yMax >= pos2.y + h2->yMin && pos1.y + h1->yMin <= pos2.y + h2->yMax;
	bool collisionZ = pos1.z + h1->zMax >= pos2.z + h2->zMin && pos1.z + h1->zMin <= pos2.z + h2->zMax;

	return collisionX && collisionY && collisionZ;
}


