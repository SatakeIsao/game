#pragma once

//背景。
class BackGround :public IGameObject

{
public:
	BackGround();
	~BackGround();
	bool Start();

	void Update();
	void Render(RenderContext& rc);


private:
	Vector3 m_position;
	ModelRender m_modelRender;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rotation;
	PhysicsStaticObject physicsStaticObject; //静的オブジェクトを保持させる。
	int m_lightNumber = 0;
};

