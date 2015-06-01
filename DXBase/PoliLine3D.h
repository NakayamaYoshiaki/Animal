#pragma once

#include "object3d.h"
#include "Billboard.h"
#include "MyMath.h"
#include "PoliLine.h"

class CPoliLine3D :
	public CObject3D
{
protected:
	CPoliLine*	m_pPoliLine;		// �|�����C���Ɏg�p����f�[�^�Q
	D3DXVECTOR3 m_vCameraVec[LINEPOINT_MAX];	// �J�����ւ̃x�N�g��
	D3DXVECTOR3 m_vDiffVec[LINEPOINT_MAX];		// �L�������

public:
	CPoliLine3D(void);
	virtual ~CPoliLine3D(void);

	CPoliLine3D* Create(D3DXVECTOR3 vInitPos, D3DXVECTOR3 vDestPos, float fWidth);
	void Initialize();

	virtual void Update(){};
	virtual void Draw(){};
	virtual void Release(){};
	//void DrawSetUp();
	//void DrawEnd();

	//void CalcLine();		// ���C���v�Z
	//void CalcDirVec();		// �i�s�����v�Z
	//void CalcCameraVec();	// �J�����ւ̃x�N�g���v�Z
	//void CalcDiffVec();		// �g�U�����v�Z
	//void CalcSquare();		// �l�p�v�Z

	//// �Z�b�^�[
	//void SetPosLine();

};

