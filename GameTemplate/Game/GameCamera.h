#pragma once

#include "camera/SpringCamera.h"
//�N���X�錾�B
class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	
	Player* m_player; //�v���C���[�B
	Vector3 m_toCameraPos; //�����_���王�_�Ɍ������x�N�g��
	Vector3 target;
	SpringCamera m_springCamera;	//�΂˃J�����B
};

