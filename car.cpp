#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	// 待ち時間	1秒:60フレーム
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;
	// 車の速度
	constexpr float kSpeed = -15.0f;
	// 車のジャンプ力
	constexpr float kJumpCar = -30.0f;
	// 車の重力
	constexpr float kGravity = 1.5f;
}

Car::Car()
{
	m_handle = -1;
	m_Phandle = -1;
	m_fieldY = 0.0f;
	m_moveType = kMoveTypeNormal;
	m_waitFrame = 0;
	m_waitFeint = 60;	// 1秒
}

void Car::setGraphic(int handle, int Phandle)
{
	m_handle = handle;
	m_Phandle = Phandle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
	GetGraphSizeF(m_Phandle, &m_Psize.x, &m_Psize.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

	// 動きのバリエーションを選択
	int randNum = GetRand(99);
	if (randNum < 38)
	{
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum < 38 + 30)
	{
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 38 + 30 + 30)
	{
		m_moveType = kMoveTypeJump;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}
	
	// デバッグ用に挙動を決める
	m_moveType = kMoveTypeStop;

	// 動き始めるまでの時間を設定	1秒から3秒待つ	60フレームから180フレーム
	m_waitFrame = GetRand(kWaitFrameMax - kWaitFrameMin) + kWaitFrameMin;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

	switch (m_moveType)
	{
	case kMoveTypeNormal:
		updateNormal();
		break;
	case kMoveTypeStop:
		updateStop();
		break;
	case kMoveTypeJump:
		updateJump();
		break;
	case kMoveTypeReturn:
		updateReturn();
		break;
	default:
		updateNormal();
		break;
	}

	
}

void Car::draw()
{
	if (m_vec.x == -kSpeed)
	{
		// 右
		DrawTurnGraph(m_pos.x, m_pos.y, m_handle, true);
	}
	else
	{
		// 左
		DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "wait:%d", m_waitFrame);
}
/////////////
// private //
/////////////
// まっすぐ進む
void Car::updateNormal()
{
	m_pos += m_vec;

	if (m_pos.x == -10)
	{
		
	}
}

// 一時停止フェイント
void Car::updateStop()
{
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "wait:%d", m_waitFeint);

	if (m_pos.x < m_Psize.x + 60)
	{
		if (m_waitFeint > 0)
		{
			m_waitFeint--;
			return;
		}
	}
	m_pos += m_vec;
}

// ジャンプする
void Car::updateJump()
{
	m_pos += m_vec;

	// 地面の当たり判定
	bool isField = false;
	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}

	if (m_pos.x < m_Psize.x + 50)
	{
		if (isField)
		{
			m_vec.y = kJumpCar;	// ジャンプ開始
		}
	}
	// 重力
	m_vec.y += kGravity;
}

// 途中で引き返す(必ず成功)
void Car::updateReturn()
{
	m_pos += m_vec;

	if (m_pos.x < m_Psize.x + 60)
	{
		//m_vec.x = -kSpeed;
		if (m_waitFeint > 0)
		{
			m_vec.x = 0;
			m_waitFeint--;
		}
		else
		{
			m_vec.x = -kSpeed;
		}
	}
}