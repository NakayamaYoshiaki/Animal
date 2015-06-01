//=======================================================================================
//
//	  DirectInput �N���X
//
//=======================================================================================
#include <windows.h>
#include <tchar.h>
#include "define.h"
#include "DInput.h"

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CDInput::CDInput()
{
	m_pDI = NULL;
	m_pDIDeviceKeyboard = NULL;
	ZeroMemory(m_diKeyboardState, sizeof(m_diKeyboardState));
	m_pDIDeviceMouse = NULL;
	ZeroMemory(&m_diMouseState, sizeof(m_diMouseState));
	ZeroMemory(m_pDIDeviceJoystick, sizeof(m_pDIDeviceJoystick));
	ZeroMemory(m_diJoyState, sizeof(m_diJoyState));
	m_nJoystick = 0;
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CDInput::~CDInput()
{
}

//---------------------------------------------------------------------------------------
//  DirectInput �̏�����
//---------------------------------------------------------------------------------------
bool CDInput::Initialize(HWND hWnd)
{
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	// DirectInput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL))) {
		MessageBox(hWnd, _T("DirectInput �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	//******** �L�[�{�[�h�p
	// DirectInputDevice�I�u�W�F�N�g�̍쐬
	if (FAILED(m_pDI->CreateDevice(GUID_SysKeyboard, &m_pDIDeviceKeyboard, NULL))) {
		MessageBox(hWnd, _T("DirectInputDevice �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDIDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard))) {
		MessageBox(hWnd, _T("DirectInput �Ńf�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// �������x���̐ݒ�
	if (FAILED(m_pDIDeviceKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
		MessageBox(hWnd, _T("DirectInput�ŋ������x���̐ݒ�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// �f�o�C�X�ւ̓��͐���J�n
	if (FAILED(m_pDIDeviceKeyboard->Acquire())) {
		MessageBox(hWnd, _T("DirectInput �Ńf�o�C�X�ւ̓��͐���J�n�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	//******** �}�E�X�p
	// DirectInputDevice�I�u�W�F�N�g�̍쐬
	if (FAILED(m_pDI->CreateDevice(GUID_SysMouse, &m_pDIDeviceMouse, NULL))) {
		MessageBox(hWnd, _T("DirectInputDevice �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(m_pDIDeviceMouse->SetDataFormat(&c_dfDIMouse))) {
		MessageBox(hWnd, _T("DirectInput �Ńf�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// �������x���̐ݒ�
	if (FAILED(m_pDIDeviceMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
		MessageBox(hWnd, _T("DirectInput�ŋ������x���̐ݒ�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize       = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = DIPROPAXISMODE_REL;		// ���Βl���[�h�ɐݒ�
	m_pDIDeviceMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);

	// �f�o�C�X�ւ̓��͐���J�n
	if (FAILED(m_pDIDeviceMouse->Acquire())) {
		MessageBox(hWnd, _T("DirectInput �Ńf�o�C�X�ւ̓��͐���J�n�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}

	//******** �W���C�X�e�B�b�N�p
	// DirectInputDevice�I�u�W�F�N�g�̍쐬
	m_nJoystick = 0;
	if (FAILED(m_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, this, DIEDFL_ATTACHEDONLY))) {
		MessageBox(hWnd, _T("DirectInputDevice �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
		return false;
	}
	if (m_nJoystick == 0) {
//		MessageBox(hWnd, _T("�W���C�X�e�B�b�N��������܂���B"), _T("warning"), MB_OK | MB_ICONINFORMATION);
		return true;
	}

	for (int i = 0; i < m_nJoystick; i++) {
		// �f�[�^�t�H�[�}�b�g�̐ݒ�
		if (FAILED(m_pDIDeviceJoystick[i]->SetDataFormat(&c_dfDIJoystick))) {
			MessageBox(hWnd, _T("DirectInput �Ńf�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
			return false;
		}

		// �������x���̐ݒ�
		if (FAILED(m_pDIDeviceJoystick[i]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) {
			MessageBox(hWnd, _T("DirectInput�ŋ������x���̐ݒ�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
			return false;
		}

		// �f�o�C�X�̐ݒ�
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = DIJOFS_X;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_X;
		diprg.lMax       = JOY_MAX_X;
		m_pDIDeviceJoystick[i]->SetProperty(DIPROP_RANGE, &diprg.diph);	// �w�����͈̔͂��w��
		diprg.diph.dwObj = DIJOFS_Y;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_Y;
		diprg.lMax       = JOY_MAX_Y;
		m_pDIDeviceJoystick[i]->SetProperty(DIPROP_RANGE, &diprg.diph);	// �x�����͈̔͂��w��

		// �f�o�C�X�ւ̓��͐���J�n
		if (FAILED(m_pDIDeviceJoystick[i]->Acquire())) {
//			MessageBox(hWnd, _T("DirectInput �Ńf�o�C�X�ւ̓��͐���J�n�Ɏ��s���܂����I"), _T("error"), MB_OK | MB_ICONSTOP);
			return false;
		}
	}

	return true;
}

//---------------------------------------------------------------------------------------
//    �W���C�X�e�B�b�N�₢���킹�p�R�[���o�b�N�֐�
//---------------------------------------------------------------------------------------
BOOL CALLBACK CDInput::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	DIDEVCAPS	diDevCaps;			// �f�o�C�X���
	HRESULT		hRes;
	CDInput*	pDI = (CDInput*)pvRef;

	// �W���C�X�e�B�b�N�p�f�o�C�X�I�u�W�F�N�g���쐬
	hRes = pDI->m_pDI->CreateDevice(lpddi->guidInstance, &pDI->m_pDIDeviceJoystick[pDI->m_nJoystick], NULL);
	if (FAILED(hRes))
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hRes = pDI->m_pDIDeviceJoystick[pDI->m_nJoystick]->GetCapabilities(&diDevCaps);
	if (FAILED(hRes)) {
		SAFE_RELEASE(pDI->m_pDIDeviceJoystick[pDI->m_nJoystick]);
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	}
	if (++(pDI->m_nJoystick) < MAX_JOY)
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	return DIENUM_STOP;		// �K�v���������̂ŗ񋓂��I������
}

//---------------------------------------------------------------------------------------
//	DirectInput �̏I��
//---------------------------------------------------------------------------------------
void CDInput::Finalize(void)
{
	for (int i = 0; i < m_nJoystick; i++) {
		if (m_pDIDeviceJoystick[i])
			m_pDIDeviceJoystick[i]->Unacquire();	// ���͂��I��
		SAFE_RELEASE(m_pDIDeviceJoystick[i]);		// DirectInputDevice8 �I�u�W�F�N�g�̉��
	}
	if (m_pDIDeviceKeyboard)
		m_pDIDeviceKeyboard->Unacquire();	// ���͂��I��
	SAFE_RELEASE(m_pDIDeviceKeyboard);		// DirectInputDevice8 �I�u�W�F�N�g�̉��
	if (m_pDIDeviceMouse)
		m_pDIDeviceMouse->Unacquire();		// ���͂��I��
	SAFE_RELEASE(m_pDIDeviceMouse);			// DirectInputDevice8 �I�u�W�F�N�g�̉��
	SAFE_RELEASE(m_pDI);					// DirectInput8 �I�u�W�F�N�g�̉��
}

//---------------------------------------------------------------------------------------
//	DirectInput �L�[�{�[�h�^�}�E�X�^�W���C�X�e�B�b�N����̓���
//---------------------------------------------------------------------------------------
void CDInput::GetCtrlInfo(void)
{
	HRESULT	hRes;

	if (m_pDIDeviceKeyboard) {
		m_pDIDeviceKeyboard->Acquire();		// �v�����o��
		// ���݂̃L�[�{�[�h�̏�Ԃ��擾
		hRes = m_pDIDeviceKeyboard->GetDeviceState(256, &m_diKeyboardState);
		if (hRes == DIERR_INPUTLOST)
			m_pDIDeviceKeyboard->Acquire();	// �ēx�A�v�����o��
	}
	if (m_pDIDeviceMouse) {
		m_pDIDeviceMouse->Acquire();		// �v�����o��
		// ���݂̃}�E�X�̏�Ԃ��擾
		hRes = m_pDIDeviceMouse->GetDeviceState(sizeof(m_diMouseState), &m_diMouseState);
		if (hRes == DIERR_INPUTLOST)
			m_pDIDeviceMouse->Acquire();	// �ēx�A�v�����o��
	}
	for (int i = 0; i < m_nJoystick; i++) {
		m_pDIDeviceJoystick[i]->Acquire();		// �v�����o��
		m_pDIDeviceJoystick[i]->Poll();		// �f�o�C�X��̃|�[�����O�ΏۃI�u�W�F�N�g����f�[�^���擾
		// ���݂̃W���C�X�e�B�b�N�̏�Ԃ��擾
		hRes = m_pDIDeviceJoystick[i]->GetDeviceState(sizeof(m_diJoyState[0]), &m_diJoyState[i]);
		if (hRes == DIERR_INPUTLOST)
			m_pDIDeviceJoystick[i]->Acquire();	// �ēx�A�v�����o��
	}
}

//=======================================================================================
//	End of File
//=======================================================================================