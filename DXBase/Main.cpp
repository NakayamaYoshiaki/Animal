//=======================================================================================
//
//	  [ DX9Game ] : DirectX9 �Q�[���x�[�X
//
//=======================================================================================//
#include "GameWnd.h"
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include "main.h"
#include "define.h"



#define CAPTION_NAME	_T("�A�j�܂�")	// �L���v�V����

//---------------------------------------------------------------------------------------
//	���C��
//---------------------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int iCmdShow)
{
	// �E�B���h�E���쐬
	int nResult = EXIT_FAILURE;
	CGameWindow* pWnd = new CGameWindow();
	if (pWnd->CreateFrame(CAPTION_NAME,				// �E�B���h�E �L���v�V����
		WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, 0,	// �E�B���h�E �X�^�C���C�g���X�^�C��
		CW_USEDEFAULT, CW_USEDEFAULT,				// �E�B���h�E�ʒu
		SCREEN_WIDTH, SCREEN_HEIGHT)) {				// �N���C�A���g�̈�T�C�Y
		pWnd->Show(iCmdShow);							// �E�B���h�E��\��
		pWnd->Update();									// �E�B���h�E�\�����X�V
		nResult = pWnd->Run();							// ���b�Z�[�W ���[�v
	}
	delete pWnd;
	return nResult;
}

//=======================================================================================
//	End of File
//=======================================================================================