#pragma once
class Bannin;

class Bannin : public IGameObject
{
public:

	Bannin();
	bool Start();
	void Update();

	void Render(RenderContext& rc);

	void Move();
	void PlayAnimation();
	ModelRender m_modelRender;
	Vector3 m_position; //ç¿ïWÅB
};

