#include "stdafx.h"
#include "Star.h"
#include "Player.h"
#include "GameClear.h"

//ColisionObject���g�p���������߁A�t�@�C�����C���N���[�h����B
#include"collision/CollisionObject.h"

Star::Star()
{


}

Star::~Star()
{

}

bool Star::Start()
{
	//���̃��f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/Star/Star2.tkm");

	m_player = FindGO<Player>("player");

	//���W��ݒ肷��B
	Vector3 position = m_position;
	
	m_modelRender.SetPosition(m_position);
	//�傫����ݒ肷��B
	m_modelRender.SetScale(1.0f, 1.0f, 1.0f);

	//�����蔻���L��������B
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0f,		//���a�B
		100.0f,		//�����B
		m_position  //���W�B
	);

	return true;
}

void Star::Update()
{
	//�G�`������̍X�V�����B
	m_modelRender.Update();

	//�v���C���[���灙�Ɍ������x�N�g�����v�Z�B
	Vector3 diff = m_player->m_position - m_position;
	//�x�N�g���̒�����120.0f��菬����������B
	if (diff.Length() <= 120.0f)
	{
		m_player->starCount += 1;
		//�Q�[���N���A�̃I�u�W�F�N�g�����B
		//NewGO<GameClear>(0, "gameclear");
		//���g���폜����B
		DeleteGO(this);
	}

}

void Star::Render(RenderContext& rc)
{
	//����`�悷��B
	m_modelRender.Draw(rc);
}