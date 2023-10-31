#pragma once
class Scene6 : public Scene
{
private:
	ObImage bg;
	ObImage cloudA;
	ObImage cloudB;
	ObImage cloudC;
	ObImage Island;
	ObImage seamove1;
	ObImage seamove2;

	Player& pl;
	ObTileMap	map;
	bool isChangingNext = false;
	bool isChangingBack = false;

	float vol1;
	float vol2;
public:
	Scene6(Player& pl);
	~Scene6();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

