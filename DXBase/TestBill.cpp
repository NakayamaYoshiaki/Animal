#include "TestBill.h"
#include "Input.h"
#include "Graphics.h"
#include "SceneBase.h"
#include "Camera.h"
#include "SceneBase.h"


CTestBill::CTestBill(void)
{
}

CTestBill::CTestBill(int n, int nTexNum) : CBillboard(n, nTexNum)
{

}


CTestBill::~CTestBill(void)
{

}


CTestBill*	CTestBill::Create(int nID, int nTexNum, D3DXVECTOR3 vPos)
{
	CTestBill*	pTest = new CTestBill(nID, nTexNum);

	pTest->m_vPos = vPos;

	if(!pTest->Initialize(nTexNum))
	{
		SAFE_DELETE(pTest);
	}

	return pTest;
}

bool		CTestBill::Initialize(int nTexNum)
{
	m_nObjGroupID = OBJ3DGROUP_MAP;		// �O���[�v�ݒ�
	//m_nDType = OT_2D;
	
	// 2D�X�e�[�^�X�Z�b�g
	
	m_Board.ReSize(D3DXVECTOR2(64.0f, 64.0f));
	
	m_nCollBasePoint = COLLBASEPOINT_CENTER;		// �����蔻���_

	SetPosToMatrix();

	// HWND hWnd = CGameWindow::GetHwnd();

	// �r���{�[�h������
	InitializeBillboard();

	// �r���{�[�h�����I�t
	m_bBillBoard = false;

	// �J�����O�I�t
	SetbCull(true);


	m_bAlphaBlend = false;
	return true;
}
#define BILLSPD (0.4f)
void		CTestBill::Update()
{
	/*if(GETINPUT->GetKey(KEY_PRS, DIK_RIGHT))
	{
		m_vPos.x += BILLSPD;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_LEFT))
	{
		m_vPos.x -= BILLSPD;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_UP))
	{
		m_vPos.y += BILLSPD;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_DOWN))
	{
		m_vPos.y -= BILLSPD;
	}

	if(GETINPUT->GetKey(KEY_PRS, DIK_I))
	{
		m_vPos.z += 1.0f;
	}
	if(GETINPUT->GetKey(KEY_PRS, DIK_K))
	{
		m_vPos.z -= 1.0f;
	}*/
	// ���W�Z�b�g
	// �r���{�[�h�p***************************
	
	// �r���{�[�h�X�V
	UpdateBillBoard();
	//****************************************************

}


