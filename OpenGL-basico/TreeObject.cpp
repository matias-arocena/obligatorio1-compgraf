#include "TreeObject.h"
#include <iostream>

TreeObject::TreeObject()
{
	loadModel("../assets/tree.3ds", true);
	doScale(Vector3(0.8, 0.8, 0.8));
}


void TreeObject::render()
{
	glPushMatrix();
	
	glTranslatef(pos.x, pos.y, pos.z);
	glScalef(scale.x, scale.y, scale.z);
	glEnable(GL_LIGHTING);
	GameObject::render();
	glDisable(GL_LIGHTING);
	
	glPopMatrix();
}

void TreeObject::update()
{
	GameObject::update();
}


