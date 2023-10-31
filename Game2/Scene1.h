#pragma once
class Scene1 : public Scene
{

private:
	ObImage bg;
	ObImage cloudA;
	ObImage cloudB;
	ObImage cloudC;
	ObImage Island;
	ObImage seamove1;
	ObImage seamove2;
	ObImage AcornWood1;
	ObImage AcornWood2;


	Player& pl;
	ObTileMap	map;
	Camera cam1;
	bool isChangingNext = false;
	bool isChangingBack = false;


public:
	Scene1(Player& pl);
	~Scene1();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;

};

