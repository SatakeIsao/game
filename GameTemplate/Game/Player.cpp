#include "stdafx.h"
#include "Player.h"


Player::Player() 
{

}

Player::~Player()
{

}

bool Player::Start()
{

	//アニメーションクリップのロード。
	m_animClips[enAnimationClip_idle].Load("Assets/animData/idle.tka");
	m_animClips[enAnimationClip_walk].Load("Assets/animData/walk.tka");
	//ループフラグを設定する。
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/unityChan.tkm",m_animClips,enAnimationClip_Num,enModelUpAxisY);

	m_pointLight.Init();
	m_pointLight.SetPosition(m_position);
	m_pointLight.SetColor(Vector3(10.0f, 10.0f, 10.0f));
	m_pointLight.SetAffectPowParam(0.7f);
	m_pointLight.SetRange(100.0f);

	//キャラクターコントローラーを初期化。
	m_charaCon.Init(25.0f, 75.0f, m_position);

	return true;
}

void Player::Update()
{
	//移動処理。
	Move();

	//回転処理。
	Rotation();
	//ステート管理。
	ManageState();
	//アニメーションを再生する。
	PlayAnimation();

	Vector3 pointLightPosition = m_position;
	pointLightPosition.y += 50.0f;
	m_pointLight.SetPosition(pointLightPosition);
	m_pointLight.Update();

	//モデルの更新。
	m_modelRender.Update();
}

void Player::Move()
{
	//xzの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と120.0fを乗算。
	right *= stickL.x * 120.0f;
	forward *= stickL.y * 120.0f;

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;

	//キャラクターコントローラーを使って座標を移動させる。
	m_position = m_charaCon.Execute(m_moveSpeed, 1.0f / 60.0f);
	//座標を設定。
	m_modelRender.SetPosition(m_position);

}




void Player::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える。
		m_modelRender.SetRotation(m_rotation);
	}
}


//ステート管理。
void Player::ManageState()
{
	//地面に付いていたら。
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//ステートを1(歩き)にする。
		playerState = 1;
	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//ステートを0(待機)にする。
		playerState = 0;
	}
}




void Player::PlayAnimation()
{
	//switch文。
	switch (playerState) {
		//プレイヤーステートが0(待機)だったら。
	case 0:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_idle);
		break;

		//プレイヤーステートが1(歩き)だったら。
	case 1:
		//歩きアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_walk);
		break;
	}
}

void Player::Render(RenderContext& rc)
{
	//モデルの描画。
	m_modelRender.Draw(rc);
}