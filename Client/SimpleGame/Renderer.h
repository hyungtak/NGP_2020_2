#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	void DrawSolidRect(float x, float y, float z, float sizeX, float sizeY, float r, float g, float b, float a);

	void DrawP(float x, float y);
	void DrawL(float x, float y);
	void DrawA(float x, float y);
	void DrawY(float x, float y);
	void DrawE(float x, float y);
	void DrawR(float x, float y);
	void DrawC(float x, float y);
	void DrawO(float x, float y);

	void DrawW(float x, float y);
	void DrawI(float x, float y);
	void DrawN(float x, float y);
	void DrawD(float x, float y);

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string* target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();
	void GetGLPosition(float x, float y, float* newX, float* newY);

	bool m_Initialized = false;

	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_SolidRectShader = 0;
};

