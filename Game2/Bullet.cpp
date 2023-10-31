#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{

	active = false;
	SetPivot() = OFFSET_T;
	isFilled = false;
	SetScale().x = 40.0f;
	SetScale().y = 35.0f;

	bulletImg.LoadFile(L"Player/sprCottonBulletDefault.png");
	bulletImg.maxFrame.x = 1;
	bulletImg.SetScale().x = bulletImg.imageSize.x * 2.0f / 1.0f;
	bulletImg.SetScale().y = bulletImg.imageSize.y * 2.0f;
	bulletImg.SetWorldPos(Vector2(0.0f, 5.0f));
	bulletImg.SetPivot() = OFFSET_T;
	bulletImg.SetParentRT(*this);
	bulletImg.ChangeAnim(ANIMSTATE::LOOP, 0.1f);

}

void Bullet::Init(Vector2 FirePos, float rotation)
{
	if (active)
		return;

	SetWorldPos(FirePos);
	fireDir.x = cos(rotation);
	fireDir.y = sin(rotation);
	speed = 800.0f;
	active = true;

	bulletImg.isVisible = true;

}

void Bullet::Update()
{
	if (not active)
		return;

	MoveWorldPos(fireDir * speed * DELTA);
}

void Bullet::Render(Camera* cam)
{
	if (not active)return;

	ObRect::Render(cam);

	bulletImg.Render(cam);

}