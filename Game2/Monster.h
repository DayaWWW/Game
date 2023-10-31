#pragma once
enum class MonsterState
{
	IDLE,
	MOVE,
	ATTACK
};

class Monster
{
	MonsterState	state;
	ObImage			img;
	ObRect			col;

	float			time;
	float			speed;

public:
	ObTileMap* map;

public:
	Monster();
	void Update();
	void Render();

	Vector2 GetWorldPos() { return col.GetWorldPos(); }

};

