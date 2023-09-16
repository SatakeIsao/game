#pragma once
class Game;

class Player : public IGameObject
{
public:
	//////////////////////////////////////
	// �����o�֐��B
	//////////////////////////////////////
	Player();
	~Player();
	bool Start();
	void Update();
	
	void Render(RenderContext& rc);

	
	
	void Rotation();
	//�X�e�[�g�Ǘ��B
	void ManageState();
	//////////////////////////////////////
	// �����o�ϐ��B
	//////////////////////////////////////
	enum EnAnimationClip {
		enAnimationClip_idle,	//�ҋ@�A�j���[�V����
		enAnimationClip_walk,	//�����A�j���[�V����
		enAnimationClip_Num,	//�A�j���[�V�����N���b�v
	};

	void Move();
	void PlayAnimation();
	ModelRender m_modelRender;
	Vector3 m_position; //���W
	CharacterController m_charaCon;	//�L�����N�^�[�R���g���[���[
	Vector3 m_moveSpeed; //�ړ����x
	Quaternion m_rotation;	//�N�H�[�^�j�I���B
	PointLight m_pointLight; //�|�C���g���C�g�B
	int playerState = 0;	//�v���C���[�̃X�e�[�g(���)��\���ϐ��B
	AnimationClip m_animClips[enAnimationClip_Num];
	Player* m_player = nullptr;
};


