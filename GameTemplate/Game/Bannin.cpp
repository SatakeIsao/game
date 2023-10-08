#include "stdafx.h"
#include "Bannin.h"

Bannin::Bannin()
{

}

bool Bannin::Start()
{
	m_modelRender.Init("Assets/modelData/Kemono.tks.tkm");
	//m_modelRender.SetScale(0.3f, 0.3f, 0.3f);

	//アニメーションイベント用の関数を設定する。
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});
	return true;
}

void Bannin::Update()
{

}

void Bannin::Move()
{
	m_modelRender.SetPosition(m_position); //座標を設定。
}

void Bannin::Bark()
{
	//吠えないなら処理しない。
	if (m_banninState != enBanninState_Bark)
	{
		return;
	}

	//
}

void Bannin::PlayAnimation()
{

}

void Bannin::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//キーの名前が「bark_start」の時。
	if (wcscmp(eventName, L"bark_start") == 0)
	{
		//吠えている
		m_isUnderBark = true;
	}
	//キーの名前が「bark_end」の時。
	else if (wcscmp(eventName, L"bark_end") == 0)
	{
		//吠えるのを終える。
		m_isUnderBark = false;
	}

}

void Bannin::Render(RenderContext& rc)
{
	//モデルの描画
	m_modelRender.Draw(rc);
}