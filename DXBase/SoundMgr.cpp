#include "SoundMgr.h"

#define NULL_ID (9999)

CSoundMgr::CSoundMgr(void)
{
}


CSoundMgr::~CSoundMgr(void)
{
	//UnInitWave();
}

// ����
CSoundMgr* CSoundMgr::Create(int nSoundNum)
{
	CSoundMgr* pSFB = new CSoundMgr();

	pSFB->Initialize(nSoundNum);

	return pSFB;
}

void CSoundMgr::Initialize(int nSoundNum)
{
	m_nEntryNum = nSoundNum;
	InitBuffer(nSoundNum);		// �o�b�t�@�̏�����
}

void CSoundMgr::Release()
{
	// �o�b�t�@���
	for(int i = 0; i < m_nEntryNum; i++)
	{
		SAFE_RELEASE(m_lppSound[i]);
	}

	// ���ꕨ���
	SAFE_DELETE_ARRAY(m_lppSound);
	SAFE_DELETE_ARRAY(m_pnIDArray);

	delete this;
}

void CSoundMgr::InitBuffer(int nSoundNum)
{
	// �ϐ��錾
	// ���I�m��
	m_lppSound = new LPDIRECTSOUNDBUFFER8[nSoundNum];
	m_pnIDArray = new int[nSoundNum];
	// �T�E���h�Z�J���_���o�b�t�@������
	for(int i = 0; i < nSoundNum; i ++)
	{
		m_lppSound[i] = NULL;
		m_pnIDArray[i] = NULL_ID;		// �o�^ID��������
	}

	m_nEntryNum = nSoundNum;		// �ő吔��o�^

}
void CSoundMgr::LoadWave(void)
{
	// wav�t�@�C���̃��[�h
	//g_pSound[BGM_WAVE] = LoadSound(_T("SE/nami.wav"));

	//g_pSE_gogo = LoadSound(_T("gogo.wav"));
	//g_pSound[nNum] = LoadSound(_T("SE/%s", szFile));
}

void CSoundMgr::PlayWave(int nNum, int nLoop)
{
	m_lppSound[nNum]->Play(0, 0, nLoop);
}

//void CSoundFactryBase::UnInitWave(void)
//{
//	// �ϐ��錾
//
//	for(int i = 0; i < m_nEntryNum; i ++)
//	{
//		SAFE_RELEASE(m_lppSound[i]);
//	}
//
//	// ���ꕨ���
//	SAFE_DELETE_ARRAY(m_lppSound);
//	SAFE_DELETE_ARRAY(m_pnIDArray);
//}

// ���Đ��̃��N�G�X�g
void CSoundMgr::RequestSound(int nID, int nLoop)
{
	// �o�^����Ă���Y�������擾
	int nEntry = RequestEntryNum(nID);

	// ��ނ��Ƃ�switch
	switch(nID)
	{
	case SOUND_TEST:
		PlayWave(nEntry, nLoop);
		break;

	default:

		break;
	}

}

// �o�^����Ă��邩�̑���
int	CSoundMgr::CheckRunEntry(int nID)
{
	// ID���o�^�ς݂�����
	for(int i = 0; i < m_nEntryNum; i++)
	{
		// �o�^���Ă�������
		if(m_pnIDArray[i] == nID)
		{
			return i;		// ���̔z��̔ԍ���Ԃ�
		}

		// ��̔z��ɍs��������
		if(m_pnIDArray[i] == NULL_ID)
		{
			m_pnIDArray[i] = nID;		// �V�K�o�^�I�u�W�FID
			return i;		// �V�����o�^����z��̓Y������Ԃ�
		}
	}

	// �G���[
	// ���X�g���߂Ƃ��H
	return NULL_ID;
}

// ���y�f�[�^�̓o�^(ID�̓V�[���̃w�b�_�ł͂Ȃ��A�t�@�N�g���̃w�b�_�ɋL�����������L�q)
void CSoundMgr::Entry(int nID, LPTSTR file)
{
	// ����
	int nEntry = CheckRunEntry(nID);

	// �_�C���N�g�T�E���h�֓ǂݍ��ݗv��
	// �Z�J���_���o�b�t�@���擾
	m_lppSound[nEntry] = CSound::GetThis()->LoadSound(file);
}

// ���y���o�^����Ă���z��̓Y���������炤
int CSoundMgr::RequestEntryNum(int nID)
{
	// ID���o�^�ς݂�����
	for(int i = 0; i < m_nEntryNum; i++)
	{
		// �o�^���Ă�������
		if(m_pnIDArray[i] == nID)
		{
			return i;		// ���̔z��̔ԍ���Ԃ�
		}

		// ��̔z��ɍs��������
		if(m_pnIDArray[i] == NULL_ID)
			continue;
	}

	// �G���[
	// �o�^����ĂȂ�
	return NULL_ID;
}

// eof