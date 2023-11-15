#pragma once
class Game;

class GameClear :public IGameObject
{
public:
	GameClear();
	~GameClear();

	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数。
	SpriteRender m_spriteRender; //スプライトレンダー

	Game* game = nullptr;
};

