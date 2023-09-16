#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"

Title::Title()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/meiroMEIN.dds", 1920.0f, 1080.0f);
	//m_spriteRender.Update();

	//タイトルのBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/maou_bgm_8bit29.wav");
	//タイトルのBGMを再生する。
	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
}

Title::~Title()
{
	//タイトルのBGMを削除する。
	DeleteGO(titleBGM);
}


//更新処理
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
	//画像を描画する。
	m_spriteRender.Draw(rc);
}