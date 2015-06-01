//=======================================================================================
//
//	  �Q�[���p�E�B���h�E �N���X��`
//
//=======================================================================================
#include "GameWnd.h"
#include "define.h"

#pragma comment(lib, "imm32.lib")

//---------------------------------------------------------------------------------------
//	�E�B���h�E������
//---------------------------------------------------------------------------------------
bool CGameWindow::InitInstance()
{
	if (!CWindow::InitInstance()) return false;

	// IME�֎~
	m_himc = ::ImmAssociateContext(GetHwnd(), NULL);

	m_bWindow = false;
	if (IDYES == MessageBox(_T("�E�B���h�E���[�h�Ŏ��s���܂����H"), _T("��ʃ��[�h"), MB_YESNO))
		m_bWindow = true;

	::timeBeginPeriod(1);	// �^�C�}�̕���\���ŏ��ɃZ�b�g

	// �O���t�B�b�N�f�o�C�X������
	m_pGraph = CGraphics::Create(GetHwnd(), SCREEN_WIDTH, SCREEN_HEIGHT, m_bWindow);
	if (!m_pGraph) return false;

	// ���̓f�o�C�X������
	m_pInput = GETINPUT;
	m_pInput->InitInput(GetHInstance(), GetHwnd());

	// �T�E���h�f�o�C�X������
	m_pSound = m_pSound->Create();
	m_pSound->InitSound(GetHwnd());

	// �Q�[���}�l�[�W���[������
	m_pGameMgr = CGameMgr::Create(m_pGraph);
	//if(!m_pScene = CreateScene(m_pGraph, SCENE_START))
		//return false;		// �V�[���������s
	if (!m_pGameMgr) return false;

	m_dwFPSLastTime = ::timeGetTime();
	m_dwExecLastTime = m_dwFPSLastTime - FRAME_RATE;// �K���ŏ��� m_pScene->Update() �����s
	m_dwFrameCount = 0;

	return true;
}

//---------------------------------------------------------------------------------------
//	�E�B���h�E���
//---------------------------------------------------------------------------------------
int CGameWindow::ExitInstance()
{
	// �V�[�����
	SAFE_RELEASE(m_pGameMgr);

	// �O���t�B�b�N �f�o�C�X���
	SAFE_RELEASE(m_pGraph);

	// ���̓f�o�C�X���
	m_pInput->UninitInput();

	// �T�E���h�f�o�C�X���
	m_pSound->Release();

	::timeEndPeriod(1);				// �^�C�}�̕���\�����ɖ߂�

	// IME����
	::ImmAssociateContext(GetHwnd(), m_himc);

	return CWindow::ExitInstance();	// ���s�t�@�C���̖߂�l
}

//---------------------------------------------------------------------------------------
//	�A�C�h��������
//---------------------------------------------------------------------------------------
bool CGameWindow::OnIdle(long lCount)
{
	
	// ���̕ӂŃt���[�����J�E���g
	DWORD dwCurrentTime = ::timeGetTime();			// ���݂̃^�C�}�l���擾
	if (dwCurrentTime - m_dwFPSLastTime >= 500) {	// 0.5 �b���ƂɌv��
		// �t���[�������v�Z
		if (m_pGameMgr) {
			m_pGameMgr->SetFPS(m_dwFrameCount * 1000 / (dwCurrentTime - m_dwFPSLastTime));
		
		}
		// �t���[�������v�Z
		/*if (CScene::CheckSceneIdle()) {
			//m_pScene->SetFPS(m_dwFrameCount * 1000 / (dwCurrentTime - m_dwFPSLastTime));
		
		}*/
		m_dwFPSLastTime = dwCurrentTime;	// �^�C�}�l���X�V
		m_dwFrameCount = 0;					// �t���[���J�E���^�����Z�b�g
	}
	// ���̕ӂŎ��ԊǗ�
	while (dwCurrentTime - m_dwExecLastTime >= FRAME_RATE)
	{	// ��莞�Ԃ��o�߂�����c
		m_dwExecLastTime += FRAME_RATE;							// �^�C�}�l���X�V
		if (m_pGameMgr) 
		{
			m_pInput->UpdateInput();							// ���͍X�V
			m_pGameMgr->Update();								// �Q�[�� ���C������
		}
	}
	if (m_pGameMgr) {
		m_pGameMgr->Render();				// �����_�����O����
	}
	m_dwFrameCount++;					// �t���[���J�E���g�{�P
	return true;
}

//---------------------------------------------------------------------------------------
//	WM_KEYDOWN �n���h��
//---------------------------------------------------------------------------------------
void CGameWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// [Esc] ��������Ă�����
	if (nChar == VK_ESCAPE) {
		// �E�B���h�E�����
		OnClose();
	}
}

//---------------------------------------------------------------------------------------
//	WM_ERASEBKGND �n���h��
//---------------------------------------------------------------------------------------
bool CGameWindow::OnEraseBkgnd(HDC hdc)
{
	// �w�i�������Ȃ��ŏ����ς݂Ƃ��ĕԂ�
	return true;
}

//---------------------------------------------------------------------------------------
//	WM_SETCURSOR �n���h��
//---------------------------------------------------------------------------------------
bool CGameWindow::OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg)
{
	// �S��ʃ��[�h���A�}�E�X�J�[�\�����W���N���C�A���g�̈���Ȃ�
	if (!m_bWindow || nHitTest == HTCLIENT) {
		// �}�E�X�J�[�\������
		::SetCursor(NULL);
		return true;
	}
	return false;
}

//=======================================================================================
//	End of File
//=======================================================================================