#include "stdafx.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"
#include "Scene7.h"
#include "Main.h"



Main::Main()
{
	
}

Main::~Main()
{

}
void Main::Init()
{
	Player* one = new Player;


	SCENE->AddScene("SCENE1",new Scene1(*one));
	SCENE->AddScene("SCENE2",new Scene2(*one));
	SCENE->AddScene("SCENE3",new Scene3(*one));
	SCENE->AddScene("SCENE4",new Scene4(*one));
	SCENE->AddScene("SCENE5",new Scene5(*one));
	SCENE->AddScene("SCENE6",new Scene6(*one));
	SCENE->AddScene("SCENE7",new Scene7(*one));

	SCENE->ChangeScene("SCENE1");

}

void Main::Release()
{
}

void Main::Update()
{
	SCENE->Update();
}

void Main::LateUpdate()
{
	SCENE->LateUpdate();
}

void Main::Render()
{
	SCENE->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"TheRamsey");
	app.SetInstance(instance);
	app.InitWidthHeight(1280.0f, 720.0f);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();
	
	return wParam;
}