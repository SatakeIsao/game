#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Bannin.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Botan.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"

bool Game::Start()
{

	return true;
}

Game::Game()
{
	//�v���C���[�̃I�u�W�F�N�g�����B
	player = NewGO<Player>(0, "player");
	player->m_position = { -600.0f,0.0f,0.0f };

	//�Ԑl�̃I�u�W�F�N�g�����B
	//m_levelRender.Init("Assets/level3D/level.tkl",
		//[&](LevelObjectData& objData)
		//{
			//if (objData.EqualObjectName(L"bannin") == true)
			//{
				//�Ԑl�̃I�u�W�F�N�g�����B
				//bannin = NewGO<Bannin>(0, "bannin");
				//���W��ݒ�B
				//bannin->SetPosition(objData.position);
				//return true;
			//}
			//return true;
		//});

	//bannin = NewGO<Bannin>(0, "bannin");
	//bannin->m_position = { 500.0f,0.0f,-100.0f };

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
	//�Ԑl���폜����B
	DeleteGO(bannin);
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
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d�b�o��!!", int(m_timer));
	


	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(400.0f, 400.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(2.0f);
	//�t�H���g�̐F��ݒ�B
	m_fontRender.SetColor({ 255.0f,0.0f,0.0f,1.0f });

	m_timer += g_gameTime->GetFrameDeltaTime();


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
	//�t�H���g��`�悷��B
	m_fontRender.Draw(rc);
}
