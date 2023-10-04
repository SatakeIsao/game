#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Bannin.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Botan.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"

bool Game::Start()
{

	return true;
}

Game::Game()
{
	//プレイヤーのオブジェクトを作る。
	player = NewGO<Player>(0, "player");
	player->m_position = { -600.0f,0.0f,0.0f };

	//番人のオブジェクトを作る。
	//m_levelRender.Init("Assets/level3D/level.tkl",
		//[&](LevelObjectData& objData)
		//{
			//if (objData.EqualObjectName(L"bannin") == true)
			//{
				//番人のオブジェクトを作る。
				//bannin = NewGO<Bannin>(0, "bannin");
				//座標を設定。
				//bannin->SetPosition(objData.position);
				//return true;
			//}
			//return true;
		//});

	//bannin = NewGO<Bannin>(0, "bannin");
	//bannin->m_position = { 500.0f,0.0f,-100.0f };

	//ゲームカメラのオブジェクトを作る。
	m_GameCamera = NewGO<GameCamera>(0, "gamecamera");

	//背景のオブジェクトを作る。
	background = NewGO<BackGround>(0, "backGround");
	
	//background->m_position = { 0.0f,0.0f,0.0f };

	//ボタンのオブジェクトを作る。
	botan = NewGO<Botan>(0, "botan");
	botan->m_position = {600.0f,-20.0f,-200.0f };

	//ゲーム中のBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/maou_game_dangeon15.wav");

	//ゲーム中のBGMを再生する。
	gameBGM = NewGO<SoundSource>(1);
	gameBGM->Init(1);
	gameBGM->Play(true);
}

Game::~Game()
{
	//プレイヤーを削除する。
	DeleteGO(player);
	//番人を削除する。
	DeleteGO(bannin);
	//ゲームカメラを削除する。
	DeleteGO(m_GameCamera);
	//ゲーム中のBGMを削除する。
	DeleteGO(gameBGM);
	//背景を削除する。
	DeleteGO(background);
}



//更新処理
void Game::Update()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d秒経過!!", int(m_timer));
	


	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(400.0f, 400.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
	//フォントの色を設定。
	m_fontRender.SetColor({ 255.0f,0.0f,0.0f,1.0f });

	m_timer += g_gameTime->GetFrameDeltaTime();


	Vector3 diff = botan->m_position - player->m_position;
	if (diff.Length() <= 70.0f)
	{
		NewGO<GameClear>(0, "gameclear");
		//自身を削除
		DeleteGO(this);
	}
	
}

void Game::Render(RenderContext& rc)
{
	//フォントを描画する。
	m_fontRender.Draw(rc);
}
