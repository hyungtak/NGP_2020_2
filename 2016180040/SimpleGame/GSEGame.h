#pragma once
#include "Renderer.h"
#include "GSEObject.h"
#include "GSEGlobal.h"

class GSEGame
{
public:
	GSEGame();
	~GSEGame();

	void Update(float elapsedTimeInSec, GSEInputs* inputs);
	void RendererScene();
	int AddObject(float x, float y, float depth, float sx, float sy, float velX, float velY, float accX,float accY, float mass);
	void DeleteObject(int index);

private:
	Renderer* m_renderer = NULL;
	GSEObject* m_objects[GSE_MAX_OBJECTS];
	int m_HeroID = -1;
};

