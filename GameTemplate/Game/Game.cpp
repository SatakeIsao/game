#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Botan.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"

Game::Game()
{
	//プレイヤーのオブジェクトを作る。
	player = NewGO<Player>(0, "player");
	player->m_position = { -600.0f,0.0f,0.0f };

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

}
