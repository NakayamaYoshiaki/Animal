#pragma once
#include "SceneBase.h"
#include "Image.h"
#include "TestBill.h"
#include "FadeOut.h"
#include "FadeIn.h"

// �g�p���b�V��
enum
{
	S_MESH_PLAYER = 0,
	S_MESH_ENEMY,
	S_MESH_MAP,
	S_MESH_SKY,		// �X�J�C�h�[��

	S_NMESH,

	S_MESH_DOLL,
	S_MESH_BUNNY,
	// S_MESH_BATTLE,

	S_MESH_MAX
};

// �g�p�e�N�X�`��
enum
{
	S_TEX_TEST = 0,
	S_TEX_CARTEN,

	S_TEX_MAX
};

// �X�e�[�W�N���X
class CStage : public CSceneBase
{
private:
	static CStage*		m_pThis;

	// �g�p�I�u�W�F�N�g�擪�A�h���X����
	CFadeOut* m_pFadeOut;
	CFadeIn* m_pFadeIn;
	
public:
	CStage(void);					// �R���X�g���N�^
	virtual ~CStage(void);			// �f�X�g���N�^

	void InitReturn();
	virtual void Update();			// �X�V
	virtual void Draw();		// �`�揈��

	static void Create();		// ����
	virtual void Release();		// �������

	void UnbushStage();			// �}�b�v�T���̃I�u�W�F�𕚂���
	void PopStage();			// ��̔���

	// �Q�b�^�[
	static CStage*	GetThis(){return m_pThis;};
	
	// �Z�b�^�[
	
private:
	void Initialize();		// ����������
	

};

