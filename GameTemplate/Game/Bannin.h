#pragma once
class Player;

class Bannin : public IGameObject
{
public:
	//番人のステート。
	enum EnBanninState {
		enBanninState_Idle,			//待機。
		enBanninState_Walk,			//歩き。
		enBanninState_Run,			//走る。
		enBanninState_Bark,			//吠える。
		enBanninState_Chase,		//追跡。
		enBanninState_Down,			//HPが0。  
		enBanninState_ReceiveDamage,  //被ダメージ。
		enBanninState_Clear		    //クリアー。
	};
public:
	Bannin();
	bool Start();
	void Update();

	void Render(RenderContext& rc);

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	const Vector3& GetPosition() const
	{
		return m_position;
	}


	//HPを設定する。
	void SetHP(const int hp)
	{
		m_hp = hp;
	}


	//<summary>
	//動ける状態(ステート)かどうかを取得。
	// </summary>
	//<returns>動ける状態(ステート)ならtrue。</returns>
	bool IsEnableMove() const
	{
		return m_banninState != enBanninState_Bark &&
			m_banninState != enBanninState_Chase &&
			m_banninState != enBanninState_Down &&
			m_banninState != enBanninState_Clear;
	}
private:

	//アニメーションイベント用の関数。
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	//アニメーション
	enum EnAnimationClip {
		enAnimationClip_Idle,		//待機アニメーション。
		enAnimationClip_Walk,		//歩きアニメーション。
		enAnimationClip_Run,        //走りアニメーション。
		enAnimationClip_Bark,		//吠えるアニメーション。
		enAnimationClip_Down,		//ダウンアニメーション。
		enAnimationClip_Winner,		//勝利アニメーション。
		enAnimationClip_Num,		//アニメーションの数。
	};
	void Chase(); //追跡処理
	void Collision(); //プレイヤーとの当たり判定
	const bool SearchPlayer() const; //プレイヤーを探索する。
									 //プレイヤーが見つかったらtrue。

	void MakeBarkCollision(); //吠える用の当たり判定コリジョンを作成する。
	void ProcessCommonStateTransition(); //共通のステートの遷移処理。
	void ProcessIdleStateTransition(); //待機ステートの遷移処理。
	void ProcessRunStateTransition();   //走りステートの遷移処理。
	void ProcessChaseStateTransition();  //追跡ステートの遷移処理。
	void ProcessBarkStateTransition();  //吠えるステートの遷移処理。

	void Move();
	void Bark();
	void PlayAnimation();
	void ManageState();

	AnimationClip m_animationClips[enAnimationClip_Num];
	ModelRender m_modelRender;
	Vector3 m_position; //座標。
	Vector3 m_scale = Vector3::One; //大きさ
	CharacterController	m_charaCon; //キャラコン。
	EnBanninState m_banninState = enBanninState_Idle;
	bool m_isUnderBark = false; //吠えているのならtrue。
	int m_hp = 0;
	float m_chaseTimer = 0.0f; //追跡タイマー。
	float m_idleTimer = 0.0f; //待機タイマー。
};

