//=======================================================================================
//
//	  DirectInput �N���X��`
//
//=======================================================================================
#pragma once

#include <dinput.h>						// DirectInput �֘A�̃w�b�_
// #define DIRECTINPUT_VERSION 0x0900		// DirectX8 �𖾎�

//-------- �W���C�X�e�B�b�N�֌W
#define		MAX_JOY			4			// �ő�F���ڑ���
#define		JOY_MIN_X		-128		// �w���ŏ��l
#define		JOY_MAX_X		127			// �w���ő�l
#define		JOY_MIN_Y		-128		// �x���ŏ��l
#define		JOY_MAX_Y		127			// �x���ő�l

class CDInput
{
private:
	LPDIRECTINPUT8			m_pDI;					// DirectInput8 �I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8	m_pDIDeviceKeyboard;	// DirectInputDevice8 �I�u�W�F�N�g
	BYTE					m_diKeyboardState[256];	// �L�[�{�[�h���擾�o�b�t�@
	LPDIRECTINPUTDEVICE8	m_pDIDeviceMouse;		// DirectInputDevice8 �I�u�W�F�N�g
	DIMOUSESTATE			m_diMouseState;			// �}�E�X���擾�o�b�t�@
	LPDIRECTINPUTDEVICE8	m_pDIDeviceJoystick[MAX_JOY];	// DirectInputDevice8 �I�u�W�F�N�g
	DIJOYSTATE				m_diJoyState[MAX_JOY];	// �W���C�X�e�B�b�N���擾�o�b�t�@
	int						m_nJoystick;			// �W���C�X�e�B�b�N�ڑ���

	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

public:
	CDInput();
	virtual ~CDInput();

	bool Initialize(HWND hWnd);
	void Finalize(void);
	void GetCtrlInfo(void);
	BYTE GetKey(int nIndex) {return m_diKeyboardState[nIndex];}
	DIMOUSESTATE& GetMouse() {return m_diMouseState;}
	int GetJoyCount() {return m_nJoystick;}
	DIJOYSTATE& GetJoy(int nIndex) {return m_diJoyState[nIndex];}
};

//=======================================================================================
//	End of File
//=======================================================================================