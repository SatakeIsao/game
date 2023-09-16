#pragma once

//îwåiÅB
class BackGround :public IGameObject

{
public:
	BackGround();
	~BackGround();

	void Render(RenderContext& rc);

	Vector3 m_position;
private:
	ModelRender m_modelRender;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rotation;
	PhysicsStaticObject m_physicsStaticObject;
	int m_lightNumber = 0;
};

