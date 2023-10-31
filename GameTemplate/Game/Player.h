#pragma once
class Game;

class Player : public IGameObject
{
public:
	//////////////////////////////////////
	// メンバ関数。
	//////////////////////////////////////
	Player();
	~Player();
	bool Start();
	void Update();
	
	void Render(RenderContext& rc);

	///<summary>
	///座標を設定。
	///</summary>
	/// <param name="position">座標。</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得。
	/// </summary>
	/// <returns>座標。</param>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	void Rotation();
	//ステート管理。
	void ManageState();
	//////////////////////////////////////
	// メンバ変数。
	//////////////////////////////////////
	enum EnAnimationClip {
		enAnimationClip_idle,	//待機アニメーション
		enAnimationClip_walk,	//歩きアニメーション
		enAnimationClip_Num,	//アニメーションクリップ
	};

	void Move();
	void PlayAnimation();
	ModelRender m_modelRender;
	Vector3 m_position; //座標
	CharacterController m_charaCon;	//キャラクターコントローラー
	Vector3 m_moveSpeed; //移動速度
	Quaternion m_rotation;	//クォータニオン。
	PointLight m_pointLight; //ポイントライト。
	int playerState = 0;	//プレイヤーのステート(状態)を表す変数。
	AnimationClip m_animClips[enAnimationClip_Num];
	Player* m_player = nullptr;
};


