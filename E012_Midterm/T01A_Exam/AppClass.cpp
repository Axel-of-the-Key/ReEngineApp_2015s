#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Alexander Dunn"); // Window Name
	m_pSystem->SetWindowWidth(720); //Set window dimensions
	m_pSystem->SetWindowHeight(720);
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);//Set clear color
}
void AppClass::InitVariables(void)
{
	//Set the camera position
	m_pCameraMngr->SetPosition(vector3(0.0f, 0.0f, 18.0f));
	//Load the model
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");

	m_m4Steve = IDENTITY_M4;
}
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
#pragma endregion
#pragma region Your code goes here
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 

	float fStartTime = 0.0f; //start of simulation
	float fEndTime = 5.0f; //end of simulation

	//m_m4Steve = IDENTITY_M4; //example
#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}
void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}
void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}