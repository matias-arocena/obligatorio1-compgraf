#include "TreeObject.h"
#include <iostream>

TreeObject::TreeObject()
{
	model = new Model(true);
	model->loadMesh("../assets/tree.3ds");
	hitbox = model->getHitBox();
	doScale(Vector3(0.8, 0.8, 0.8));
}

TreeObject::~TreeObject()
{
	delete model;
}

void TreeObject::render()
{
	glPushMatrix();
	
	glTranslatef(pos.x, pos.y, pos.z);
	glScalef(scale.x, scale.y, scale.z);
	glEnable(GL_LIGHTING);
	model->render();
	glDisable(GL_LIGHTING);
	
	glPopMatrix();
}

void TreeObject::update()
{
	GameObject::update();
}


