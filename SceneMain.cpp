#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"
#include "Vec2.h"

namespace
{
	// ’n–Ê‚Ì‚‚³
	constexpr int kFieldY = Game::kScreenHeight - 64;
}

SceneMain::SceneMain()
{
	m_hPlayer = -1;
	m_hCar = -1;
}

SceneMain::~SceneMain()
{

}

void SceneMain::init()
{
	m_hPlayer = LoadGraph("data/player.png");
	m_hCar = LoadGraph("data/car.png");

	
	m_player.setGraphic(m_hPlayer);
	m_player.setup(kFieldY);

	m_car.setGraphic(m_hCar, m_hPlayer);
	m_car.setup(kFieldY);
}

void SceneMain::end()
{
	DeleteGraph(m_hPlayer);
	DeleteGraph(m_hCar);
}

// ƒQ[ƒ€ˆ—
void SceneMain::update()
{
	m_player.update();
	m_car.update();

	// “–‚½‚è”»’è
	if (m_player.isCol(m_car))
	{
		m_player.setDead(true);
	}

	/*if (m_car.isRestart())
	{
		m_car.setup(kFieldY);
		m_player.setDead(false);
	}*/
}

// •`‰æ
void SceneMain::draw()
{
	// ’n–Ê‚Ì•`‰æ
	DrawLine(0, kFieldY, Game::kScreenWidth, kFieldY, GetColor(255, 255, 255));
	m_player.draw();
	m_car.draw();
}