#include "Particle.h"

#define DEFO_LIFE 300
CParticle::CParticle()
{
	m_Particle.vPos = D3DXVECTOR3(0,0,0);
	m_Particle.vSpd = D3DXVECTOR3(0,0,0);
	m_Particle.vAngle = D3DXVECTOR3(0,0,0);
	m_Particle.vSize = D3DXVECTOR3(0,0,0);

	m_Particle.BezierKey[4];		// �x�W�G�p����_
	m_Particle.HermiteKey[2];		// �G���~�[�g�p
	m_Particle.HermiteVecKey[2];	// �G���~�[�g�p�x�N�g��
	m_Particle.nLife = DEFO_LIFE;		// ���ł܂ł̎���
	m_Particle.nType = 0;		// ���
}


CParticle::~CParticle(void)
{
}

void CParticle::Release()
{

}

