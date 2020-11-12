#include "stdafx.h"
#include "GSEGame.h"

GSEGame::GSEGame()
{
	//Renderer 积己
	m_renderer = new Renderer(500,500);

	for (int i = 0; i < GSE_MAX_OBJECTS; i++)
	{
		m_objects[i] = NULL;
	}
	
	//Create Player
	m_HeroID = AddObject(0, 0, 0, 20, 20, 0, 0, 0, 0, 2);
}

GSEGame::~GSEGame()
{
	//Renderer 昏力
}

void GSEGame::Update(float elapsedTimeInSec, GSEInputs* inputs)
{
	GSEUpdateParams othersParam;
	GSEUpdateParams heroParam;
	memset(&othersParam, 0, sizeof(GSEUpdateParams));
	memset(&heroParam, 0, sizeof(GSEUpdateParams));

	//calc force
	float forceAmount = 200.0f;
	if (inputs->KEY_A)
	{
		heroParam.forceX -= forceAmount;
	}
	if (inputs->KEY_D)
	{
		heroParam.forceX += forceAmount;
	}
	if (inputs->KEY_W)
	{
		heroParam.forceY += forceAmount;
	}
	if (inputs->KEY_S)
	{
		heroParam.forceY -= forceAmount;
	}

	//Update all objects
	for (int i = 0; i < GSE_MAX_OBJECTS; i++)
	{
		if (m_objects[i] != NULL)
		{
			if (i == m_HeroID)
			{
				m_objects[i]->Update(elapsedTimeInSec, &heroParam);
			}
			else
			{
				m_objects[i]->Update(elapsedTimeInSec, &othersParam);
			}
		}
	}
}

void GSEGame::RendererScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	
	// Renderer Test
	//m_renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);

	//Draw all objects
	for (int i = 0; i < GSE_MAX_OBJECTS; i++)
	{
		if (m_objects[i] != NULL) 
		{
			float x, y, depth;
			m_objects[i]->GetPosition(&x, &y, &depth);
			float sx, sy;
			m_objects[i]->GetSize(&sx, &sy);
			m_renderer->DrawSolidRect(x, y, depth, sx, 1, 1, 1, 1);
		}
	}

}

int GSEGame::AddObject(float x, float y, float depth, float sx, float sy, float velX, float velY, float accX, float accY, float mass)
{
	//find empty slot
	int index = -1;
	for (int i = 0; i < GSE_MAX_OBJECTS; i++)
	{
		if (m_objects[i] == NULL)
		{
			index = i;
			break;
		}
	}

	if (index < 0)
	{
		std::cout << "后 object 磊府 绝澜!!!!" << std::endl;
		return -1;
	}

	m_objects[index] = new GSEObject();
	m_objects[index]->SetPosition(x, y, depth);
	m_objects[index]->SetSize(sx, sy);
	m_objects[index]->SetVel(velX, velY);
	m_objects[index]->SetAcc(accX, accY);
	m_objects[index]->SetMass(mass);


	return index;
}

void GSEGame::DeleteObject(int index)
{
	if (m_objects[index] != NULL)
	{
		std::cout << "Try to delete NULL object : " << index << std::endl;
	}
	else 
	{

	}
	
}
