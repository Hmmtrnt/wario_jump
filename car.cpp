#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	// �҂�����	1�b:60�t���[��
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;
	// �Ԃ̑��x
	constexpr float kSpeed = -15.0f;
	// �Ԃ̃W�����v��
	constexpr float kJumpCar = -30.0f;
	// �Ԃ̏d��
	constexpr float kGravity = 1.5f;
}

Car::Car()
{
	m_handle = -1;
	m_Phandle = -1;
	m_fieldY = 0.0f;
	m_moveType = kMoveTypeNormal;
	m_waitFrame = 0;
	m_waitFeint = 60;	// 1�b
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

	// �����̃o���G�[�V������I��
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
	
	// �f�o�b�O�p�ɋ��������߂�
	m_moveType = kMoveTypeStop;

	// �����n�߂�܂ł̎��Ԃ�ݒ�	1�b����3�b�҂�	60�t���[������180�t���[��
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
		// �E
		DrawTurnGraph(m_pos.x, m_pos.y, m_handle, true);
	}
	else
	{
		// ��
		DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	}
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "wait:%d", m_waitFrame);
}
/////////////
// private //
/////////////
// �܂������i��
void Car::updateNormal()
{
	m_pos += m_vec;

	if (m_pos.x == -10)
	{
		
	}
}

// �ꎞ��~�t�F�C���g
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

// �W�����v����
void Car::updateJump()
{
	m_pos += m_vec;

	// �n�ʂ̓����蔻��
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
			m_vec.y = kJumpCar;	// �W�����v�J�n
		}
	}
	// �d��
	m_vec.y += kGravity;
}

// �r���ň����Ԃ�(�K������)
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