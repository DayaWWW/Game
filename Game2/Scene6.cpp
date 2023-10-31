#include "stdafx.h"
#include "Scene6.h"



Scene6::Scene6(Player& pl) : pl(pl)
{
}

Scene6::~Scene6()
{
}

void Scene6::Init()
{
	map.file = "map6.txt";
	map.Load();
	map.CreateTileCost();
	map.SetLocalPosX(-1290.0f);
	map.SetLocalPosY(-360.0f);
	map.SetScale().x *= 1.05f;
	map.SetScale().y *= 1.05f;

	//플레이어가 참조하는 맵은 map
	pl.map = &map;


	bg.LoadFile(L"BG/sprBackgroundAcornTown.png");
	bg.SetScale().x = 2560;
	bg.SetScale().y = 1440;

	cloudC.LoadFile(L"BG/sprAcornCloudC.png");
	cloudC.SetLocalPosY(-210.0f);
	cloudC.SetScale().x = app.GetWidth() * 2.0f;
	cloudC.SetScale().y = app.GetHeight() * 2.0f;

	cloudB.LoadFile(L"BG/sprAcornCloudB.png");
	cloudB.SetLocalPosY(-135.0f);
	cloudB.SetScale().x = app.GetWidth() * 2.0f;
	cloudB.SetScale().y = app.GetHeight() * 2.0f;

	cloudA.LoadFile(L"BG/sprAcornCloudA.png");
	cloudA.SetLocalPosY(-160.0f);
	cloudA.SetScale().x = app.GetWidth() * 2.0f;
	cloudA.SetScale().y = app.GetHeight() * 2.0f;

	Island.LoadFile(L"BG/sprAcornTownIsland.png");
	Island.SetLocalPosY(-160.0f);
	Island.SetScale().x = app.GetWidth();
	Island.SetScale().y = app.GetHeight() * 0.2f;

	seamove1.LoadFile(L"BG/seamove15.png");
	seamove1.SetScale().x = seamove1.imageSize.x / 15.0f * 4.0f;
	seamove1.SetScale().y = seamove1.imageSize.y * 2.5f;
	seamove1.SetLocalPosY(-310.0f);
	seamove1.maxFrame.x = 15;
	seamove1.ChangeAnim(ANIMSTATE::LOOP, 0.2f);

	seamove2.LoadFile(L"BG/seamove15.png");
	seamove2.SetScale().x = seamove2.imageSize.x / 15.0f * 4.0f;
	seamove2.SetScale().y = seamove2.imageSize.y * 2.5f;
	seamove2.SetLocalPosY(-330.0f);
	seamove2.maxFrame.x = 15;
	seamove2.frame.x = 8;
	seamove2.ChangeAnim(ANIMSTATE::LOOP, 0.2f);

	isChangingNext = false;
	isChangingBack = false;


	LIGHT->lightColor.x = 0.5f;
	LIGHT->lightColor.y = 0.5f;
	LIGHT->lightColor.z = 0.5f;

	app.maincam->viewport.x = 0.0f;
	app.maincam->viewport.y = 0.0f;
	app.maincam->viewport.width = app.GetWidth();
	app.maincam->viewport.height = app.GetHeight();
}

void Scene6::Release()
{
}

void Scene6::Update()
{
	if (isChangingNext)
	{
		LIGHT->lightColor.x -= DELTA * 0.5f;
		LIGHT->lightColor.y -= DELTA * 0.5f;
		LIGHT->lightColor.z -= DELTA * 0.5f;

		if (LIGHT->lightColor.z < 0.1f)
		{
			pl.SetWorldPos(Vector2(-300.0f, -200.0f));
		}
	}
	if (isChangingBack)
	{
		LIGHT->lightColor.x -= DELTA * 0.5f;
		LIGHT->lightColor.y -= DELTA * 0.5f;
		LIGHT->lightColor.z -= DELTA * 0.5f;

		if (LIGHT->lightColor.z < 0.1f)
		{
			pl.SetWorldPos(Vector2(-1040.0f, -100.0f));
		}
	}

	cloudC.uv.x -= DELTA / cloudC.GetScale().x * 4.0f;
	cloudC.uv.z -= DELTA / cloudC.GetScale().x * 4.0f;

	cloudB.uv.x -= DELTA / cloudB.GetScale().x * 7.0f;
	cloudB.uv.z -= DELTA / cloudB.GetScale().x * 7.0f;

	cloudA.uv.x -= DELTA / cloudA.GetScale().x * 12.0f;
	cloudA.uv.z -= DELTA / cloudA.GetScale().x * 12.0f;

	seamove1.uv.x += DELTA / seamove1.GetScale().x * 20.0f;
	seamove1.uv.z += DELTA / seamove1.GetScale().x * 20.0f;

	seamove2.uv.x += DELTA / seamove2.GetScale().x * 20.0f;
	seamove2.uv.z += DELTA / seamove2.GetScale().x * 20.0f;

	pl.Update();

	float x =
		Utility::Saturate(app.maincam->GetWorldPos().x, -640.0f, -640.0f);
	app.maincam->SetWorldPosX(x);

	float y =
		Utility::Saturate(app.maincam->GetWorldPos().y, -0.0f, 0.0f);
	app.maincam->SetWorldPosY(y);
	//cout << y << endl;
	app.maincam->UpdateMatrix();
}

void Scene6::LateUpdate()
{	//디버깅용
	if (INPUT->KeyPress(VK_F1))
	{
		SCENE->ChangeScene("SCENE5", 1.0f);
		isChangingBack = true;
	}
	if (INPUT->KeyPress(VK_F2))
	{
		SCENE->ChangeScene("SCENE7", 1.0f);
		isChangingNext = true;
	}
	if (map.GetTileState((pl.GetFoot())) == TILE_WALL)
	{
		pl.StepBack();
	}
	else if (map.GetTileState((pl.GetLeftSide())) == TILE_WALL)
	{
		pl.StepBackR();
	}
	else if (map.GetTileState((pl.GetRightSide())) == TILE_WALL)
	{
		pl.StepBackL();
	}

	if (map.GetTileState((pl.GetRightSide())) == TILE_DOOR)
	{
		SCENE->ChangeScene("SCENE5", 1.0f);
		isChangingBack = true;
	}

	if (map.GetTileState((pl.GetLeftSide())) == TILE_DOOR)
	{
		SCENE->ChangeScene("SCENE7", 1.0f);
		isChangingNext = true;
	}
	if (map.GetTileState((pl.GetFoot())) == TILE_TRAP)
	{
		pl.Damage();
	}
	else if (map.GetTileState((pl.GetLeftSide())) == TILE_TRAP)
	{
		pl.Damage();
	}
	else if (map.GetTileState((pl.GetRightSide())) == TILE_TRAP)
	{
		pl.Damage();
	}
	if (map.GetTileState((pl.GetLeftSide())) == TILE_STONEWALL)
	{
		pl.StepBackR();
	}
	else if (map.GetTileState((pl.GetRightSide())) == TILE_STONEWALL)
	{
		pl.StepBackL();
	}
	if (map.GetTileState((pl.GetFoot())) == TILE_HALFBLOCK)
	{
		pl.StepBack();
	}
}

void Scene6::Render()
{
	Light::GetInstance()->Set();
	bg.Render();
	cloudC.Render();
	cloudB.Render();
	cloudA.Render();
	Island.Render();
	seamove1.Render();
	seamove2.Render();
	map.Render();
	pl.Render();
}

void Scene6::ResizeScreen()
{
}
