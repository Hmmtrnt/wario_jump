#pragma once

class SceneTitle
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	// �����������A�I������
	void init();
	void end();

	// �Q�[������
	void update();
	// �`��
	void draw();
};