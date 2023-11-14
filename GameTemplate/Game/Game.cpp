#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Bannin.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Botan.h"
#include "Star.h"
#include "GameClear.h"
#include "GameOver.h"
#include "sound/SoundEngine.h"

Game::Game()
{
	
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
	//時間を削除する。
	//DeleteGO(this);
}

bool Game::Start()
{
	//プレイヤーのオブジェクトを作る。
	player = NewGO<Player>(0, "player");
	player->m_position = { -650.0f,0.0f,0.0f };

	//番人のオブジェクトを作る。
	//m_levelRender.Init("Assets/modelData/level.tkl",
	//	[&](LevelObjectData& objData)
	//	{
	//		if (objData.EqualObjectName(L"Bannin") == true)
	//		{
	//			//番人のオブジェクトを作る。
	//			bannin = NewGO<Bannin>(0, "bannin");
	//			//座標を設定。
	//			bannin->SetPosition(objData.position);
	//			//回転を設定。
	//			bannin->SetRotation(objData.rotation);
	//			//大きさを設定。
	//			bannin->SetScale(objData.scale);
	//			return true;
	//		}
	//		return true;
	//	});

	bannin = NewGO<Bannin>(0, "bannin");
	bannin->m_position = { -400.0f,0.0f,0.0f };
	

	//ゲームカメラのオブジェクトを作る。
	m_GameCamera = NewGO<GameCamera>(0, "gamecamera");

	//背景のオブジェクトを作る。
	background = NewGO<BackGround>(0, "backGround");

	//background->m_position = { 0.0f,0.0f,0.0f };

	//ボタンのオブジェクトを作る。
	//botan = NewGO<Botan>(0, "botan");
	//botan->m_position = { -600.0f,-20.0f,500.0f };

	//Starクラスのオブジェクトを作る。
	Star* star1 = NewGO<Star>(0, "star");
	star1->m_position = { -800.0f,10.0f,0.0f };
	star1->m_firstPosition = star1->m_position;

	//当たり判定を可視化する。
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//ゲーム中のBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/maou_game_dangeon15.wav");

	//ゲーム中のBGMを再生する。
	gameBGM = NewGO<SoundSource>(1);
	gameBGM->Init(1);
	gameBGM->Play(true);

	////パス配置
	//struct Point {
	//	Vector3 s_position;
	//	int     s_number;
	//};


	return true;
}





//更新処理
void Game::Update()
{
	wchar_t wcsbuf[256];

	//int minit = 0;
	swprintf_s(wcsbuf, 256, L"%02d:%02d", int(minit), int(m_timer));
	
	//int minit = 0;
	float nowTime = m_timer;
	for (; nowTime >= 60.0f;) {
		nowTime -= 60.0f;
		m_timer = nowTime;	//追加
		minit++;
	}

	


	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(400.0f, 400.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
	//フォントの色を設定。
	m_fontRender.SetColor({ 255.0f,0.0f,0.0f,1.0f });


	m_timer += g_gameTime->GetFrameDeltaTime(); //1f=1/60秒
	


	//プレイヤーから番人に向かうベクトルを計算。
	Vector3 diff = player->m_position - bannin->m_position;
	//ベクトルの長さが120.0fより小さかったら。
	if (diff.Length() <= 120.0f)
	{

		//ゲームオーバーのオブジェクトを作る。
		NewGO<GameOver>(0, "gameover");
		//自身を削除する。
		DeleteGO(this);
		
	}



	//☆が全部(5つ)消えたら
	if (player->starCount == 1)
	{
		//ゲームクリアのオブジェクトをつくる。
		NewGO<GameClear>(0, "gameclear");
		//自身を削除する。
		DeleteGO(this);
	}




	
}

void Game::Render(RenderContext& rc)
{
	//フォントを描画する。
	m_fontRender.Draw(rc);
}
