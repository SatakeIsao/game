#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{
	
}

bool BackGround::Start()
{
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/yakata.tkm");
	//座標を設定する。
	m_modelRender.SetPosition(m_position);
	//大きさを設定する。
	m_modelRender.SetScale(m_scale);

	
	//モデルを更新する。
	m_modelRender.Update();
	//静的物理オブジェクトを作成
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	
	return true;
}

void BackGround::Update()
{
	m_modelRender.Update();
}

void BackGround::Render(RenderContext& rc)
{
	//モデルを描画する
	m_modelRender.Draw(rc);
}