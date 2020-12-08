#pragma once

#include "Renderer.h"
#include "GSEGlobal.h"

class GSEFinishScene
{
public:
	GSEFinishScene();
	~GSEFinishScene();

	void RendererScene(int num);

	
	void WinPlayer(int playerNum);
	void DrawPlayers();

	void DrawW(float x, float y);
	void DrawI(float x, float y);
	void DrawN(float x, float y);
	void DrawD(float x, float y);
	void DrawR(float x, float y);
	void DrawA(float x, float y);
private:
	Renderer* m_renderer = NULL;
};

	