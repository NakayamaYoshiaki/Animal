#include "Main.h"
#include "Sound.h"
#include "GameWnd.h"

// *************************
// �O���[�o���ϐ�
// *************************

CSound* CSound::m_pThis = new CSound();

CSound::CSound()
{

}

CSound::~CSound()
{
	
}

// ����
CSound*	CSound::Create()
{
	CSound* pSound = new CSound();

	pSound->Initialize();

	m_pThis = pSound;

	return pSound;
}

// ��������
void CSound::Initialize()
{
	
}

// ���
void CSound::Release()
{
	SAFE_RELEASE(m_pDirectSound);
	SAFE_DELETE(m_pThis);			// ���g�̏���
}

//================
// ������
// ==============
HRESULT CSound::InitSound(HWND hWnd)
{
	// DirectSound�I�u�W�F�N�g�̍쐬
	if( FAILED(DirectSoundCreate8(NULL, &m_pDirectSound, NULL)))
		return E_FAIL;

	// �������x���ݒ�
	if(FAILED(m_pDirectSound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
		return E_FAIL;

	return S_OK;
}

// ====================
// �T�E���h�̃��[�h
// ===================
LPDIRECTSOUNDBUFFER8 CSound::LoadSound(LPTSTR file)
{
	// MMIO = �}���`���f�B�A���o�́A�̗�
	LPDIRECTSOUNDBUFFER  pBaseBuffer = NULL;// �ȃf�[�^�̑����o�b�t�@
	LPDIRECTSOUNDBUFFER8 pBuffer = NULL;	// �ȃf�[�^�̃o�b�t�@
	DSBUFFERDESC buff;						// �o�b�t�@�ݒ�\����

	HMMIO hMmio = NULL;						// MMIO�n���h��
	MMIOINFO mmioInfo;						// �}���`���f�B�A�f�[�^�\����

	MMRESULT mmRes;								// MM�������ʊi�[�ϐ�
	MMCKINFO riffChunk, formatChunk, dataChunk;	// �`�����N�f�[�^�\����
	DWORD size;									// �f�[�^�T�C�Y�i�[�p
	WAVEFORMATEX pcm;							// �ȃf�[�^�t�H�[�}�b�g�\����

	LPVOID pBlock;					// �Z�J���_���o�b�t�@�̃f�[�^�������ݐ�A�h���X
	DWORD dwSize;					// �Z�J���_���o�b�t�@�̃T�C�Y

	// 1.�n���h�������Ƀt�@�C�����J��
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen(file, &mmioInfo, MMIO_READ);
	if(!hMmio)
		return NULL;

	// 2.�t�@�C����͇@ RIFF�`�����N����
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');				// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);	// �L�[���[�h�����Ɍ���

	if(mmRes != MMSYSERR_NOERROR)// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	// 3. �t�@�C����͇A�@�t�H�[�}�b�g�`�����N����
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');			// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);// �L�[���[�h�����Ɍ���

	if(mmRes != MMSYSERR_NOERROR)// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	size = mmioRead(hMmio, (HPSTR)&pcm, formatChunk.cksize);			// �����������ɓǂݍ���

	if(size != formatChunk.cksize)// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	mmioAscend(hMmio, &formatChunk, 0);

	// 4. �t�@�C����͇C�@�f�[�^�`�����N����
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');							// �����L�[���[�h
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);			// �L�[���[�h�����Ɍ���
	
	if(mmRes != MMSYSERR_NOERROR)			// ������Ȃ�������ُ�I��
	{
		mmioClose(hMmio, 0);
		return NULL;
	}

	//5. �f�[�^�ǂݍ���
	char *pData = new char[dataChunk.cksize];				// �K�v�ȗ̈�̑傫�����m�ۂ���
	size = mmioRead(hMmio, (HPSTR)pData, dataChunk.cksize);	// �f�[�^��ǂݍ���

	if(size != dataChunk.cksize)			// �������ǂݍ��߂Ȃ�������ُ�I��
	{
		delete[] pData;
		return NULL;
	}

	// 6. �Ȃ�ǂݍ��ށu�Z�J���_���o�b�t�@�v��p��
	ZeroMemory(&buff, sizeof(DSBUFFERDESC));			// �܂�������
	buff.dwSize = sizeof(DSBUFFERDESC);					// ��������e��ݒ�
	buff.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER;
	buff.dwBufferBytes = size;
	buff.lpwfxFormat = &pcm;

	// �����o�b�t�@�����
	if(FAILED(m_pDirectSound->CreateSoundBuffer(&buff, &pBaseBuffer, NULL)))
		return NULL;

	// �T�E���h�o�b�t�@�����o��
	if(FAILED(pBaseBuffer->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pBuffer)))
		return NULL;

	// ���o�����瑍���o�b�t�@���̂Ă�
	pBaseBuffer->Release();

	// 7. ���ꂽ�Z�J���_���o�b�t�@�Ƀf�[�^��]��
	// �܂��͏������݂ł���悤�o�b�t�@�����b�N
	if(FAILED(pBuffer->Lock(0, 0, &pBlock, &dwSize, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
		return NULL;

	memcpy(pBlock, pData, dwSize);		// �f�[�^�]��
	delete[] pData;						// ���̓ǂݍ��ݗ̈������

	// �o�b�t�@�̃��b�N����
	pBuffer->Unlock(pBlock, dwSize, 0, 0);

	// �Z�J���_���o�b�t�@��Ԃ��Ă悤�₭����
	return pBuffer;
}


//=======================================================================================
//	End of File
//==========================