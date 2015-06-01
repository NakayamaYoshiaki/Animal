#pragma once
#include "object2d.h"
#include "PoliLine.h"

class CPoliLine2D :
	public CObject2D
{
protected:
	CPoliLine* m_pPoliLine;

public:
	CPoliLine2D(void);
	virtual ~CPoliLine2D(void);

	CPoliLine2D* Create(D3DXVECTOR3 vInitPos, D3DXVECTOR3 vDestPos, float fWidth);
	void Initialize();
	void Release();
	//void Update();
	//void Draw();
	//void DrawSetUp();
	//void DrawEnd();

	//void CalcLine();		// ���C���v�Z
	//void CalcDirVec();		// �i�s�����v�Z
	//void CalcCameraVec();	// �J�����ւ̃x�N�g���v�Z
	//void CalcDiffVec();		// �g�U�����v�Z
	//void CalcSquare();		// �l�p�v�Z

	// �Z�b�^�[
	//void SetPosLine();

};

