#pragma once

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// 初期化処理、終了処理
	void init();
	void end();

	// ゲーム処理
	void update();
	// 描画
	void draw();
};