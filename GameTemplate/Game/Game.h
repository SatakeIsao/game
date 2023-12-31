#pragma once
#include "Level3DRender/LevelRender.h"


class Player;
class Bannin;
class GameCamera;
class BackGround;
class Botan;

class Game : public IGameObject
{
public:
	
	Game();
	~Game();

	bool Start();

	//更新処理
	

	void Update();

	void Render(RenderContext& rc);

	

public:
	LevelRender m_levelRender;
	Player* player = nullptr;
	Bannin* bannin = nullptr;
	GameCamera* m_GameCamera;
	BackGround* background = nullptr;
	Botan* botan = nullptr;
	GameClear* gameclear = nullptr;
	ModelRender m_modelRender;
	Vector3 m_position;
	SoundSource* gameBGM; //ゲーム中のBGM。

	FontRender m_fontRender;
	float m_timer = 0.0f;
	float g_timer = 0.0f;

	bool m_isSaveClearTime =false;

	int minit = 0;	//追加
};

