#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"

Player::Player()
{
	col.SetPivot() = OFFSET_B;
	col.isFilled = false;
	col.SetWorldPosY(100.0f);

	idle.LoadFile(L"Player/sprPlayerIdle.png");
	idle.SetPivot() = OFFSET_B;
	idle.maxFrame.x = 4;
	idle.SetParentRT(col);
	idle.SetScale().x = idle.imageSize.x / 4.0f * 2.0f;
	idle.SetScale().y = idle.imageSize.y * 2.0f;
	idle.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	idle.isVisible = false;

	Gunidle.LoadFile(L"Player/sprPlayerGunIdle.png");
	Gunidle.SetPivot() = OFFSET_B;
	Gunidle.maxFrame.x = 4;
	Gunidle.SetParentRT(col);
	Gunidle.SetScale().x = Gunidle.imageSize.x / 4.0f * 2.0f;
	Gunidle.SetScale().y = Gunidle.imageSize.y * 2.0f;
	Gunidle.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	Gunidle.isVisible = true;


	move.LoadFile(L"Player/sprPlayerWalk.png");
	move.SetPivot() = OFFSET_B;
	move.maxFrame.x = 4;
	move.SetParentRT(col);
	move.SetScale().x = move.imageSize.x / 4.0f * 2.0f;
	move.SetScale().y = move.imageSize.y * 2.0f;
	move.isVisible = false;

	Gunmove.LoadFile(L"Player/sprPlayerGunWalk.png");
	Gunmove.SetPivot() = OFFSET_B;
	Gunmove.maxFrame.x = 4;
	Gunmove.SetParentRT(col);
	Gunmove.SetScale().x = Gunmove.imageSize.x / 4.0f * 2.0f;
	Gunmove.SetScale().y = Gunmove.imageSize.y * 2.0f;
	Gunmove.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	Gunmove.isVisible = false;

	sit.LoadFile(L"Player/sprPlayerSit.png");
	sit.SetPivot() = OFFSET_B;
	sit.maxFrame.x = 4;
	sit.SetParentRT(col);
	sit.SetScale().x = sit.imageSize.x / 4.0f * 2.0f;
	sit.SetScale().y = sit.imageSize.y * 2.0f;
	sit.isVisible = false;

	Gunsit.LoadFile(L"Player/sprPlayerGunSit.png");
	Gunsit.SetPivot() = OFFSET_B;
	Gunsit.maxFrame.x = 4;
	Gunsit.SetParentRT(col);
	Gunsit.SetScale().x = Gunsit.imageSize.x / 4.0f * 2.0f;
	Gunsit.SetScale().y = Gunsit.imageSize.y * 2.0f;
	Gunsit.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	Gunsit.isVisible = false;

	jump.LoadFile(L"Player/sprPlayerJumpUpDown.png");
	jump.SetPivot() = OFFSET_B;
	jump.maxFrame.x = 4;
	jump.SetParentRT(col);
	jump.SetScale().x = jump.imageSize.x / 4.0f * 2.0f;
	jump.SetScale().y = jump.imageSize.y * 2.0f;
	jump.isVisible = false;

	Gunjump.LoadFile(L"Player/sprPlayerGunJumpUpDown.png");
	Gunjump.SetPivot() = OFFSET_B;
	Gunjump.maxFrame.x = 4;
	Gunjump.SetParentRT(col);
	Gunjump.SetScale().x = Gunjump.imageSize.x / 4.0f * 2.0f;
	Gunjump.SetScale().y = Gunjump.imageSize.y * 2.0f;
	Gunjump.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	Gunjump.isVisible = false;

	jumpdown.LoadFile(L"Player/sprPlayerJumpDown.png");
	jumpdown.SetPivot() = OFFSET_B;
	jumpdown.maxFrame.x = 2;
	jumpdown.SetParentRT(col);
	jumpdown.SetScale().x = jumpdown.imageSize.x / 2.0f * 2.0f;
	jumpdown.SetScale().y = jumpdown.imageSize.y * 2.0f;
	jumpdown.isVisible = false;

	Gunjumpdown.LoadFile(L"Player/sprPlayerGunJumpDown.png");
	Gunjumpdown.SetPivot() = OFFSET_B;
	Gunjumpdown.maxFrame.x = 2;
	Gunjumpdown.SetParentRT(col);
	Gunjumpdown.SetScale().x = Gunjumpdown.imageSize.x / 2.0f * 2.0f;
	Gunjumpdown.SetScale().y = Gunjumpdown.imageSize.y * 2.0f;
	Gunjumpdown.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	Gunjumpdown.isVisible = false;

	state = PlayerState::IDLE;
	isright = true;

	gravity = 0.0f;
	damaging = 0.0f;
	speed = 600.0f;

}

void Player::Update()
{

	if (INPUT->KeyPress(VK_RIGHT))	// 오른쪽방향 기본이미지
	{
		col.SetRotation().y = 0.0f;
	}
	else if (INPUT->KeyPress(VK_LEFT))	// 왼쪽 방향 볼때 이미지뒤집기
	{
		col.SetRotation().y = PI;
	}


	if (INPUT->KeyDown('Z'))
	{
		for (int i = 0; i < 30; i++)
		{
			if (not bullet[i].active)
			{
				if (col.GetRotation().y == 0.0f)
				{
					bullet[i].Init(GetWorldPos() + Vector2(70, 50), 0);
					break;
				}
				else	// 왼쪽 방향 볼때 이미지뒤집기
				{
					bullet[i].Init(GetWorldPos() + Vector2(-70, 50), PI);
					break;
				}
			}

		}
	}

	if (state == PlayerState::IDLE)
	{
		col.SetScale() = Gunidle.GetScale() * 0.9f;

		if (gravity > 100.0f)
		{
			Gunjumpdown.isVisible = true;
			Gunsit.isVisible = false;
			Gunmove.isVisible = false;
			Gunidle.isVisible = false;
			Gunjump.isVisible = false;
			Gunjumpdown.ChangeAnim(ANIMSTATE::STOP, 0.1f);
		}
		if (gravity <= 0.0f)
		{
			Gunidle.isVisible = true;
			Gunsit.isVisible = false;
			Gunmove.isVisible = false;
			Gunjumpdown.isVisible = false;
			Gunjump.isVisible = false;
			Gunidle.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}


		//idle -> move
		if (INPUT->KeyPress(VK_RIGHT))	// 오른쪽방향 볼때
		{
			Gunidle.isVisible = false;
			Gunjump.isVisible = false;
			Gunsit.isVisible = false;
			Gunjumpdown.isVisible = false;
			Gunmove.isVisible = true;

			Gunmove.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			state = PlayerState::MOVE;
		}
		else if (INPUT->KeyPress(VK_LEFT))	// 왼쪽방향 볼때
		{
			Gunidle.isVisible = false;
			Gunjump.isVisible = false;
			Gunsit.isVisible = false;
			Gunjumpdown.isVisible = false;
			Gunmove.isVisible = true;
			Gunmove.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			state = PlayerState::MOVE;
		}
		//idle -> jump

		if (INPUT->KeyDown('X'))
		{
			Gunidle.isVisible = false;
			Gunmove.isVisible = false;
			Gunsit.isVisible = false;
			Gunjumpdown.isVisible = false;
			Gunjump.isVisible = true;
			Gunjump.ChangeAnim(ANIMSTATE::ONCE, 0.2f);
			state = PlayerState::JUMP;
			gravity = -800.0f;
		}
		//idle -> sit
		if (INPUT->KeyDown(VK_DOWN))
		{
			Gunidle.isVisible = false;
			Gunmove.isVisible = false;
			Gunjump.isVisible = false;
			Gunjumpdown.isVisible = false;
			Gunsit.isVisible = true;
			Gunsit.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			state = PlayerState::SIT;
		}
	}

	else if (state == PlayerState::MOVE)
	{
		col.SetScale() = Gunmove.GetScale() * 0.9f;


		if (INPUT->KeyPress(VK_RIGHT))	// 오른쪽방향 볼때
		{
			col.MoveWorldPos(RIGHT * speed * DELTA);
		}
		else if (INPUT->KeyPress(VK_LEFT))	// 왼쪽방향 볼때
		{
			col.MoveWorldPos(LEFT * speed * DELTA);
		}


		// move -> idle
		if (not INPUT->KeyPress(VK_RIGHT) and not INPUT->KeyPress(VK_LEFT))
		{
			Gunidle.isVisible = true;
			Gunsit.isVisible = false;
			Gunmove.isVisible = false;
			Gunjumpdown.isVisible = false;
			Gunjump.isVisible = false;
			Gunidle.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			state = PlayerState::IDLE;
		}

		// move -> sit
		if ((INPUT->KeyPress(VK_RIGHT) and INPUT->KeyDown(VK_DOWN))
			or (INPUT->KeyPress(VK_LEFT) and INPUT->KeyDown(VK_DOWN)))// 오른쪽방향 볼때
		{
			Gunidle.isVisible = false;
			Gunmove.isVisible = false;
			Gunjump.isVisible = false;
			Gunjumpdown.isVisible = false;
			Gunsit.isVisible = true;
			Gunsit.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			state = PlayerState::SIT;
		}
		// move -> jump

		if ((INPUT->KeyPress(VK_RIGHT) and INPUT->KeyDown('X'))
			or (INPUT->KeyPress(VK_LEFT) and INPUT->KeyDown('X')))
		{
			Gunidle.isVisible = false;
			Gunmove.isVisible = false;
			Gunsit.isVisible = false;
			Gunjumpdown.isVisible = false;
			Gunjump.isVisible = true;
			Gunjump.ChangeAnim(ANIMSTATE::ONCE, 0.2f);
			state = PlayerState::JUMP;
			gravity = -800.0f;
		}

	}
	else if (state == PlayerState::JUMP)
	{
		col.SetScale() = Gunjump.GetScale() * 0.9f;

		if (gravity == 0.0f)
		{
			Gunidle.isVisible = true;
			Gunsit.isVisible = false;
			Gunmove.isVisible = false;
			Gunjumpdown.isVisible = false;
			Gunjump.isVisible = false;
			Gunidle.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			state = PlayerState::IDLE;
		}
		if (INPUT->KeyPress(VK_RIGHT))	// 오른쪽방향 볼때
		{
			col.MoveWorldPos(RIGHT * speed * DELTA);
		}
		else if (INPUT->KeyPress(VK_LEFT))	// 왼쪽방향 볼때
		{
			col.MoveWorldPos(LEFT * speed * DELTA);
		}
	}

	else if (state == PlayerState::SIT)
	{
		col.SetScale() = Gunsit.GetScale() * 0.9f;

		//sit -> idle
		if (INPUT->KeyUp(VK_DOWN))
		{
			Gunidle.isVisible = true;
			Gunsit.isVisible = false;
			Gunmove.isVisible = false;
			Gunjump.isVisible = false;
			Gunjumpdown.isVisible = false;
			Gunidle.ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			state = PlayerState::IDLE;

		}
		//sit -> Underjump


	}

	//맞고있을때
	if (damaging >= 0.0f)
	{
		damaging -= DELTA;
		Gunidle.color.x = RANDOM->Float(0.5f, 1.0f);
		Gunmove.color.x = RANDOM->Float(0.5f, 1.0f);
		Gunsit.color.x = RANDOM->Float(0.5f, 1.0f);
		Gunjump.color.x = RANDOM->Float(0.5f, 1.0f);

		Gunidle.color.w = RANDOM->Float(0.0f, 0.5f);
		Gunmove.color.w = RANDOM->Float(0.0f, 0.5f);
		Gunsit.color.w = RANDOM->Float(0.0f, 0.5f);
		Gunjump.color.w = RANDOM->Float(0.0f, 0.5f);

	}
	else
	{
		Gunidle.color.x = 0.5f;
		Gunmove.color.x = 0.5f;
		Gunsit.color.x = 0.5f;
		Gunjump.color.x = 0.5f;
		Gunidle.color.w = 0.5f;
		Gunmove.color.w = 0.5f;
		Gunsit.color.w = 0.5f;
		Gunjump.color.w = 0.5f;
	}

	for (int i = 0; i < 30; i++)
	{
		bullet[i].Update();
	}

	app.maincam->SetWorldPos(col.GetWorldPos());
	col.MoveWorldPos(DOWN * gravity * DELTA);
	gravity += DELTA * 2000.0f;

}

void Player::Render()
{

	Gunidle.Render();
	Gunsit.Render();
	Gunmove.Render();
	Gunjump.Render();
	Gunjumpdown.Render();
	idle.Render();
	move.Render();
	jump.Render();
	jumpdown.Render();
	sit.Render();
	col.Render();

	for (int i = 0; i < 30; i++)
	{
		bullet[i].Render();
	}

}

void Player::StepBack()
{
	gravity = 0.0f;
	col.MoveWorldPos(Vector2(0, 1) * speed * DELTA);
}

void Player::OnHalfBlock()
{

	//sit -> Underjump????

}

void Player::StepBackR()
{
	col.MoveWorldPos(Vector2(1, 0) * speed * DELTA);
}

void Player::StepBackL()
{
	col.MoveWorldPos(Vector2(-1, 0) * speed * DELTA);
}

void Player::Damage()
{
	//맞은지 1초가 지났을떄
	if (damaging <= 0.0f)
	{
		damaging = 1.0f;
	}
}


