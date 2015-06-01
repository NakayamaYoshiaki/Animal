#pragma once
#include "main.h"
#include "Image.h"

// �e�N�X�`���Ǘ��N���X
class CTexMgr
{
public:
	CTexMgr(void);
	virtual ~CTexMgr(void);

	CTexMgr*		Create(int nTexNum);
	void		Initialize(int nTexNum);
	void		Release();		// ���

	void		InitList();		// ���X�g������
	void		Entry(int nID, LPCTSTR pszfName, int nPattern);		// �o�^
	int			CheckRunID(int nID);		// �o�^����

	void		ReleaseList();		// ���X�g�̉��
	
	// �Q�b�^�[
	CImage*		GetTex(int nTexID);

private:
	CImage**		m_ppTexList;		// ���I���X�g
	int*			m_pnIDArray;		// ID�i�[�z��i���I�j
	int				m_nEntryNum;		// �G���g���[�ő吔
};

