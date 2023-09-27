#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�
	m_toCameraPos.Set(10.0f, 50.0f, 0.0f);
	
	//�v���C���[�̃C���X�^���X��T��
	m_player = FindGO<Player>("player");

	//�΂˃J�����̏�����
	//m_springCamera.Init(
		//*g_camera3D,	//�΂˃J�����̏������s���J�������w��B
		//1000.0f,		//�J�����̈ړ����x�̍ő�l�B
		//true,			//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s���B
		//5.0f			//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��R������ture�̎��ɗL���ɂȂ�B

	//);

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ�
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(30000.0f);

	return true;
}

void GameCamera::Update()
{
	//�J�������X�V
	//�����_���v�Z����B
	Vector3 target = m_player->m_position;
	//�����_ �v���C���[�̍��W�ɐݒ�
	target.y += 30.0f;
	//target.z += 30.0f;
	
	//���_���v�Z����B
	Vector3 toCameraPosOld = m_player->m_position;
	toCameraPosOld.y += 30.0f;
	//�p�b�h�̓��͂��g���ăJ��������
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//Y������̉�]
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	qRot.Apply(m_toCameraPos);

	//X������̉�]
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY,m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX , 1.3f * y);
	qRot.Apply(m_toCameraPos);

	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ遨�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ�������
	//Vector3 toPosDir =m_player->m_position;//m_toCameraPos;
	//toPosDir.Normalize();
	//if (toPosDir.y < -0.2f) {
	//	//�J���������������
	//	m_toCameraPos = toCameraPosOld;
	//}
	//else if (toPosDir.y > 0.9f) {
	//	//�J����������������
	//	m_toCameraPos = toCameraPosOld;
	//}

	//���_���v�Z����B
	Vector3 pos = target + m_toCameraPos;

	//�΂˃J�����ɒ����_�Ǝ��_��ݒ�
	//m_springCamera.SetPosition(pos);
	//m_springCamera.SetTarget(target);

	//���C���J�����ɒ����_�Ǝ��_��ݒ�
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//�J�����̍X�V
	g_camera3D->Update();
	//m_springCamera.Update();
}