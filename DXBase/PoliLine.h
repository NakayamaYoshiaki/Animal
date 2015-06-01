#pragma once

#include "objbase.h"
#include "MyMath.h"


#define LINEPOINT_MAX (10)		// ���ԓ_�̐�
// #define FVF_DVERTEX		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


struct POLIVERTEX
{
	int		m_nTimer;
	float	m_fRate;
	KEY		m_HKey[2];		// �G���~�[�g�n�_�I�_		
	KEY		m_HVecKey[2];	// �G���~�[�g�n�_�I�_�x�N�g��
};

// #define D3DFVF_POLIVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class CPoliLine :
	public CObjBase
{
protected:
	

public:
	CBoard2D	m_Board;		// �{�[�h���i�e�N�X�`�����̂ݎg���j
	float		m_fLineWidth;	// ���C����
	float		m_fRate;		// �ړ��䗦
	D3DXVECTOR3 m_vInitPos;		// �n�_
	D3DXVECTOR3 m_vDestPos;		// �I�_
	D3DXVECTOR3	m_vLinePos[LINEPOINT_MAX];		// ���ԓ_
	
	D3DXVECTOR3 m_vDirVec[LINEPOINT_MAX];		// �i�s�����x�N�g��
	D3DXVECTOR3 m_vCameraVec[LINEPOINT_MAX];	// �J�����ւ̃x�N�g��
	D3DXVECTOR3 m_vDiffVec[LINEPOINT_MAX];		// �L�������

	POLIVERTEX	m_Point[LINEPOINT_MAX * 2];	// �|�����C���X�N�G�A
	DVERTEX		m_verWk[LINEPOINT_MAX * 2];

	// �֐�
	CPoliLine(void);
	virtual ~CPoliLine(void);

	CPoliLine* Create(int nTexNum, D3DXVECTOR3 vInitPos, D3DXVECTOR3 vDestPos, float fWidth);
	void Initialize(int nImage);

	void Update();
	void Draw();
	void DrawSetUp();
	void DrawEnd();

	void CalcLine();		// ���C���v�Z
	void CalcDirVec();		// �i�s�����v�Z
	void CalcCameraVec();	// �J�����ւ̃x�N�g���v�Z
	void CalcDiffVec();		// �g�U�����v�Z
	void CalcSquare();		// �l�p�v�Z

	// �Z�b�^�[
	void SetPosLine();

};

