#include "Object3D.h"
#include "Shader.h"
#include "SceneBase.h"
#include "ObjMgr.h"

// �R���X�g���N�^
CObject3D::CObject3D()
{
	// ���ʃX�e�[�^�X������
	m_nDrawType = DRAWTYPE_2D_NORMAL;
	m_nObjStatus = OBJST_NONE;

	m_bSphere = false;
	m_bBox = false;

	// ���b�V�� �N���X������
	m_pMesh = NULL;

	// �`��^�C�v
	m_nDrawType = DRAWTYPE_3D_NORMAL;

	// ���e�@
	m_nViewProjType = VIEWPROJ_PERS;

	// ���݃V�[������I�u�W�F�}�l�[�W�����擾
	//CObjMgr* pMgr = CSceneBase::GetCurScene()->GetObjMgr();

	// �}�l�[�W������g�b�v���擾
	//CObject3D* pTop = pMgr->GetListTop3D(m_nObjTypeID);

	// �A��
	//if(pTop->GetNext())		// ���������
	//	pTop->GetNext()->SetPrev(this);// �g�b�v��Next�̃I�u�W�F��Prev�ɐ�������I�u�W�F��o�^
	//SetNext(pTop->GetNext());		   // �g�b�v��Next�𐶐�����I�u�W�F��Next�ɂ���
	//SetPrev(pTop);				// ��������I�u�W�F�̑O���g�b�v�ɐݒ�
	//pTop->SetNext(this);		// �g�b�v��Next�ɐ�������I�u�W�F��o�^

	//if(pTop->m_pNext)		// ���������
	//	pTop->m_pNext->SetPrev(this);// �g�b�v��Next�̃I�u�W�F��Prev�ɐ�������I�u�W�F��o�^
	//m_pNext = pTop->m_pNext;		   // �g�b�v��Next�𐶐�����I�u�W�F��Next�ɂ���
	//m_pPrev = pTop;;				// ��������I�u�W�F�̑O���g�b�v�ɐݒ�
	//pTop->m_pNext = this;		// �g�b�v��Next�ɐ�������I�u�W�F��o�^

}

CObject3D::CObject3D(int nID) : CObjBase(nID)
{
	// ���ʃX�e�[�^�X������
	m_nDrawType = DRAWTYPE_2D_NORMAL;
	m_nObjStatus = OBJST_NONE;

	m_bSphere = false;
	m_bBox = false;

	// ���b�V�� �N���X������
	m_pMesh = NULL;

	// �`��^�C�v
	m_nDrawType = DRAWTYPE_3D_NORMAL;

	// ���e�@
	m_nViewProjType = VIEWPROJ_PERS;
}

// �f�X�g���N�^
CObject3D::~CObject3D(void)
{
	
}

// �X�V
void CObject3D::Update(void)
{
	
}

// �s���������`��
void CObject3D::Draw(void)
{
	if (!m_pMesh) return;

	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);
	m_pMesh->DrawNoAlpha(m_world);
}

// �����������`��
void CObject3D::DrawAlpha(void)
{
	if (!m_pMesh) return;

	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);
	m_pMesh->Draw(m_world,m_fAlpha);
	
	//CObject3D::DrawAlpha();
	/*D3DCOLORVALUE red = {1.0f, 0.0f, 0.0f, 0.3f};
	D3DCOLORVALUE green = {0.0f, 1.0f, 0.0f, 0.3f};
	if (m_bHit)
		m_pMesh->DrawBox(m_world, red);
	else
		m_pMesh->DrawBox(m_world, green);*/
}

// ���[���h�}�g���b�N�X�ւ̍��W�Z�b�g
void CObject3D::SetPosToMatrix()
{
	m_world._41 = m_vPos.x;
	m_world._42 = m_vPos.y;
	m_world._43 = m_vPos.z;
}

//void CObject3D::SetViewProj()
//{
//	switch(m_nViewProjType)
//	{
//	case VIEWPROJ_PERS:
//
//		break;
//
//	case VIEWPROJ_ORT:
//
//		break;
//	}
//}


void CObject3D::DrawSetUp()
{
	// �A���t�@ �u�����h�L����
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


}

void CObject3D::DrawEnd()
{
		// �A���t�@ �u�����h�L����
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	 // �A���t�@ �u�����h������
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

}