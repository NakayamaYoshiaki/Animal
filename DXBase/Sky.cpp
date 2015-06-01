#include "Sky.h"


CSky::CSky(void)
{
}

CSky::~CSky(void)
{
	
}

//---------------------------------------------
// ����
// --------------------------------------------
CSky* CSky::Create(CMesh* pMesh)
{
	CSky* pSky;
	pSky = new CSky();

	// �I�u�W�F�N�g�Ƀ��b�V���Z�b�g
	pSky->SetMesh(pMesh);

	// ����������
	pSky->Initialize();

	return pSky;
}

//------------------------------------------------
// ����������
//-------------------------------------------------
void CSky::Initialize(void)
{
	// �X�e�[�^�X������
	m_vPos.x = m_world._41;
	m_vPos.y = m_world._42;
	m_vPos.z = m_world._43;

	m_vLocalVec[0] = D3DXVECTOR3(m_world._11, m_world._12, m_world._13);
	m_vLocalVec[1] = D3DXVECTOR3(m_world._21, m_world._22, m_world._23);
	m_vLocalVec[2] = D3DXVECTOR3(m_world._31, m_world._32, m_world._33);

	//m_vSpeed.y = 0.2;
}

