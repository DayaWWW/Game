#include "stdafx.h"
#include "Boss.h"

Boss::Boss()
{
	//col.SetPivot() = OFFSET_B;
	col.isFilled = false;

	img.LoadFile(L"boss/sprBossWeaselIdle.png");
	//img.SetPivot() = OFFSET_B;
	img.maxFrame.x = 4;
	img.SetParentRT(col);
	img.SetScale().x = img.imageSize.x / 4.0f * 2.0f;
	img.SetScale().y = img.imageSize.y  * 2.0f;
	col.SetScale() = img.GetScale();

	state = BossState::IDLE;

	speed = 100.0f;
}

void Boss::Update()
{

	if (state == BossState::IDLE)
	{

	}
	else if (state == BossState::MOVE)
	{

		
		//move -> attack


		//move -> idle

	}
	else if (state == BossState::ATTACK)
	{
		


		//attack -> move
		
	}
	

}

void Boss::Render()
{
	col.Render();
	img.Render();

}



