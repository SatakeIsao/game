#include "stdafx.h"
#include "Bannin.h"

#include "Game.h"
#include "Player.h"

//ColisionObject���g�p���������߁A�t�@�C�����C���N���[�h����B
#include"collision/CollisionObject.h"
Bannin::Bannin()
{

}

bool Bannin::Start()
{
	//�A�j���[�V������ǂݍ��ށB
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/bannin/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/bannin/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Bark].Load("Assets/animData/bannin/bark.tka");
	m_animationClips[enAnimationClip_Bark].SetLoopFlag(false);
	
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/Kemono.tks.tkm");
	//m_modelRender.SetScale(0.3f, 0.3f, 0.3f);

	//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	//���W��ݒ肷��B

	//�傫����ݒ肷��B
	m_modelRender.SetScale(m_scale);


	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0f,		//���a�B
		100.0f,		//�����B
		m_position  //���W�B
	);



	return true;


}

void Bannin::Update()
{
	//�ǐՏ����B
	Chase();
	//�����蔻��B
	Collision();
}



void Bannin::Chase()
{
	//�ǐՃX�e�[�g�łȂ��Ȃ�A�ǐՏ����͂��Ȃ��B
	if (m_banninState != enBanninState_Chase)
	{
		return;
	}
}

void Bannin::Collision()
{
	//��_���[�W�A���邢�̓_�E���X�e�[�g�̎��ɂ́B
	//�����蔻�菈�������Ȃ��B
	if (m_banninState == enBanninState_ReceiveDamage || m_banninState == enBanninState_Down)
	{
		return;
	}

	//�Ԑl�̖i����p�̃R���W�����擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("Bannin_balk");
	//�R���W�����̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_charaCon))
		{
			//HP��1���炷
			m_hp -= 1;

			//HP��0����Ȃ�B
			if (m_hp > 0)
			{
				//��_���[�W�X�e�[�g�ɑJ�ڂ���B
				m_banninState - enBanninState_ReceiveDamage;
			}
			//HP��0�Ȃ�B
			else if (m_hp == 0)
			{
				//�_�E���X�e�[�g�ɑJ�ڂ���B
				m_banninState = enBanninState_Down;
			}

			//���ʉ����Đ�����B
		}
	}
}



void Bannin::Move()
{
	m_modelRender.SetPosition(m_position); //���W��ݒ�B
}

void Bannin::Bark()
{
	//�i���Ȃ��Ȃ珈�����Ȃ��B
	if (m_banninState != enBanninState_Bark)
	{
		return;
	}

	//�i���Ă���΁B
	if (m_isUnderBark == true)
	{
		//�i����p�̃R���W�������쐬����B
		MakeBarkCollision();
	}
}


const bool Bannin::SearchPlayer() const
{
	return false;
}

void Bannin::PlayAnimation()
{

}

void Bannin::MakeBarkCollision()
{

}

void Bannin::ProcessCommonStateTransition()
{
	
}

void Bannin::ProcessIdleStateTransition() //�ҋ@�X�e�[�g�B
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//�ҋ@���Ԃ�������x�o�߂�����B
	if (m_idleTimer >= 0.9f)
	{
		//���̃X�e�[�g�֑J�ڂ���B
		ProcessCommonStateTransition();
	}
}

void Bannin::ProcessRunStateTransition() //����X�e�[�g�B
{
	//���̃X�e�[�g�֑J�ڂ���B
	ProcessCommonStateTransition();
}

void Bannin::ProcessChaseStateTransition()
{
	//�ǐՎ��Ԃ�������x�o�߂�����B
	if (m_chaseTimer >= 0.8f)
	{
		//���̃X�e�[�g�֑J�ڂ���B
		ProcessCommonStateTransition();
	}
}

void Bannin::ProcessBarkStateTransition()
{

}

void Bannin::ManageState()
{
	switch (m_banninState)
	{
	//�ҋ@�X�e�[�g�̎��B
	case enBanninState_Idle:
		//�ҋ@�X�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessIdleStateTransition();
		break;
	//�ǐՃX�e�[�g�̎��B
	case enBanninState_Chase:
		//�ǐՃX�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessChaseStateTransition();
		break;
	//�i����X�e�[�g�̎��B
	case enBanninState_Bark:
		//�i����X�e�[�g�̃X�e�[�g�J�ڏ����B
		ProcessBarkStateTransition();
		break;
	}
}

void Bannin::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//�L�[�̖��O���ubark_start�v�̎��B
	if (wcscmp(eventName, L"bark_start") == 0)
	{
		//�i���Ă���
		m_isUnderBark = true;
	}
	//�L�[�̖��O���ubark_end�v�̎��B
	else if (wcscmp(eventName, L"bark_end") == 0)
	{
		//�i����̂��I����B
		m_isUnderBark = false;
	}

}

void Bannin::Render(RenderContext& rc)
{
	//���f���̕`��
	m_modelRender.Draw(rc);
}