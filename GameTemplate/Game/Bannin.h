#pragma once
class Bannin;

class Bannin : public IGameObject
{
public:

	Bannin();
	bool Start();
	void Update();

	void Render(RenderContext& rc);

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	const Vector3& GetPosition() const
	{
		return m_position;
	}

	void Move();
	void PlayAnimation();
	ModelRender m_modelRender;
	Vector3 m_position; //ç¿ïWÅB
};

