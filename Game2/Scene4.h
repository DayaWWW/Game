#pragma once
class Scene4 : public Scene
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
	bool isChangingNext = false;
	bool isChangingBack = false;


	float vol1;
	float vol2;
public:
	Scene4(Player& pl);
	~Scene4();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

