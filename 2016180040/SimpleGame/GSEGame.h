#pragma once

#include "Renderer.h"

#include "GSEGlobal.h"

class GSEGame
{
public:
	GSEGame();
	~GSEGame();

	void Update(float elapsedTimeInSec, KeyInput* inputs);
	void RendererScene();
private:
	MapData m_pMapdata[MAP_SIZE][MAP_SIZE];
	Renderer* m_renderer = NULL;

};

