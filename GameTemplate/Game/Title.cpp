#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"

Title::Title()
{
	//�摜��ǂݍ��ށB
	m_spriteRender.Init("Assets/sprite/meiroMEIN.dds", 1920.0f, 1080.0f);
	//m_spriteRender.Update();

	//�^�C�g����BGM��ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/maou_bgm_8bit29.wav");
	//�^�C�g����BGM���Đ�����B
	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
}

Title::~Title()
{
	//�^�C�g����BGM���폜����B
	DeleteGO(titleBGM);
}


//�X�V����
void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		NewGO<Game>(0,"game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	//�摜��`�悷��B
	m_spriteRender.Draw(rc);
}