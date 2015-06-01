// ���Đ��Ǘ�
#pragma once

// �C���N���[�h
#include "Sound.h"


enum
{
	SOUND_ONE,
	SOUND_LOOP,
};

// �Q�[���S�̂Ŏg�����̗�
enum
{
	SOUND_TEST = 0,

	SOUND_MAX
};

// ���Ǘ��N���X
class CSoundMgr
{
protected:
	static CSoundMgr* m_pThis;		// ���g

	LPDIRECTSOUNDBUFFER8*   m_lppSound;			// �T�E���h�Z�J���_���o�b�t�@(���I��)

	int*		m_pnIDArray;		// �o�^ID�i�[�z��i���I�j
	int			m_nEntryNum;		// �o�^��
public:
	CSoundMgr(void);
	virtual ~CSoundMgr(void);

	// ��{
	CSoundMgr* Create(int nSoundNum);	// ����
	void Initialize(int nSoundNum);
	virtual void Release();

	void UninitSound(void);								// �T�E���h�֘A��n��
	void InitBuffer(int nSoundNum);
	void LoadWave(void);
	void PlayWave(int nNum, int nLoop);
	// void UnInitWave(void);
	void RequestSound(int nID, int nLoop);		// ���Đ��̃��N�G�X�g

	// �g��
	int	CheckRunEntry(int nID);
	void Entry(int nID, LPTSTR file);
	// void ReleaseEntry();
	int RequestEntryNum(int nID);		// ���y���o�^����Ă���z��̓Y���������炤

};

