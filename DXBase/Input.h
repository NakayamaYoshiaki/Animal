// ���̓N���X��`
#pragma once
//#define DIRECTINPUT_VERSION 0x0900

// �C���N���[�h

#include "main.h"

//******************************
// �}�N����`
///*****************************
#define MAX_CONTROLER		(2)				// �R���g���[���ő吔(�g�����ɉ����ĕύX���邱��)

//******************************
// �v���g�^�C�v�Eextern�錾
//******************************
#include "define.h"

// ��
typedef enum
{
	KEY_PRS = 0,
	KEY_TRG,
	KEY_RLS,

	KEY_MAX
}KEY_TYPE;



// ���̓N���X
class CInput
{
public:
	CInput(void);
	~CInput(void);

	static CInput* GetThis(){return m_pThis;}

	HRESULT InitInput(HINSTANCE hInst, HWND hWnd);			// Input������
	void UninitInput(void);									// Input��n��
	void UpdateInput(void);									// ���͏��X�V

	// �L�[�{�[�h�֘A
	HRESULT InitKeyboard(HWND hWnd);
	void UninitKeyboard(void);
	void UpdateKeyboard(void);
	bool GetKey(KEY_TYPE eKeyType, DWORD dwKey);		// �L�[�{�[�h���͔���

	// �}�E�X�֘A
	HRESULT InitMouse(HWND hWnd);
	void UninitMouse(void);
	void UpdateMouse(void);
	void SetPosCursor(POINT pt);		// ���W�擾

	// �W���C�p�b�h�֘A
	HRESULT InitJoypad(HWND hWnd);
	void UninitJoypad(void);
	void UpdateJoypad(void);
	
	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

private:
	static CInput*					m_pThis;				// �������g

	static LPDIRECTINPUT8			m_pDInput;				// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
	
	// �L�[�{�[�h�֘A
	static LPDIRECTINPUTDEVICE8		m_pDIDevKeyboard;		// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
	BYTE				m_KeyState[256];					// �L�[�{�[�h���z��
	BYTE				m_KeyStatePrev[256];				// �L�[�{�[�h���z�� (���O)
	BYTE				m_KeyStateTrg[256];		// �g���K�[�p
	BYTE				m_KeyStateRls[256];		// �����[�X�p

	// �}�E�X�֘A
	static LPDIRECTINPUTDEVICE8		m_pDIDevMouse;			// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�}�E�X)
	DIMOUSESTATE2		m_mouseState;						// �}�E�X���z��
	DIMOUSESTATE2		m_mouseStatePrev;					// �}�E�X���z�� (���O)
		
	// �W���C�p�b�h�֘A
	static LPDIRECTINPUTDEVICE8		m_pDIDevJoypad[MAX_CONTROLER];// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�W���C�p�b�h)
	DIJOYSTATE			m_joyState[MAX_CONTROLER];			// �W���C�p�b�h���z��
	DIJOYSTATE			m_joyStatePrev[MAX_CONTROLER];		// �W���C�p�b�h���z�� (���O)
	static int						m_nNumCont;				// �R���g���[���̐�

	
	
	




};

#define GETINPUT (CInput::GetThis())
