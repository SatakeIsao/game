#pragma once

class Player;
//�{�^���N���X�B
class Botan:public IGameObject
{
public:
	Botan();
	~Botan();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);
	bool Start();
	
	//�����o�ϐ��B
	ModelRender m_modelRender; //���f�������_�[�B
	Vector3 m_position; //���W�B
	Player* player; //�v���C���[�B
	Botan* botan; //�{�^���B
};

