#pragma once
#include "sound/SoundSource.h"

//�^�C�g��
class Title:public IGameObject
{
public:
	Title();
	~Title();

	//�X�V�����B
	void Update();
	//�`��֐��B
	void Render(RenderContext& rc);
	
	//�X�v���C�g�����_�[
	SpriteRender m_spriteRender;
	SoundSource* titleBGM; //�^�C�g����BGM�B
};

