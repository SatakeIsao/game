#pragma once
class GameClear :public IGameObject
{
public:
	GameClear();
	~GameClear();
	//�X�V����
	void Update();
	//�`�揈��
	void Render(RenderContext& rc);

	//�����o�ϐ��B
	SpriteRender m_spriteRender; //�X�v���C�g�����_�[
};
