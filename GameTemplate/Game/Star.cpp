#include "stdafx.h"
#include "Star.h"
#include "Player.h"
#include "GameClear.h"

//ColisionObjectを使用したいため、ファイルをインクルードする。
#include"collision/CollisionObject.h"

Star::Star()
{


}

Star::~Star()
{

}

bool Star::Start()
{
	//☆のモデルを読み込む。
	m_modelRender.Init("Assets/modelData/Star/Star2.tkm");

	m_player = FindGO<Player>("player");

	//座標を設定する。
	Vector3 position = m_position;
	
	m_modelRender.SetPosition(m_position);
	//大きさを設定する。
	m_modelRender.SetScale(1.0f, 1.0f, 1.0f);

	//当たり判定を有効化する。
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0f,		//半径。
		100.0f,		//高さ。
		m_position  //座標。
	);

	return true;
}

void Star::Update()
{
	//絵描きさんの更新処理。
	m_modelRender.Update();

	//プレイヤーから☆に向かうベクトルを計算。
	Vector3 diff = m_player->m_position - m_position;
	//ベクトルの長さが120.0fより小さかったら。
	if (diff.Length() <= 120.0f)
	{
		m_player->starCount += 1;
		//ゲームクリアのオブジェクトを作る。
		//NewGO<GameClear>(0, "gameclear");
		//自身を削除する。
		DeleteGO(this);
	}

}

void Star::Render(RenderContext& rc)
{
	//☆を描画する。
	m_modelRender.Draw(rc);
}