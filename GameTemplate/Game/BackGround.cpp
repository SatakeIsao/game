#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	//���f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/yakata.tkm");
	//�ÓI�����I�u�W�F�N�g���쐬
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

BackGround::~BackGround()
{
	
}

void BackGround::Render(RenderContext& rc)
{
	//���f����`�悷��
	m_modelRender.Draw(rc);
}