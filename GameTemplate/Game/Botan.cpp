#include "stdafx.h"
#include "Botan.h"
#include "Player.h"
#include "GameClear.h"

Botan::Botan()
{
	//�{�^���̃��f����ǂݍ��ށB
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
	//�{�^����`�悷��B
	m_modelRender.Draw(rc);
}