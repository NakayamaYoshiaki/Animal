//2D�I�u�W�F�N�g�N���X�錾
#pragma once
#include "ObjBase.h"



class CObject2D :
	public CObjBase
{
protected:
	//CObject2D* m_pNext;		// ��
	//CObject2D* m_pPrev;		// �O

	//int		m_nObjTypeID;	// �I�u�W�F��ނ�ID

	//D3DXVECTOR3 m_vPos;
	// 2D���
	CBoard2D			m_Board;	// �QD�{�[�h���
public:
	CObject2D(void);
	CObject2D(int nID, int nTexNum);
	virtual ~CObject2D(void);

	//CObject2D* Create();
	CObject2D* Create(int nID, int nTexNum, D3DXVECTOR3 vPos);
	void Initilaize(){};
	virtual void Update();
	virtual void DrawSetUp();
	virtual void DrawEnd();
	virtual void Draw();
	virtual void Release(){};

	//void Hit(CObject3D* pObj){};

	


};

