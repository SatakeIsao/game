#include "stdafx.h"
#include "Bannin.h"

Bannin::Bannin()
{

}

bool Bannin::Start()
{
	m_modelRender.Init("Assets/modelData/Kemono.tks.tkm");
	//m_modelRender.SetScale(0.3f, 0.3f, 0.3f);
	return true;
}

void Bannin::Update()
{

}

void Bannin::Move()
{
	m_modelRender.SetPosition(m_position); //座標を設定。
}

void Bannin::PlayAnimation()
{

}

void Bannin::Render(RenderContext& rc)
{
	//モデルの描画
	m_modelRender.Draw(rc);
}