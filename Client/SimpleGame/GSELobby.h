#pragma once

#include "Renderer.h"
#include "GSEGlobal.h"
#include <chrono>

class GSELobby
{
public:
	GSELobby();
	~GSELobby();

	void RendererScene(int num);
	void DrawP(float x, float y);
	void DrawL(float x, float y);
	void DrawA(float x, float y);
	void DrawY(float x, float y);
	void DrawE(float x, float y);
	void DrawR(float x, float y);
	void DrawC(float x, float y);
	void DrawO(float x, float y);

private:
	int playerNumSave = 0;
	Renderer* m_renderer = NULL;
	std::chrono::system_clock::time_point loadingTimer;
	std::chrono::duration<float> boxMoveTimer;
};

