#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Game.h"

GameClear::GameClear()
{
	//ゲームクリアの画面を読み込む。
	m_spriteRender.Init("Assets/sprite/meiroCLEAR.dds", 1920.0f,1080.0f);
	//ゲームクリアしたタイムを表示。
	
}

GameClear::~GameClear()
{

}

//更新処理
void GameClear::Update()
{
	//Bボタンが押されていたら。
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		//タイトルのオブジェクトを作成
		NewGO<Title>(0, "title");

		
		//自身を削除する。
		DeleteGO(this);
	}
}

//描画処理
void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}
