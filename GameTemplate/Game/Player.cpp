#include "stdafx.h"
#include "Player.h"


Player::Player() 
{

}

Player::~Player()
{

}

bool Player::Start()
{

	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animClips[enAnimationClip_idle].Load("Assets/animData/idle.tka");
	m_animClips[enAnimationClip_walk].Load("Assets/animData/walk.tka");
	//���[�v�t���O��ݒ肷��B
	m_animClips[enAnimationClip_idle].SetLoopFlag(true);
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/unityChan.tkm",m_animClips,enAnimationClip_Num,enModelUpAxisY);

	m_pointLight.Init();
	m_pointLight.SetPosition(m_position);
	m_pointLight.SetColor(Vector3(10.0f, 10.0f, 10.0f));
	m_pointLight.SetAffectPowParam(0.7f);
	m_pointLight.SetRange(100.0f);

	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(25.0f, 75.0f, m_position);

	return true;
}

void Player::Update()
{
	//�ړ������B
	Move();

	//��]�����B
	Rotation();
	//�X�e�[�g�Ǘ��B
	ManageState();
	//�A�j���[�V�������Đ�����B
	PlayAnimation();

	Vector3 pointLightPosition = m_position;
	pointLightPosition.y += 50.0f;
	m_pointLight.SetPosition(pointLightPosition);
	m_pointLight.Update();

	//���f���̍X�V�B
	m_modelRender.Update();
}

void Player::Move()
{
	//xz�̈ړ����x��0.0f�ɂ���B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ��B
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�120.0f����Z�B
	right *= stickL.x * 120.0f;
	forward *= stickL.y * 120.0f;

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	m_moveSpeed += right + forward;

	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	m_position = m_charaCon.Execute(m_moveSpeed, 1.0f / 60.0f);
	//���W��ݒ�B
	m_modelRender.SetPosition(m_position);

}




void Player::Rotation()
{
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//�G�`������ɉ�]��������B
		m_modelRender.SetRotation(m_rotation);
	}
}


//�X�e�[�g�Ǘ��B
void Player::ManageState()
{
	//�n�ʂɕt���Ă�����B
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�X�e�[�g��1(����)�ɂ���B
		playerState = 1;
	}
	//x��z�̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B
	else
	{
		//�X�e�[�g��0(�ҋ@)�ɂ���B
		playerState = 0;
	}
}




void Player::PlayAnimation()
{
	//switch���B
	switch (playerState) {
		//�v���C���[�X�e�[�g��0(�ҋ@)��������B
	case 0:
		//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_idle);
		break;

		//�v���C���[�X�e�[�g��1(����)��������B
	case 1:
		//�����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_walk);
		break;
	}
}

void Player::Render(RenderContext& rc)
{
	//���f���̕`��B
	m_modelRender.Draw(rc);
}