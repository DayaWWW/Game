#pragma once

enum class BossState
{
	IDLE,
	MOVE,
	ATTACK
};

class Boss
{
	BossState		state;
	ObImage			img;
	ObRect			col;


	float			time;
	float			speed;


public:
	ObTileMap*	map;

public:
	Boss();
	void Update();
	void Render();


	Vector2 GetWorldPos() { return col.GetWorldPos(); }

};

