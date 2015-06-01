// ���Đ��N���X�錾
#pragma once
#include "main.h"

// SE�p��
typedef enum
{
	SE_TEST = 0,
	
	SE_MAX
};


// BGM�p��
typedef enum
{
	BGM_TEST = 0,
	
	BGM_MAX
};

#define PLAYSOUND_MAX (20)		// �����Đ�SE��

class CSound
{
protected:
	static CSound*					m_pThis;	// �������g
	// int						m_EntryNum;		// �o�^��
	
	LPDIRECTSOUND8				m_pDirectSound;

public:
	CSound(void);
	virtual ~CSound();

	// ��{
	CSound*				Create();
	void				Initialize();
	virtual void		Release();

	HRESULT InitSound(HWND hWnd);				// �T�E���h�֘A������
	LPDIRECTSOUNDBUFFER8 LoadSound(LPTSTR file);		// �T�E���h�̃��[�h

	
	// �g��
	static CSound*		GetThis(){return m_pThis;};
};

//=======================================================================================
//	End of File
//=======

