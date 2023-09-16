#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Botan.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"

Game::Game()
{
	//�v���C���[�̃I�u�W�F�N�g�����B
	player = NewGO<Player>(0, "player");
	player->m_position = { -600.0f,0.0f,0.0f };

	//�Q�[���J�����̃I�u�W�F�N�g�����B
	m_GameCamera = NewGO<GameCamera>(0, "gamecamera");

	//�w�i�̃I�u�W�F�N�g�����B
	background = NewGO<BackGround>(0, "backGround");
	//background->m_position = { 0.0f,0.0f,0.0f };

	//�{�^���̃I�u�W�F�N�g�����B
	botan = NewGO<Botan>(0, "botan");
	botan->m_position = {600.0f,-20.0f,-200.0f };

	//�Q�[������BGM��ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/maou_game_dangeon15.wav");

	//�Q�[������BGM���Đ�����B
	gameBGM = NewGO<SoundSource>(1);
	gameBGM->Init(1);
	gameBGM->Play(true);
}

Game::~Game()
{
	//�v���C���[���폜����B
	DeleteGO(player);
	//�Q�[���J�������폜����B
	DeleteGO(m_GameCamera);
	//�Q�[������BGM���폜����B
	DeleteGO(gameBGM);
	//�w�i���폜����B
	DeleteGO(background);
}



//�X�V����
void Game::Update()
{

	Vector3 diff = botan->m_position - player->m_position;
	if (diff.Length() <= 70.0f)
	{
		NewGO<GameClear>(0, "gameclear");
		//���g���폜
		DeleteGO(this);
	}
	
}

void Game::Render(RenderContext& rc)
{

}
