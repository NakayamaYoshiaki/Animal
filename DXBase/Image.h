// �e�N�X�`���Ǘ��N���X�錾
#pragma once

#include "main.h"
#include "Graphics.h"

enum
{
	TEX_A = 0,
	TEX_B,

	TEX_MAX
};

// �QD�e�N�X�`���Ǘ��N���X
class CImage
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DXVECTOR2			m_vSize;
	D3DXVECTOR2			m_vHalfSize;
	int					m_nPattern;
	D3DSURFACE_DESC		m_Desc;					// �e�N�X�`���̃T�C�Y���̏���ێ�����
	D3DXIMAGE_INFO		m_Info;					// ���摜�̃T�C�Y���̏���ێ�����

public:
	CImage(void);
	virtual ~CImage(void);

	static	CImage*		Create(LPCTSTR pszFName, int nPattern);
	bool	Initialize(LPCTSTR pszFName);
	bool	InitializeN(LPCTSTR pszFName);

	void				Release(void);				// �������
	D3DXVECTOR2*		GetSize()		{return &m_vSize;}
	D3DXVECTOR2*		GetHalfSize()	{return &m_vHalfSize;}
	LPDIRECT3DTEXTURE9	GetTexture()	{return m_pTexture;}
	int					GetPattern()	{return m_nPattern;}
	
};

