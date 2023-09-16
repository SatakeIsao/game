#pragma once

class Player;
//ボタンクラス。
class Botan:public IGameObject
{
public:
	Botan();
	~Botan();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
	bool Start();
	
	//メンバ変数。
	ModelRender m_modelRender; //モデルレンダー。
	Vector3 m_position; //座標。
	Player* player; //プレイヤー。
	Botan* botan; //ボタン。
};

