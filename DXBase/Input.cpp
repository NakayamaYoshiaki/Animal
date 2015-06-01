#include "Input.h"

CInput* CInput::m_pThis = new CInput();

LPDIRECTINPUT8			CInput::m_pDInput = NULL;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	CInput::m_pDIDevKeyboard = NULL;			// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
LPDIRECTINPUTDEVICE8	CInput::m_pDIDevMouse = NULL;				// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�}�E�X)
LPDIRECTINPUTDEVICE8	CInput::m_pDIDevJoypad[MAX_CONTROLER];		// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�W���C�p�b�h)
int						CInput::m_nNumCont = 0;						// �R���g���[���̐�


CInput::CInput(void)
{

}


CInput::~CInput(void)
{

}

//==============================
// ���͏����̏�����
//==============================
HRESULT CInput::InitInput(HINSTANCE hInst, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̍쐬
	if(FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION,
					IID_IDirectInput8, (void**)&m_pDInput, NULL)))
		return E_FAIL;

	// �L�[�{�[�h�̏�����
	if(FAILED(InitKeyboard(hWnd)))
		return E_FAIL;

	// �}�E�X�̏�����
	if(FAILED(InitMouse(hWnd)))
		return E_FAIL;

	// �Q�[���p�b�h�̏�����
	if(FAILED(InitJoypad(hWnd)))
		return E_FAIL;

	return S_OK;
}

//==============================
// ���͏����̏I������
//==============================
void CInput::UninitInput(void)
{
	// �L�[�{�[�h�̏I������
	UninitKeyboard();

	// �}�E�X�̏I������
	UninitMouse();

	// �Q�[���p�b�h�̏I������
	UninitJoypad();

	// �I�u�W�F�N�g�̌�n��
	SAFE_RELEASE(m_pDInput);
}

//==============================
// ���͏����̍X�V����
//==============================
void CInput::UpdateInput(void)
{
	// �L�[�{�[�h�̍X�V
	UpdateKeyboard();

	// �}�E�X�̍X�V
	UpdateMouse();

	// �Q�[���p�b�h�̍X�V
	UpdateJoypad();
}

//==============================
// �L�[�{�[�h�̏�����
//==============================
HRESULT CInput::InitKeyboard(HWND hWnd)
{
	// �f�o�C�X�I�u�W�F�N�g���쐬
	if(FAILED(m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevKeyboard, NULL)) || m_pDIDevKeyboard == NULL)
		return E_FAIL;

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(m_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
		return E_FAIL;

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if(FAILED(m_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		return E_FAIL;

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDIDevKeyboard->Acquire();

	return S_OK;
}

//==============================
// �L�[�{�[�h�̏I������
//==============================
void CInput::UninitKeyboard(void)
{
	SAFE_RELEASE(m_pDIDevKeyboard);
}

//==============================
// �L�[�{�[�h�̍X�V����
//==============================
void CInput::UpdateKeyboard(void)
{
	// �f�o�C�X����f�[�^���擾�B���s������L�[�{�[�h�ւ̃A�N�Z�X�����擾
	if(FAILED(m_pDIDevKeyboard->GetDeviceState(sizeof(m_KeyState), m_KeyState)))
		m_pDIDevKeyboard->Acquire();

	// �g���K�[�ƃ����[�X�p�f�[�^�擾
	for(DWORD dwCnt = 0; dwCnt < 256; dwCnt ++)
	{
		m_KeyStateTrg[dwCnt] = (m_KeyStatePrev[dwCnt] ^ m_KeyState[dwCnt]) & m_KeyState[dwCnt];
		m_KeyStateRls[dwCnt] = (m_KeyStatePrev[dwCnt] ^ m_KeyState[dwCnt]) & m_KeyStatePrev[dwCnt];
		m_KeyStatePrev[dwCnt] = m_KeyState[dwCnt];
	}

	// ���O�L�[���̃o�b�N�A�b�v
	//memcpy(m_KeyStatePrev, m_KeyState, sizeof(m_KeyState));


}

// �L�[�{�[�h�̓��͔���
bool CInput::GetKey(KEY_TYPE eKeyType, DWORD dwKey)
{
	switch(eKeyType)
	{
	case KEY_PRS:		// �v���X
		if(m_KeyState[dwKey] & 0x80)
			return true;
		break;

	case KEY_TRG:		// �g���K�[
		if(m_KeyStateTrg[dwKey] & 0x80)
			return true;
		break;

	case KEY_RLS:		// �����[�X
		if(m_KeyStateRls[dwKey] & 0x80)
			return true;
		break;
	}
	return false;
}

//==============================
// �}�E�X�̏�����
//==============================
HRESULT CInput::InitMouse(HWND hWnd)
{
	// �f�o�C�X�I�u�W�F�N�g���쐬
	if(FAILED(m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIDevMouse, NULL)) || m_pDIDevMouse == NULL)
		return E_FAIL;

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(m_pDIDevMouse->SetDataFormat(&c_dfDIMouse2)))
		return E_FAIL;

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if(FAILED(m_pDIDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		return E_FAIL;

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDIDevMouse->Acquire();

	return S_OK;
}

//==============================
// �}�E�X�̏I������
//==============================
void CInput::UninitMouse(void)
{
	SAFE_RELEASE(m_pDIDevMouse);
}

//==============================
// �}�E�X�̍X�V����
//==============================
void CInput::UpdateMouse(void)
{
	// ���O�}�E�X���̃o�b�N�A�b�v
	m_mouseStatePrev = m_mouseState;

	// �f�o�C�X����f�[�^���擾�B���s������}�E�X�ւ̃A�N�Z�X�����擾
	if(FAILED(m_pDIDevMouse->GetDeviceState(sizeof(m_mouseState), &m_mouseState)))
		m_pDIDevMouse->Acquire();
}

//===============================
// �}�E�X�̍��W�擾(2D�j
//===============================
void CInput::SetPosCursor(POINT pt)
{
	m_mouseState.lX = pt.x;
	m_mouseState.lY = pt.y;
}

//==============================
// �W���C�p�b�h�̏�����
//==============================
HRESULT CInput::InitJoypad(HWND hWnd)
{
	int nLoop;

	// ������
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
		m_pDIDevJoypad[nLoop] = NULL;

	// �f�o�C�X�I�u�W�F�N�g���쐬(�ڑ�����Ă���W���C�p�b�h��񋓂���)
	if(FAILED(m_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY)))
		return E_FAIL;

	// �W���C�p�b�h�̐���������
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// �W���C�p�b�h���Ȃ��ꍇ�͂�����΂�
		if(m_pDIDevJoypad[nLoop] == NULL)
			continue;

		// �f�[�^�t�H�[�}�b�g�̐ݒ�
		if(FAILED(m_pDIDevJoypad[nLoop]->SetDataFormat(&c_dfDIJoystick)))
			return E_FAIL;

		// �������x���̐ݒ�
		if(FAILED(m_pDIDevJoypad[nLoop]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
			return E_FAIL;

		// �f�o�C�X�ւ̓��͐���J�n
		m_pDIDevJoypad[nLoop]->Acquire();	
	}

	return S_OK;
}

//==============================
// �W���C�p�b�h�₢���킹�p�R�[���o�b�N�֐�
//==============================
BOOL CALLBACK CInput::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	DIDEVCAPS	diDevCaps;			// �f�o�C�X���

	// �W���C�p�b�h�p�f�o�C�X�I�u�W�F�N�g���쐬
	if(FAILED(m_pDInput->CreateDevice(lpddi->guidInstance, &m_pDIDevJoypad[m_nNumCont], NULL)))
		return DIENUM_CONTINUE;		// �񋓂𑱂���

	// �W���C�p�b�h�̔\�͂𒲂ׂ�
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	if(FAILED(m_pDIDevJoypad[m_nNumCont]->GetCapabilities(&diDevCaps)))
	{
		if(m_pDIDevJoypad[m_nNumCont])
			m_pDIDevJoypad[m_nNumCont]->Release();
		m_pDIDevJoypad[m_nNumCont] = NULL;
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	}

	// �K�萔�ɒB������I��
	m_nNumCont++;
	if(m_nNumCont == MAX_CONTROLER)
		return DIENUM_STOP;		// �񋓂��I������
	else
		return DIENUM_CONTINUE;		// �񋓂𑱂���
}

//==============================
// �W���C�p�b�h�̏I������
//==============================
void CInput::UninitJoypad(void)
{
	for(int nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
		SAFE_RELEASE(m_pDIDevJoypad[nLoop]);
}

//==============================
// �W���C�p�b�h�̍X�V����
//==============================
void CInput::UpdateJoypad(void)
{
	int nLoop;
	
	for(nLoop = 0; nLoop < MAX_CONTROLER; nLoop++)
	{
		// ���O�W���C�p�b�h���̃o�b�N�A�b�v
		m_joyStatePrev[nLoop] = m_joyState[nLoop];

		if(m_pDIDevJoypad[nLoop])
		{
			// �f�o�C�X����f�[�^���擾
			if(FAILED(m_pDIDevJoypad[nLoop]->GetDeviceState(sizeof(DIJOYSTATE), &m_joyState[nLoop])))
				m_pDIDevJoypad[nLoop]->Acquire();
		}
	}
}


//=================================================================
// EOF
//===================================================================
