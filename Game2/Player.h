#pragma once
enum class PlayerState
{
	IDLE,		//대기
	SIT,
	JUMP,
	JUMPDOWN,
	GETITEM,
	DAMAGED,
	DEAD,
	REST,
	RESTSLEEP,
	RESTWAKE,
	VICTORY,
	WARP,
	MOVE		//입력명령 움직이기
};

class Player
{
private:
	bool			jumping;
	bool			isright;
	bool			isrest;
	bool			isvictory;	// boss맵 이기면 양쪽 봉쇄된 door 열리게
	ObRect			col;
	PlayerState		state;

	ObImage			idle;
	ObImage			sit;
	ObImage			move;
	ObImage			jump;
	ObImage			jumpdown;

	ObImage			Gunidle;
	ObImage			Gunsit;
	ObImage			Gunmove;
	ObImage			Gunjump;
	ObImage			Gunjumpdown;
	
	ObImage			damaged;
	ObImage			dead;
	
	ObImage			rest;
	ObImage			restsleep;
	ObImage			restwake;

	ObImage			warp;
	ObImage			getitem;
	ObImage			victory;

	Bullet			bullet[30];


	float			speed;
	float			gravity;//중력
	float			damaging;//피격표현용



public:


	ObTileMap*		map;
public:
	Player();
	void Update();
	void Render();

	void    SetWorldPos(Vector2 pos) { col.SetWorldPos(pos); }
	Vector2 GetWorldPos() { return col.GetWorldPos(); }
	Vector2 GetFoot() { return col.GetWorldPos() + Vector2(0, 5); }
	Vector2 GetLeftSide() { return col.GetWorldPos() + Vector2(-20, 5); }
	Vector2 GetRightSide() { return col.GetWorldPos() + Vector2(20, 5); }
	void StepBack();
	void OnHalfBlock();
	void StepBackR();
	void StepBackL();
	void Damage();
};