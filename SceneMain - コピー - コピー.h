#pragma once

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// �����������A�I������
	void init();
	void end();

	// �Q�[������
	void update();
	// �`��
	void draw();
};