//=======================================================================================
//
//	  �Q�[���p�E�B���h�E �N���X��`
//
//=======================================================================================
#pragma once

#include "Window.h"
#include "Graphics.h"
#include "SceneBase.h"
#include "GameMgr.h"
#include "Input.h"
#include "Sound.h"

#define FRAME_RATE		(1000/60)	// �t���[�����[�g

class CGameWindow : public CWindow
{
private:
	CGraphics*	m_pGraph;			// �`��f�o�C�X �N���X
	// CScene*		m_pScene;			// �V�[��
	CGameMgr*	m_pGameMgr;			// �Q�[���}�l�[�W���C���X�^���X�H
	CInput*		m_pInput;			// ���̓C���X�^���X
	CSound*		m_pSound;			// �T�E���h�C���X�^���X

	bool		m_bWindow;			// �E�B���h�E / �t���X�N���[��

	DWORD		m_dwExecLastTime;	// FPS�v���p
	DWORD		m_dwFPSLastTime;
	DWORD		m_dwFrameCount;

	HIMC		m_himc;

public:
	bool InitInstance();
	int ExitInstance();
	bool OnIdle(long lCount);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	bool OnEraseBkgnd(HDC hdc);
	bool OnSetCursor(HWND hwnd, UINT nHitTest, UINT uMouseMsg);
};

//=======================================================================================
//	End of File
//=======================================================================================