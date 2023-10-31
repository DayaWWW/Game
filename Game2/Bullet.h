#pragma once

class Bullet : public ObRect
{

	ObImage			bulletImg;
	ObImage			bulletTrailImg;


	float			speed;
	Vector2			fireDir;


public:
	bool  active;
	Bullet();
	void Init(Vector2 FirePos, float rotation);		//√ ±‚»≠
	void Update();
	void Render(class Camera* cam = app.maincam);
};



