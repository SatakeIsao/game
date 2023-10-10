#include "stdafx.h"
#include "Bannin.h"

#include "Game.h"
#include "Player.h"

//ColisionObjectを使用したいため、ファイルをインクルードする。
#include"collision/CollisionObject.h"
Bannin::Bannin()
{

}

bool Bannin::Start()
{
	//アニメーションを読み込む。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/bannin/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/bannin/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Bark].Load("Assets/animData/bannin/bark.tka");
	m_animationClips[enAnimationClip_Bark].SetLoopFlag(false);
	
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/Kemono.tks.tkm");
	//m_modelRender.SetScale(0.3f, 0.3f, 0.3f);

	//アニメーションイベント用の関数を設定する。
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	//座標を設定する。

	//大きさを設定する。
	m_modelRender.SetScale(m_scale);


	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0f,		//半径。
		100.0f,		//高さ。
		m_position  //座標。
	);



	return true;


}

void Bannin::Update()
{
	//追跡処理。
	Chase();
	//当たり判定。
	Collision();
}



void Bannin::Chase()
{
	//追跡ステートでないなら、追跡処理はしない。
	if (m_banninState != enBanninState_Chase)
	{
		return;
	}
}

void Bannin::Collision()
{
	//被ダメージ、あるいはダウンステートの時には。
	//当たり判定処理をしない。
	if (m_banninState == enBanninState_ReceiveDamage || m_banninState == enBanninState_Down)
	{
		return;
	}

	//番人の吠える用のコリジョン取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("Bannin_balk");
	//コリジョンの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_charaCon))
		{
			//HPを1減らす
			m_hp -= 1;

			//HPが0より上なら。
			if (m_hp > 0)
			{
				//被ダメージステートに遷移する。
				m_banninState - enBanninState_ReceiveDamage;
			}
			//HPが0なら。
			else if (m_hp == 0)
			{
				//ダウンステートに遷移する。
				m_banninState = enBanninState_Down;
			}

			//効果音を再生する。
		}
	}
}



void Bannin::Move()
{
	m_modelRender.SetPosition(m_position); //座標を設定。
}

void Bannin::Bark()
{
	//吠えないなら処理しない。
	if (m_banninState != enBanninState_Bark)
	{
		return;
	}

	//吠えていれば。
	if (m_isUnderBark == true)
	{
		//吠える用のコリジョンを作成する。
		MakeBarkCollision();
	}
}


const bool Bannin::SearchPlayer() const
{
	return false;
}

void Bannin::PlayAnimation()
{

}

void Bannin::MakeBarkCollision()
{

}

void Bannin::ProcessCommonStateTransition()
{
	
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
	//吠えるステートの時。
	case enBanninState_Bark:
		//吠えるステートのステート遷移処理。
		ProcessBarkStateTransition();
		break;
	}
}

void Bannin::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//キーの名前が「bark_start」の時。
	if (wcscmp(eventName, L"bark_start") == 0)
	{
		//吠えている
		m_isUnderBark = true;
	}
	//キーの名前が「bark_end」の時。
	else if (wcscmp(eventName, L"bark_end") == 0)
	{
		//吠えるのを終える。
		m_isUnderBark = false;
	}

}

void Bannin::Render(RenderContext& rc)
{
	//モデルの描画
	m_modelRender.Draw(rc);
}