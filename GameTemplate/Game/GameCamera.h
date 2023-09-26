#pragma once

#include "camera/SpringCamera.h"
//クラス宣言。
class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	
	Player* m_player; //プレイヤー。
	Vector3 m_toCameraPos; //注視点から視点に向かうベクトル
	Vector3 target;
	SpringCamera m_springCamera;	//ばねカメラ。
};

