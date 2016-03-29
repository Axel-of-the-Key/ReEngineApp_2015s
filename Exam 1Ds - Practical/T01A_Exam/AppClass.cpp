#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("YOUR NAME GOES HERE"); // Window Name
	m_pSystem->SetWindowWidth(720); //Set window dimensions
	m_pSystem->SetWindowHeight(720);
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);//Set clear color
}
void AppClass::InitVariables(void)
{
	//Set the camera position
	m_pCameraMngr->SetPosition(vector3(0.0f, 0.0f, 18.0f));
	//Load the model
	m_pMeshMngr->LoadModel("Lego\\Unikitty.bto", "Unikitty");
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

	matrix4 m4Scale = glm::scale(vector3(0.25f)); //example
	m_m4Model = m4Scale;
#pragma endregion
#pragma region DOES NOT NEED CHANGES
	std::vector<vector3> lStops;
	lStops.push_back(vector3(-2.25f,-2.25f, 0.0f));
	lStops.push_back(vector3( 0.0f, 2.25f, 0.0f));
	lStops.push_back(vector3( 2.25f,-2.25f, 0.0f));
	
	static uint nStart = 0;
	static uint nEnd = 1;
		
	float fPercent = MapValue(static_cast<float>(dTotalTime), 0.0f, 1.5f, 0.0f, 1.0f);
	
	vector3 v3Position;
	v3Position = glm::lerp(lStops[nStart], lStops[nEnd], fPercent);
	m_m4Model = glm::translate(v3Position) * m4Scale;
	
	if (fPercent > 1.0f)
	{
		nStart++;
		nEnd++;

		if (nEnd >= lStops.size())
			nEnd = 0;
		if (nStart >= lStops.size())
			nStart = 0;

		dTotalTime = 0.0;
	}
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Model, "Unikitty");

	for (uint i = 0; i < lStops.size(); i++)
	{
		m_pMeshMngr->AddSphereToQueue(glm::translate(lStops[i]) * m4Scale, RERED, WIRE);
	}
	
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