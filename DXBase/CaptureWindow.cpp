#include "CaptureWindow.h"


CCaptureWindow* CCaptureWindow::m_pThis = NULL; 

CCaptureWindow::CCaptureWindow(void)
{
}



CCaptureWindow::~CCaptureWindow(void)
{
}

CCaptureWindow* CCaptureWindow::Create()
{
	CCaptureWindow* p = new CCaptureWindow();

	if(!p->Initialize())
	{
		SAFE_DELETE(p);
	}

	m_pThis = p;

	return p;
}

bool CCaptureWindow::Initialize()
{
	m_bShot = false;
	// ���݂̉�ʂ�ۑ�
	//ScreenShot();

	return true;
}

void CCaptureWindow::PreservedWindow()
{
	//���݂̉�ʏ���ۑ�
	CGraphics::GetDevice()->GetViewport( &viewport1 );
	CGraphics::GetDevice()->GetRenderTarget( 0, &m_pBackbuffer );
	CGraphics::GetDevice()->GetDepthStencilSurface( &m_pBackZ );

}

void CCaptureWindow::ChangeTex()
{
	//�����_�����O�^�[�Q�b�g�̐؂�ւ�(�e�N�X�`����)
	CGraphics::GetDevice()->SetRenderTarget( 0, m_pRendTexSurface );
	CGraphics::GetDevice()->SetDepthStencilSurface( m_pRendTexZ );

}

void CCaptureWindow::Draw()
{
	//�`��
	CGraphics::GetDevice()->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255,255,255), 1.0f, 0);
	D3DVIEWPORT9 viewport2 = { 0, 0, 1024, 1024, 0.0f, 1.0f };
	CGraphics::GetDevice()->SetViewport( &viewport2 );

	//�����_�����O�^�[�Q�b�g�̐؂�ւ�(�o�b�N�o�b�t�@��)
	CGraphics::GetDevice()->SetRenderTarget( 0, m_pBackbuffer );
	CGraphics::GetDevice()->SetDepthStencilSurface( m_pBackZ );

	CGraphics::GetDevice()->SetViewport( &viewport1 ); 
}


bool CCaptureWindow::ScreenShot()
{
	if(!m_bShot)
		return false;

	// �o�b�N�o�t�@�̎擾
	LPDIRECT3DSURFACE9 pBackBuf;
	CGraphics::GetDevice()->GetRenderTarget(0, &pBackBuf);

	// �X�N�V���o��
	D3DXSaveSurfaceToFile("../Data/Image/scr_shot/scrshot.bmp", D3DXIFF_BMP, pBackBuf, NULL, NULL);

	// Get�n�Ŏ擾�����T�[�t�F�C�X��AddRef���Ă΂�Ă���̂ŖY�ꂸ�ɉ������
	pBackBuf->Release();

	m_bShot = false;

	return true;
}

