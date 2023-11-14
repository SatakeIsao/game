#include "stdafx.h"
#include "Bannin.h"

#include "Game.h"
#include "Player.h"
#include "GameClear.h"
#include "GameOver.h"

//ColisionObject���g�p���������߁A�t�@�C�����C���N���[�h����B
#include"collision/CollisionObject.h"

Bannin::Bannin()
{

}

bool Bannin::Start()
{
	//�A�j���[�V������ǂݍ��ށB
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/SkeletonIdle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/SkeletonRun.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	//m_animationClips[enAnimationClip_Bark].Load("Assets/modelData/Mutant.fbm/bark2.tka");
	//m_animationClips[enAnimationClip_Bark].SetLoopFlag(false);
	
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/Bannin2.fbm/Skeleton.tkm",m_animationClips,enAnimationClip_Num);
	//m_modelRender.Init("Assets/modelData/Bannin2.fbm/Skeleton.tkm");
	//m_modelRender.Update();
	
	//���W��ݒ肷��B
	Vector3 position = m_position;
	position.y = 2.5f;
	m_modelRender.SetPosition(m_position);
	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rotation);
	//�傫����ݒ肷��B
	m_modelRender.SetScale(10.0f, 10.0f, 10.0f);

	//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
	//m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		//OnAnimationEvent(clipName, eventName);
		//});

	


	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0f,		//���a�B
		100.0f,		//�����B
		m_position  //���W�B
	);

	m_player = FindGO<Player>("player");

	//�������������B
	srand((unsigned)time(NULL));
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	return true;
}

void Bannin::Update()
{
	//�ǐՏ����B
	Chase();
	//��]�����B
	Rotation();
	//�����蔻��B
	Collision();
	//�A�j���[�V�����̍Đ��B
	PlayAnimation();
	//�X�e�[�g�̑J�ڏ����B
	ManageState();

	//���f���̍X�V�B
	m_modelRender.Update();


	////�Ԑl�̖i����p�̃R���W�����擾����B
	//const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_run");
	////�R���W�����̔z���for���ŉ񂷁B
	//for (auto collision : collisions)
	//{
	//	//�R���W�����ƃL�����R�����Փ˂�����B
	//	if (collision->IsHit(m_charaCon))
	//	{

	//		//�Q�[���I�[�o�[
	//		NewGO<GameOver>(0, "gameover");
	//		//���g���폜����B
	//		DeleteGO(this);



	//		//���ʉ����Đ�����B
	//	}
	//}


	////�v���C���[���灙�Ɍ������x�N�g�����v�Z�B
	//Vector3 diff = m_player->m_position - m_position;
	////�x�N�g���̒�����120.0f��菬����������B
	//if (diff.Length() <= 120.0f)
	//{
	//	//m_player->starCount += 1;
	//	//�Q�[���N���A�̃I�u�W�F�N�g�����B
	//	NewGO<GameOver>(0, "gameover");
	//	//���g���폜����B
	//	DeleteGO(this);
	//}
}

void Bannin::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotationY(-angle);

	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rotation);

	//�v���C���[�̑O�x�N�g�����v�Z����B
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Bannin::Chase()
{
	//�ǐՃX�e�[�g�łȂ��Ȃ�A�ǐՏ����͂��Ȃ��B
	if (m_banninState != enBanninState_Chase)
	{
		return;
	}

	//�Ԑl���ړ�������B
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//�n�ʂɂ����B
		//�d�͂�0�ɂ���B
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;
	//�����������f���̍��W���グ��B
	modelPosition.y += 2.5f;
	//���W��ݒ肷��B
	m_modelRender.SetPosition(modelPosition);
}

void Bannin::Collision()
{
	//��_���[�W�A���邢�̓_�E���X�e�[�g�̎��ɂ́B
	//�����蔻�菈�������Ȃ��B
	//if (m_banninState == enBanninState_ReceiveDamage || m_banninState == enBanninState_Down)
	//{
	//	return;
	//}

	////�Ԑl�̖i����p�̃R���W�����擾����B
	//const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_run");
	////�R���W�����̔z���for���ŉ񂷁B
	//for (auto collision : collisions)
	//{
	//	//�R���W�����ƃL�����R�����Փ˂�����B
	//	if (collision->IsHit(m_charaCon))
	//	{
	//		
	//		//�Q�[���I�[�o�[
	//		NewGO<GameOver>(0, "gameover");
	//		//���g���폜����B
	//		DeleteGO(this);

	//

	//		//���ʉ����Đ�����B
	//	}
	//}


}



void Bannin::Move()
{
	

}

void Bannin::Bark()
{
	//�i���Ȃ��Ȃ珈�����Ȃ��B
	//if (m_banninState != enBanninState_Bark)
	//{
	//	return;
	//}

	////�i���Ă���΁B
	//if (m_isUnderBark == true)
	//{
	//	//�i����p�̃R���W�������쐬����B
	//	MakeBarkCollision();
	//}
}

//const bool Bannin::SearchPoint() const
//{
	//�ȉ����[�v

	////�ڕW�Ƃ���|�C���g�̍��W���猻�݂̍��W�������āA�����x�N�g�������߂�     
	//Vector3 diff = m_point->s_poition - m_position;
	////���������ȓ��Ȃ�ړI�n�Ƃ���|�C���g��ς���
	//if (diff.Length() <= 20.0f) {

	//	//���ړI�n�Ƃ��Ă���|�C���g���z��̍Ō�̗v�f�Ȃ�
	//  //��ԍŏ��̃|�C���g��ړI�n�Ƃ���
	//	if (m_point->s_number == m_poinstList.size()) {
	//		m_point = m_pointList[0];
	//	}

	//	//�����łȂ��Ȃ�z��̎��̗v�f�̃|�C���g��ړI�n�Ƃ���
	//	else {
	//		m_point = m_pointList[m_point->s_number];
	//	}
	//}

	////�ڕW�Ƃ���|�C���g�̍��W���猻�݂̍��W�������āA�����x�N�g�������߂� 
	//Vector3 moveSpeed = m_point->s_position - m_position;
	////���K������
	//moveSpeed.Normalize();
	////�K���ɃX�J���[��������
	//moveSpeed *= 3.0f;
	////���W�ɉ��Z����
	//m_position += moveSpeed;
//}

const bool Bannin::SearchPlayer() const
{
	//�Ԑl����v���C���[�Ɍ������x�N�g�������߂�B
	Vector3 diff = m_player->GetPosition() - m_position;

	//�v���C���[�ɂ�����x�߂�������B
	if (diff.LengthSq() <= 700.0 * 700.0f)
	{
		//�Ԑl����v���C���[�Ɍ������x�N�g���𐳓���(�傫�����P)����B
		diff.Normalize();
		//�Ԑl�̐��ʂ̃x�N�g���ƁA�Ԑl����v���C���[�Ɍ������x�N�g���́B
		//����(cos��)�����߂�B
		float cos = m_forward.Dot(diff);
		//����(cos��)����p�x(��)�����߂�B
		float angle = acosf(cos);
		//�p�x(��)��120��(����p)��菬������΁B
		if (angle <= (Math::PI / 180.0f) * 120.0f)
		{
			//�v���C���[���������I
			return true;
		}
	}
	//�v���C���[���������Ȃ������B
	return false;
}



void Bannin::MakePushLeverCollision()
{
	////�R���W�����I�u�W�F�N�g���쐬����B
	//CollisionObject* collisionObject = NewGO<CollisionObject>(0);
	//Vector3 collisionPosition = m_position;

	////���W��Ԑl�̏����O�ɐݒ肷��B
	//collisionPosition += m_forward * 50.0f;
	////����̃R���W�������쐬����B
	//collisionObject->CreateSphere(collisionPosition, //���W�B
	//	Quaternion::Identity, //��]�B
	//	70.0f); //���̑傫��(���a)�B
	//	//���O��t����B
	//collisionObject->SetName("player_lever");
}

void Bannin::ProcessCommonStateTransition()
{
	//�e�^�C�}�[���������B
	//�ҋ@���ԂƒǐՎ��Ԃ𐧌����邽�߁B
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;

	//�Ԑl����v���C���[�Ɍ������x�N�g�����v�Z����B
	Vector3 diff = m_player->GetPosition() - m_position;

	//�ړ����x��ݒ肷��B
	m_moveSpeed = diff * 0.50f;
	
	//�v���C���[����������B
	if (SearchPlayer() == true)
	{
		//�ǐՃX�e�[�g�ɑJ�ڂ���B
		m_banninState = enBanninState_Chase;
		return;
	}
	//�v���C���[���������Ȃ���΁B
	else
	{
		//�ҋ@�X�e�[�g�ɑJ�ڂ���B
		m_banninState = enBanninState_Idle;
		return;
	}
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
	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
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
	////�i����X�e�[�g�̎��B
	//case enBanninState_Bark:
	//	//�i����X�e�[�g�̃X�e�[�g�J�ڏ����B
	//	ProcessBarkStateTransition();
	//	break;
	}
}



void Bannin::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//�L�[�̖��O���ubark_start�v�̎��B
	//if (wcscmp(eventName, L"bark_start") == 0)
	//{
	//	//�i���Ă���
	//	m_isUnderBark = true;
	//}
	////�L�[�̖��O���ubark_end�v�̎��B
	//else if (wcscmp(eventName, L"bark_end") == 0)
	//{
	//	//�i����̂��I����B
	//	m_isUnderBark = false;
	//}

}

void Bannin::PlayAnimation()
{
	m_modelRender.SetAnimationSpeed(1.0f);
	switch (m_banninState)
	{
		//�ҋ@�X�e�[�g�̎��B
	case enBanninState_Idle:
		//�ҋ@�A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.5f);
		break;
		//�ǐՃX�e�[�g�̎��B
	case enBanninState_Chase:
		//�ǐՃA�j���[�V�������Đ��B
		m_modelRender.SetAnimationSpeed(1.2f);
		//����A�j���[�V�������Đ��B
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
		//�i����X�e�[�g�̎��B
	//case enBanninState_Bark:
		//�i����A�j���[�V�������Đ��B
		//m_modelRender.PlayAnimation(enAnimationClip_Bark, 0.1f);
		//break;
	default:
		break;
	}
}

void Bannin::Render(RenderContext& rc)
{
	//���f���̕`��
	m_modelRender.Draw(rc);
}