#pragma once
#include "SceneBase.h"
#include "Collision.h"
#include "FadeOut.h"
#include "FadeIn.h"

// �g�p���郁�b�V��
enum 
{
	T_MESH_A = 0,

	T_MESH_MAX
};

// �g�p����e�N�X�`��
enum
{
	T_TEX_0 = 0,
	T_TEX_MOON,
	T_TEX_CARTEN,

	T_TEX_MAX,
};


// �^�C�g�����Ŏg�p����QD�I�u�W�F�N�g�̎��(�ڈ�)
enum
{
	T_2D_OBJ_TEST = 0,

	// �ő吔�����ɍŏ���ObjMgr�̓��ꕨ�̐���ݒ�
	T_2D_OBJ_MAX// �ォ����ꕨ�̃T�C�Y��ς�����
};

// �^�C�g�����Ŏg�p����RD�I�u�W�F�N�g�̎��
enum
{
	T_3D_OBJ_TEST = 0,
	T_3D_OBJ_TEST_BILL,

	T_3D_OBJ_MAX
};

// �g�p�T�E���h
enum
{
	T_SOUND_TEST = 0,

	T_SOUND_MAX			// �g�p����͍̂ő吔�̂�
};

class CTitle : public CSceneBase
{
public:
	CTitle(void);
	~CTitle(void);

	void Update();			// �X�V
	void Draw();			// �`��
	void Release();
			//void InitTitle();		// ������
	static CSceneBase* Create();	
	void CheckRunHit();
	//CImage* GetImage(int nTexNum){return m_pImage[nTexNum];};
	
	void SetChangeScene();
private:
	bool		 Initialize();
	
private:

	//CMesh		 m_Mesh[T_MESH_MAX];
	//CMesh		 m_MMesh[MORPMODEL_MAX];
	//CImage*		 m_pImage[TEX_ALL];

	// �C���X�^���X	
	CFadeOut* m_pFadeOut;
	CFadeIn* m_pFadeIn;

	int    m_nSwitch;

};

