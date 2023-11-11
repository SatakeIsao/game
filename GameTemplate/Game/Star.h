#pragma once

class Player;
class Star : public IGameObject
{
public:
	Star();
	~Star();
	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);

	//メンバ変数。
	ModelRender m_modelRender; //モデルレンダー。
	Vector3 m_position;        //座標。
	Vector3 m_firstPosition;   //最初の座標。
	Player* m_player;          //プレイヤー。
	CharacterController	m_charaCon; //キャラコン。
};

