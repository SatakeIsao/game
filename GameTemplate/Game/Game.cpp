#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "Bannin.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Botan.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"

Game::Game()
{
	
		//for (m_timer += g_gameTime->GetFrameDeltaTime(); m_timer <= 60;) {

			//g_timer = m_timer;
			//m_timer = 0;

			//m_timer += g_gameTime->GetFrameDeltaTime();
	//	}
	//m_timer = 00;
	//g_timer += 1;
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

bool Game::Start()
{
	//�v���C���[�̃I�u�W�F�N�g�����B
	player = NewGO<Player>(0, "player");
	player->m_position = { -600.0f,0.0f,0.0f };

	//�Ԑl�̃I�u�W�F�N�g�����B
	//m_levelRender.Init("Assets/modelData/level.tkl",
	//	[&](LevelObjectData& objData)
	//	{
	//		if (objData.EqualObjectName(L"Bannin") == true)
	//		{
	//			//�Ԑl�̃I�u�W�F�N�g�����B
	//			bannin = NewGO<Bannin>(0, "bannin");
	//			//���W��ݒ�B
	//			bannin->SetPosition(objData.position);
	//			//��]��ݒ�B
	//			bannin->SetRotation(objData.rotation);
	//			//�傫����ݒ�B
	//			bannin->SetScale(objData.scale);
	//			return true;
	//		}
	//		return true;
	//	});

	bannin = NewGO<Bannin>(0, "bannin");
	bannin->m_position = { -600.0f,0.0f,0.0f };

	//�Q�[���J�����̃I�u�W�F�N�g�����B
	m_GameCamera = NewGO<GameCamera>(0, "gamecamera");

	//�w�i�̃I�u�W�F�N�g�����B
	background = NewGO<BackGround>(0, "backGround");

	//background->m_position = { 0.0f,0.0f,0.0f };

	//�{�^���̃I�u�W�F�N�g�����B
	botan = NewGO<Botan>(0, "botan");
	botan->m_position = { 600.0f,-20.0f,-200.0f };

	//�����蔻�����������B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//�Q�[������BGM��ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/maou_game_dangeon15.wav");

	//�Q�[������BGM���Đ�����B
	gameBGM = NewGO<SoundSource>(1);
	gameBGM->Init(1);
	gameBGM->Play(true);

	return true;
}





//�X�V����
void Game::Update()
{
	wchar_t wcsbuf[256];

	//int minit = 0;
	swprintf_s(wcsbuf, 256, L"%d:%d", int(minit), int(m_timer));
	
	//int minit = 0;
	float nowTime = m_timer;
	for (; nowTime >= 60.0f;) {
		nowTime -= 60.0f;
		m_timer = nowTime;	//�ǉ�
		minit++;
	}
	//for (m_timer = 0; m_timer <= 60; m_timer++) {
		//g_timer = m_timer;
	//}

	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(400.0f, 400.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(2.0f);
	//�t�H���g�̐F��ݒ�B
	m_fontRender.SetColor({ 255.0f,0.0f,0.0f,1.0f });

	//for (m_timer += g_gameTime->GetFrameDeltaTime(); m_timer <= 60;) {
		
		//g_timer = m_timer;
		//m_timer = 0;

		//m_timer += g_gameTime->GetFrameDeltaTime();
	//}
	//m_timer = 00;
	//g_timer += 1;
	//m_timer += g_gameTime->GetFrameDeltaTime();
	m_timer += g_gameTime->GetFrameDeltaTime(); //1f=1/60�b
	
	/*int minit = 0;
	float nowTime = g_timer;
	for (; nowTime >= 60.0f ;) {
		nowTime -= 60.0f;
		minit++;
	}*/

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
