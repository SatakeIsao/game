#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Game.h"

GameClear::GameClear()
{
	//�Q�[���N���A�̉�ʂ�ǂݍ��ށB
	m_spriteRender.Init("Assets/sprite/meiroCLEAR.dds", 1920.0f,1080.0f);


	//wchar_t wcsbuf[256];
	
	//�Q�[���N���A�����^�C����\���B
	////swprintf_s(wcsbuf, 256, L"%02d:%02d", int(minit), int(m_timer));
}

GameClear::~GameClear()
{

}

//�X�V����
void GameClear::Update()
{
	//B�{�^����������Ă�����B
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		//�^�C�g���̃I�u�W�F�N�g���쐬
		NewGO<Title>(0, "title");

		
		//���g���폜����B
		DeleteGO(this);
	}
}

//�`�揈��
void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
