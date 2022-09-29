#include "DxLib.h"
#include "game.h"
#include "player.h"

namespace
{
	// キャラクターのサイズ
	constexpr float kSizeX = 128.0f;
	constexpr float kSizeY = 128.0f;
	// ジャンプ力
	constexpr float kJumpAcc = -30.0f;
	// 重力
	constexpr float kGravity = 1.5f;
}

Player::Player()
{
	m_handle = -1;
	m_fieldY = 0.0f;

	m_isDead = false;
}

void Player::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle ,&m_graphSize.x, &m_graphSize.y);
	m_colSize = m_graphSize;
}

void Player:: setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = 64.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
}

void Player::update()
{
	if (m_isDead)	return;

	m_pos += m_vec;
	// 地面の当たり判定
	bool isField = false;
	if (m_pos.y > m_fieldY - m_graphSize.y)
	{
		m_pos.y = m_fieldY - m_graphSize.y;
		isField = true;
	}

	// キー入力処理
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// Zキー
	if (padState & PAD_INPUT_1)
	{
		if (isField)
		{
			m_vec.y = kJumpAcc;	// ジャンプ開始
		}
	}
	// 重力
	m_vec.y += kGravity;
}

void Player::draw()
{
	if (m_isDead)
	{
		// 死亡
		DrawRectGraph(m_pos.x, m_pos.y, m_graphSize.x / 2, 0, m_graphSize.x, m_graphSize.y, m_handle, true);
	}
	else
	{
		// 生存
		DrawRectGraph(m_pos.x, m_pos.y, 0, 0, m_graphSize.x / 2, m_graphSize.y, m_handle, true);
	}	
}

bool Player::isCol(Car& car)
{
	float playerLeft = getPos().x;
	float playerRight = getPos().x + getColSize().x / 2;
	float playerTop = getPos().y;
	float playerBottom = getPos().y + getColSize().y;

	float carLeft = car.getPos().x;
	float carRight = car.getPos().x + car.getSize().x;
	float carTop = car.getPos().y;
	float carBottom = car.getPos().y + car.getSize().y;

	if (playerLeft > carRight)	return false;
	if (playerRight < carLeft)	return false;
	if (playerTop > carBottom)	return false;
	if (playerBottom < carTop)	return false;

	return true;
}
