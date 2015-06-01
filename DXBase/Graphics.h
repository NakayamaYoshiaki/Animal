//=======================================================================================
//
//	  DirectX Graphics9 �N���X��`
//
//=======================================================================================
#pragma once

#include "main.h"

#define FOVY			60.0f								// ����p
#define NEAR_CLIP		0.1f								// �j�A�N���b�v���s������
#define FAR_CLIP		10000.0f							// �t�@�[�N���b�v���s������

//#define GETDEVICE (CGraphics::GetDevice())
enum
{
	PROJ_PERS = 1,
	PROJ_ORT,

	PROJ_MAX
};

class CGraphics
{
private:
	LPDIRECT3D9					m_pD3D;			// Direct3D9 �I�u�W�F�N�g
	static LPDIRECT3DDEVICE9	m_pDevice;		// Direct3DDevice9 �I�u�W�F�N�g
	D3DPRESENT_PARAMETERS		m_D3DPP;		// PRESENT PARAMETERS
	LPD3DXFONT					m_pFont;		// D3DXFont �I�u�W�F�N�g

	D3DXMATRIX					m_MatView;		// �r���[ �}�g���b�N�X
	D3DXMATRIX					m_MatProj;		// �ˉe�}�g���b�N�X

	HWND						m_hWnd;			// �E�B���h�E �n���h��
	int							m_nWidth;		// �\���̈敝
	int							m_nHeight;		// �\���̈捂��
	float						m_fFovy;		// ��p

public:
	static LPDIRECT3DDEVICE9 GetDevice() {return m_pDevice;}

	static CGraphics* Create(HWND hWnd, int nWidth, int nHeight, bool bWindow);
	void Release();
	bool Begin();
	void End();
	void SwapBuffer();
	void DrawText(int nX, int nY, LPCTSTR psz);

	void SetProjection(int n);

	// �Q�b�^�[

	// �Z�b�^�[
	void SetFovy(float fFovy);		// ��p�̕ύX
	void SetOrt(float fRate);		// ���s���e�g�嗦�ύX�i0.0~1.0�j
	
private:
	bool Initialize(HWND hWnd, int nWidth, int nHeight, bool bWindow);
	void Finalize();
};

//=======================================================================================
//	End of File
//=======================================================================================