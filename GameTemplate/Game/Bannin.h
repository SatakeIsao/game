#pragma once
class Bannin;

class Bannin : public IGameObject
{
public:
	//�Ԑl�̃X�e�[�g�B
	enum EnBanninState {
		enBanninState_Idle,			//�ҋ@�B
		enBanninState_Walk,			//�����B
		enBanninState_Run,			//����B
		enBanninState_Bark,			//�i����B
		enBanninState_Down,			//HP��0�B
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

	const Vector3& GetPosition() const
	{
		return m_position;
	}
	//<summary>
	//��������(�X�e�[�g)���ǂ������擾�B
	// </summary>
	//<returns>��������(�X�e�[�g)�Ȃ�true�B</returns>
	bool IsEnableMove() const
	{
		return m_banninState != enBanninState_Bark &&
			m_banninState != enBanninState_Down &&
			m_banninState != enBanninState_Clear;
	}
private:

	//�A�j���[�V�����C�x���g�p�̊֐��B
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	//�A�j���[�V����
	enum EnAnimationClip {
		enAnimationClip_Idle,		//�ҋ@�A�j���[�V�����B
		enAnimationClip_Walk,		//�����A�j���[�V�����B
		enAnimationClip_Run,        //����A�j���[�V�����B
		enAnimationClip_Bark,		//�i����A�j���[�V�����B
		enAnimationClip_Down,		//�_�E���A�j���[�V�����B
		enAnimationClip_Winner,		//�����A�j���[�V�����B
		enAnimationClip_Num,		//�A�j���[�V�����̐��B
	};

	void Move();
	void Bark();
	void PlayAnimation();

	AnimationClip m_animationClips[enAnimationClip_Num];
	ModelRender m_modelRender;
	Vector3 m_position; //���W�B
	EnBanninState m_banninState = enBanninState_Idle;
	bool m_isUnderBark = false; //�i���Ă���̂Ȃ�true�B
};

