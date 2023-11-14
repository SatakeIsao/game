#include "stdafx.h"
#include "Bannin.h"

#include "Game.h"
#include "Player.h"
#include "GameClear.h"
#include "GameOver.h"

//ColisionObjectを使用したいため、ファイルをインクルードする。
#include"collision/CollisionObject.h"

Bannin::Bannin()
{

}

bool Bannin::Start()
{
	//アニメーションを読み込む。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/SkeletonIdle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/SkeletonRun.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	//m_animationClips[enAnimationClip_Bark].Load("Assets/modelData/Mutant.fbm/bark2.tka");
	//m_animationClips[enAnimationClip_Bark].SetLoopFlag(false);
	
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/Bannin2.fbm/Skeleton.tkm",m_animationClips,enAnimationClip_Num);
	//m_modelRender.Init("Assets/modelData/Bannin2.fbm/Skeleton.tkm");
	//m_modelRender.Update();
	
	//座標を設定する。
	Vector3 position = m_position;
	position.y = 2.5f;
	m_modelRender.SetPosition(m_position);
	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);
	//大きさを設定する。
	m_modelRender.SetScale(10.0f, 10.0f, 10.0f);

	//アニメーションイベント用の関数を設定する。
	//m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		//OnAnimationEvent(clipName, eventName);
		//});

	


	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0f,		//半径。
		100.0f,		//高さ。
		m_position  //座標。
	);

	m_player = FindGO<Player>("player");

	//乱数を初期化。
	srand((unsigned)time(NULL));
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	return true;
}

void Bannin::Update()
{
	//追跡処理。
	Chase();
	//回転処理。
	Rotation();
	//当たり判定。
	Collision();
	//アニメーションの再生。
	PlayAnimation();
	//ステートの遷移処理。
	ManageState();

	//モデルの更新。
	m_modelRender.Update();


	////番人の吠える用のコリジョン取得する。
	//const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_run");
	////コリジョンの配列をfor文で回す。
	//for (auto collision : collisions)
	//{
	//	//コリジョンとキャラコンが衝突したら。
	//	if (collision->IsHit(m_charaCon))
	//	{

	//		//ゲームオーバー
	//		NewGO<GameOver>(0, "gameover");
	//		//自身を削除する。
	//		DeleteGO(this);



	//		//効果音を再生する。
	//	}
	//}


	////プレイヤーから☆に向かうベクトルを計算。
	//Vector3 diff = m_player->m_position - m_position;
	////ベクトルの長さが120.0fより小さかったら。
	//if (diff.Length() <= 120.0f)
	//{
	//	//m_player->starCount += 1;
	//	//ゲームクリアのオブジェクトを作る。
	//	NewGO<GameOver>(0, "gameover");
	//	//自身を削除する。
	//	DeleteGO(this);
	//}
}

void Bannin::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rotation.SetRotationY(-angle);

	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);

	//プレイヤーの前ベクトルを計算する。
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Bannin::Chase()
{
	//追跡ステートでないなら、追跡処理はしない。
	if (m_banninState != enBanninState_Chase)
	{
		return;
	}

	//番人を移動させる。
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//地面についた。
		//重力を0にする。
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;
	//少しだけモデルの座標を上げる。
	modelPosition.y += 2.5f;
	//座標を設定する。
	m_modelRender.SetPosition(modelPosition);
}

void Bannin::Collision()
{
	//被ダメージ、あるいはダウンステートの時には。
	//当たり判定処理をしない。
	//if (m_banninState == enBanninState_ReceiveDamage || m_banninState == enBanninState_Down)
	//{
	//	return;
	//}

	////番人の吠える用のコリジョン取得する。
	//const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_run");
	////コリジョンの配列をfor文で回す。
	//for (auto collision : collisions)
	//{
	//	//コリジョンとキャラコンが衝突したら。
	//	if (collision->IsHit(m_charaCon))
	//	{
	//		
	//		//ゲームオーバー
	//		NewGO<GameOver>(0, "gameover");
	//		//自身を削除する。
	//		DeleteGO(this);

	//

	//		//効果音を再生する。
	//	}
	//}


}



void Bannin::Move()
{
	

}

void Bannin::Bark()
{
	//吠えないなら処理しない。
	//if (m_banninState != enBanninState_Bark)
	//{
	//	return;
	//}

	////吠えていれば。
	//if (m_isUnderBark == true)
	//{
	//	//吠える用のコリジョンを作成する。
	//	MakeBarkCollision();
	//}
}

//const bool Bannin::SearchPoint() const
//{
	//以下ループ

	////目標とするポイントの座標から現在の座標を引いて、距離ベクトルを求める     
	//Vector3 diff = m_point->s_poition - m_position;
	////距離が一定以内なら目的地とするポイントを変える
	//if (diff.Length() <= 20.0f) {

	//	//今目的地としているポイントが配列の最後の要素なら
	//  //一番最初のポイントを目的地とする
	//	if (m_point->s_number == m_poinstList.size()) {
	//		m_point = m_pointList[0];
	//	}

	//	//そうでないなら配列の次の要素のポイントを目的地とする
	//	else {
	//		m_point = m_pointList[m_point->s_number];
	//	}
	//}

	////目標とするポイントの座標から現在の座標を引いて、距離ベクトルを求める 
	//Vector3 moveSpeed = m_point->s_position - m_position;
	////正規化する
	//moveSpeed.Normalize();
	////適当にスカラーをかける
	//moveSpeed *= 3.0f;
	////座標に加算する
	//m_position += moveSpeed;
//}

const bool Bannin::SearchPlayer() const
{
	//番人からプレイヤーに向かうベクトルを求める。
	Vector3 diff = m_player->GetPosition() - m_position;

	//プレイヤーにある程度近かったら。
	if (diff.LengthSq() <= 700.0 * 700.0f)
	{
		//番人からプレイヤーに向かうベクトルを正当化(大きさを１)する。
		diff.Normalize();
		//番人の正面のベクトルと、番人からプレイヤーに向かうベクトルの。
		//内積(cosθ)を求める。
		float cos = m_forward.Dot(diff);
		//内積(cosθ)から角度(θ)を求める。
		float angle = acosf(cos);
		//角度(θ)が120°(視野角)より小さければ。
		if (angle <= (Math::PI / 180.0f) * 120.0f)
		{
			//プレイヤーを見つけた！
			return true;
		}
	}
	//プレイヤーを見つけられなかった。
	return false;
}



void Bannin::MakePushLeverCollision()
{
	////コリジョンオブジェクトを作成する。
	//CollisionObject* collisionObject = NewGO<CollisionObject>(0);
	//Vector3 collisionPosition = m_position;

	////座標を番人の少し前に設定する。
	//collisionPosition += m_forward * 50.0f;
	////球状のコリジョンを作成する。
	//collisionObject->CreateSphere(collisionPosition, //座標。
	//	Quaternion::Identity, //回転。
	//	70.0f); //球の大きさ(半径)。
	//	//名前を付ける。
	//collisionObject->SetName("player_lever");
}

void Bannin::ProcessCommonStateTransition()
{
	//各タイマーを初期化。
	//待機時間と追跡時間を制限するため。
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;

	//番人からプレイヤーに向かうベクトルを計算する。
	Vector3 diff = m_player->GetPosition() - m_position;

	//移動速度を設定する。
	m_moveSpeed = diff * 0.50f;
	
	//プレイヤーを見つけたら。
	if (SearchPlayer() == true)
	{
		//追跡ステートに遷移する。
		m_banninState = enBanninState_Chase;
		return;
	}
	//プレイヤーを見つけられなければ。
	else
	{
		//待機ステートに遷移する。
		m_banninState = enBanninState_Idle;
		return;
	}
}

void Bannin::ProcessIdleStateTransition() //待機ステート。
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//待機時間がある程度経過したら。
	if (m_idleTimer >= 0.9f)
	{
		//他のステートへ遷移する。
		ProcessCommonStateTransition();
	}
}

void Bannin::ProcessRunStateTransition() //走りステート。
{
	//他のステートへ遷移する。
	ProcessCommonStateTransition();
}

void Bannin::ProcessChaseStateTransition()
{
	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//追跡時間がある程度経過したら。
	if (m_chaseTimer >= 0.8f)
	{
		//他のステートへ遷移する。
		ProcessCommonStateTransition();
	}
}

void Bannin::ProcessBarkStateTransition()
{

}

void Bannin::ManageState()
{
	switch (m_banninState)
	{
	//待機ステートの時。
	case enBanninState_Idle:
		//待機ステートのステート遷移処理。
		ProcessIdleStateTransition();
		break;
	//追跡ステートの時。
	case enBanninState_Chase:
		//追跡ステートのステート遷移処理。
		ProcessChaseStateTransition();
		break;
	////吠えるステートの時。
	//case enBanninState_Bark:
	//	//吠えるステートのステート遷移処理。
	//	ProcessBarkStateTransition();
	//	break;
	}
}



void Bannin::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//キーの名前が「bark_start」の時。
	//if (wcscmp(eventName, L"bark_start") == 0)
	//{
	//	//吠えている
	//	m_isUnderBark = true;
	//}
	////キーの名前が「bark_end」の時。
	//else if (wcscmp(eventName, L"bark_end") == 0)
	//{
	//	//吠えるのを終える。
	//	m_isUnderBark = false;
	//}

}

void Bannin::PlayAnimation()
{
	m_modelRender.SetAnimationSpeed(1.0f);
	switch (m_banninState)
	{
		//待機ステートの時。
	case enBanninState_Idle:
		//待機アニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.5f);
		break;
		//追跡ステートの時。
	case enBanninState_Chase:
		//追跡アニメーションを再生。
		m_modelRender.SetAnimationSpeed(1.2f);
		//走りアニメーションを再生。
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
		//吠えるステートの時。
	//case enBanninState_Bark:
		//吠えるアニメーションを再生。
		//m_modelRender.PlayAnimation(enAnimationClip_Bark, 0.1f);
		//break;
	default:
		break;
	}
}

void Bannin::Render(RenderContext& rc)
{
	//モデルの描画
	m_modelRender.Draw(rc);
}