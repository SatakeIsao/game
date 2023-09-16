#include "stdafx.h"
#include "Botan.h"
#include "Player.h"
#include "GameClear.h"

Botan::Botan()
{
	//ボタンのモデルを読み込む。
	m_modelRender.Init("Assets/modelData/botan.tkm");

}

bool Botan::Start()
{
	player = FindGO<Player>("player");

	return true;
}

Botan::~Botan()
{

}

void Botan ::Update()
{
	m_modelRender.SetPosition(m_position);

	m_modelRender.Update();
}

void Botan ::Render(RenderContext& rc)
{
	//ボタンを描画する。
	m_modelRender.Draw(rc);
}