#include "Tile.h"

Tile::Tile(int aX, int aY)
{
	setPos(Vector3(aX * TILE_WIDTH, 0, -aY * TILE_WIDTH));
}

void Tile::render()
{
	glPushMatrix();
	glTranslatef(getPos().x, getPos().y, getPos().z);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0, 0, TILE_WIDTH);
	glVertex3f(0, 0, 0);
	glVertex3f(TILE_WIDTH, 0, 0);
	glVertex3f(TILE_WIDTH, 0, TILE_WIDTH);
	glEnd();
	glPopMatrix();
}
