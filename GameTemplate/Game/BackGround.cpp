#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/yakata.tkm");
	//静的物理オブジェクトを作成
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

BackGround::~BackGround()
{
	
}

void BackGround::Render(RenderContext& rc)
{
	//モデルを描画する
	m_modelRender.Draw(rc);
}