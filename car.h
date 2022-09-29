#pragma once

#include "Vec2.h"

class Car
{
public:
	Car();
	virtual ~Car() {}

	// �O���t�B�b�N�f�[�^�̐ݒ�	�����ŃT�C�Y���擾����
	void setGraphic(int handle, int Phandle);

	// �����ݒ�	�n�ʂ̍�����^����
	void setup(float fieldY);

	// �X�V
	void update();
	// �`��
	void draw();

	// �ʒu�̎擾
	Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	Vec2 getSize() const { return m_size; }

private:
	// �Ԃ̋����̃o���G�[�V����
	typedef enum MoveType
	{
		kMoveTypeNormal,
		kMoveTypeStop,
		kMoveTypeJump,
		kMoveTypeReturn,

		kMoveTypeNum,
	}MoveType;

private:
	void updateNormal();	// �܂������i��
	void updateStop();		// �ꎞ��~�t�F�C���g
	void updateJump();		// �W�����v����
	void updateReturn();	// �r���ň����Ԃ�(�K������)

private:
	// �O���t�B�b�N�n���h��
	int m_handle;
	// �v���C���[�̃O���t�B�b�N
	int m_Phandle;
	// �ړ��J�n�܂ł̑҂�����(�t���[����)
	int m_waitFrame;
	// �t�F�C���g�̑҂�����
	int m_waitFeint;

	bool m_isRestart;

	// �n�ʂ̍���
	float m_fieldY;

	// �O���t�B�b�N�̕��ƍ���	�����蔻��ɂ��g�p����
	Vec2 m_size;
	// �v���C���[�̃O���t�B�b�N�̕��ƍ���
	Vec2 m_Psize;
	// �ʒu
	Vec2 m_pos;
	// �x�N�g��
	Vec2 m_vec;

	// �Ԃ̓���
	MoveType m_moveType;
};