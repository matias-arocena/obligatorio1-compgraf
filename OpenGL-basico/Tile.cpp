#include "Tile.h"

Tile::Tile(int aX, int aY)
{
	loadModel("../assets/tiles/block.obj");
	setPos(Vector3((aX + 0.5f) * TILE_WIDTH, - TILE_WIDTH, -(aY + 0.5f) * TILE_WIDTH));
	doScale(Vector3(2, 2, 2));
}

void Tile::render()
{
	glPushMatrix();
	glTranslatef(getPos().x, getPos().y, getPos().z);
	glScalef(scale.x, scale.y, scale.z);
	GameObject::render();
	glPopMatrix();
}
