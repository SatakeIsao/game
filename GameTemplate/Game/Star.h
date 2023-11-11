#pragma once

class Player;
class Star : public IGameObject
{
public:
	Star();
	~Star();
	bool Start();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);

	//�����o�ϐ��B
	ModelRender m_modelRender; //���f�������_�[�B
	Vector3 m_position;        //���W�B
	Vector3 m_firstPosition;   //�ŏ��̍��W�B
	Player* m_player;          //�v���C���[�B
	CharacterController	m_charaCon; //�L�����R���B
};

