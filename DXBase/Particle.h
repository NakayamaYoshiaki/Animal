#pragma once

#include "billboard.h"
#include "MyMath.h"

// �p�[�e�B�N���X�e�[�^�X�\����
typedef struct 
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSpd;
	D3DXVECTOR3 vAngle;
	D3DXVECTOR3 vSize;

	KEY					BezierKey[4];		// �x�W�G�p����_
	KEY					HermiteKey[2];		// �G���~�[�g�p
	KEY					HermiteVecKey[2];	// �G���~�[�g�p�x�N�g��

	int			nLife;		// ���ł܂ł̎���
	int			nType;		// ���

}MYPARTICLE;

class CParticle :
	public CBillboard
{
protected:
	MYPARTICLE m_Particle;

private:

public:
	CParticle(void);
	virtual ~CParticle(void);

	void Release();
	void InitializeParticle(){};
	virtual void Update(){};
};

