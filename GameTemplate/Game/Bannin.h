#pragma once
class Player;

class Bannin : public IGameObject
{
public:
	//�Ԑl�̃X�e�[�g�B
	enum EnBanninState {
		enBanninState_Idle,			//�ҋ@�B
		enBanninState_Walk,			//�����B
		enBanninState_Run,			//����B
		enBanninState_Bark,			//�i����B
		enBanninState_Chase,		//�ǐՁB
		enBanninState_Down,			//HP��0�B  
		enBanninState_ReceiveDamage,  //��_���[�W�B
		enBanninState_Clear		    //�N���A�[�B
	};
public:
	Bannin();
	bool Start();
	void Update();

	void Render(RenderContext& rc);

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	const Vector3& GetPosition() const
	{
		return m_position;
	}


	//HP��ݒ肷��B
	void SetHP(const int hp)
	{
		m_hp = hp;
	}



	//<summary>
	//��������(�X�e�[�g)���ǂ������擾�B
	// </summary>
	//<returns>��������(�X�e�[�g)�Ȃ�true�B</returns>
	bool IsEnableMove() const
	{
		return m_banninState != enBanninState_Bark &&
			m_banninState != enBanninState_Chase &&
			m_banninState != enBanninState_Down &&
			m_banninState != enBanninState_Clear;
	}

	//�A�j���[�V�����C�x���g�p�̊֐��B
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	//�A�j���[�V����
	enum EnAnimationClip {
		enAnimationClip_Idle,		//�ҋ@�A�j���[�V�����B
		enAnimationClip_Walk,		//�����A�j���[�V�����B
		enAnimationClip_Run,        //����A�j���[�V�����B
		enAnimationClip_Bark,		//�i����A�j���[�V�����B
		enAnimationClip_Num,		//�A�j���[�V�����̐��B
	};
	void Chase(); //�ǐՏ���
	void Rotation(); //��]�����B
	void Collision(); //�v���C���[�Ƃ̓����蔻��
	//const bool SearchPoint() const;
	const bool SearchPlayer() const; //�v���C���[��T������B
									 //�v���C���[������������true�B

	void MakePushLeverCollision(); //�����蔻��R���W�������쐬����B
	void ProcessCommonStateTransition(); //���ʂ̃X�e�[�g�̑J�ڏ����B
	void ProcessIdleStateTransition(); //�ҋ@�X�e�[�g�̑J�ڏ����B
	void ProcessRunStateTransition();   //����X�e�[�g�̑J�ڏ����B
	void ProcessChaseStateTransition();  //�ǐՃX�e�[�g�̑J�ڏ����B
	void ProcessBarkStateTransition();  //�i����X�e�[�g�̑J�ڏ����B

	void Move();
	void Bark();
	void PlayAnimation();
	void ManageState();

	
	AnimationClip m_animationClips[enAnimationClip_Num];
	ModelRender m_modelRender;
	Vector3 m_position; //���W�B
	Vector3 m_scale = Vector3::One; //�傫��
	Vector3 m_forward = Vector3::AxisZ; //�v���C���[�̐��ʃx�N�g���B
	Vector3 m_moveSpeed; //�ړ����x�B
	Quaternion m_rotation; //��]�B
	CharacterController	m_charaCon; //�L�����R���B
	EnBanninState m_banninState = enBanninState_Idle;
	bool m_isUnderBark = false; //�i���Ă���̂Ȃ�true�B
	int m_hp = 0;
	Player* m_player = nullptr; //�v���C���[�B
	float m_chaseTimer = 0.0f; //�ǐՃ^�C�}�[�B
	float m_idleTimer = 0.0f; //�ҋ@�^�C�}�[�B
};

