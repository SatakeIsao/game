#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定
	m_toCameraPos.Set(10.0f, 50.0f, 0.0f);
	
	//プレイヤーのインスタンスを探す
	m_player = FindGO<Player>("player");

	//ばねカメラの初期化
	//m_springCamera.Init(
		//*g_camera3D,	//ばねカメラの処理を行うカメラを指定。
		//1000.0f,		//カメラの移動速度の最大値。
		//true,			//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		//5.0f			//カメラに設定される球体コリジョンの半径。第３引数がtureの時に有効になる。

	//);

	//カメラのニアクリップとファークリップを設定
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(30000.0f);

	return true;
}

void GameCamera::Update()
{
	//カメラを更新
	//注視点を計算する。
	Vector3 target = m_player->m_position;
	//注視点 プレイヤーの座標に設定
	target.y += 30.0f;
	//target.z += 10.0f;
	
	//視点を計算する。
	Vector3 toCameraPosOld = m_player->m_position;
	toCameraPosOld.y += 30.0f;
	//パッドの入力を使ってカメラを回す
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	qRot.Apply(m_toCameraPos);

	//X軸周りの回転
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY,m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX , 1.3f * y);
	qRot.Apply(m_toCameraPos);

	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になる→ベクトルから強さがなくなり、方向のみの情報となるということ
	//Vector3 toPosDir =m_player->m_position;//m_toCameraPos;
	//toPosDir.Normalize();
	//if (toPosDir.y < -0.2f) {
	//	//カメラが上向きすぎ
	//	m_toCameraPos = toCameraPosOld;
	//}
	//else if (toPosDir.y > 0.9f) {
	//	//カメラが下向きすぎ
	//	m_toCameraPos = toCameraPosOld;
	//}

	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;

	//ばねカメラに注視点と視点を設定
	//m_springCamera.SetPosition(pos);
	//m_springCamera.SetTarget(target);

	//メインカメラに注視点と視点を設定
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新
	g_camera3D->Update();
	//m_springCamera.Update();
}