#pragma once
#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class BackGround;
class Botan;
class Game : public IGameObject
{
public:
	
	Game();
	~Game();

	bool Start();

	//�X�V����
	

	void Update();

	void Render(RenderContext& rc);

private:
	Player* player = nullptr;
	GameCamera* m_GameCamera;
	BackGround* background = nullptr;
	Botan* botan = nullptr;
	ModelRender m_modelRender;
	Vector3 m_position;
	SoundSource* gameBGM; //�Q�[������BGM�B

	FontRender m_fontRender;
	float m_timer = 0.0f;
};

