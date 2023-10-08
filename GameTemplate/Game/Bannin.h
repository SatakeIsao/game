#pragma once
class Bannin;

class Bannin : public IGameObject
{
public:
	//番人のステート。
	enum EnBanninState {
		enBanninState_Idle,			//待機。
		enBanninState_Walk,			//歩き。
		enBanninState_Run,			//走る。
		enBanninState_Bark,			//吠える。
		enBanninState_Down,			//HPが0。
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
	//<summary>
	//動ける状態(ステート)かどうかを取得。
	// </summary>
	//<returns>動ける状態(ステート)ならtrue。</returns>
	bool IsEnableMove() const
	{
		return m_banninState != enBanninState_Bark &&
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

	void Move();
	void Bark();
	void PlayAnimation();

	AnimationClip m_animationClips[enAnimationClip_Num];
	ModelRender m_modelRender;
	Vector3 m_position; //座標。
	EnBanninState m_banninState = enBanninState_Idle;
	bool m_isUnderBark = false; //吠えているのならtrue。
};

