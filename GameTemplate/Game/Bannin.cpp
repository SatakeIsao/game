#include "stdafx.h"
#include "Bannin.h"

Bannin::Bannin()
{

}

bool Bannin::Start()
{
	m_modelRender.Init("Assets/modelData/Kemono.tks.tkm");
	//m_modelRender.SetScale(0.3f, 0.3f, 0.3f);

	//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
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
	m_modelRender.SetPosition(m_position); //���W��ݒ�B
}

void Bannin::Bark()
{
	//�i���Ȃ��Ȃ珈�����Ȃ��B
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
	//�L�[�̖��O���ubark_start�v�̎��B
	if (wcscmp(eventName, L"bark_start") == 0)
	{
		//�i���Ă���
		m_isUnderBark = true;
	}
	//�L�[�̖��O���ubark_end�v�̎��B
	else if (wcscmp(eventName, L"bark_end") == 0)
	{
		//�i����̂��I����B
		m_isUnderBark = false;
	}

}

void Bannin::Render(RenderContext& rc)
{
	//���f���̕`��
	m_modelRender.Draw(rc);
}