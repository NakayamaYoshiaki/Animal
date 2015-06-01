#include "Object2D.h"
#include "SceneBase.h"
#include "ObjMgr.h"

CObject2D::CObject2D(void)
{
	m_nDrawType = DRAWTYPE_2D_NORMAL;
}

CObject2D::CObject2D(int nID, int nTexNum) : CObjBase(nID)
{
	// ���݃V�[������I�u�W�F�}�l�[�W�����擾
	//CObjMgr* pMgr = CSceneBase::GetCurScene()->GetObjMgr();

	//pMgr->EntryObj2D(this, m_nObjTypeID);
	// �}�l�[�W������g�b�v���擾
	//CObject2D* pTop = pMgr->GetListTop2D(m_nObjTypeID);

	// �A��
	//if(pTop->GetNext())		// ���������
	//	pTop->GetNext()->SetPrev(this);// �g�b�v��Next�̃I�u�W�F��Prev�ɐ�������I�u�W�F��o�^
	//SetNext(pTop->GetNext());		   // �g�b�v��Next�𐶐�����I�u�W�F��Next�ɂ���
	//SetPrev(pTop);				// ��������I�u�W�F�̑O���g�b�v�ɐݒ�
	//pTop->SetNext(this);		// �g�b�v��Next�ɐ�������I�u�W�F��o�^
	//

	//if(pTop->m_pNext)		// ���������
	//	pTop->m_pNext->SetPrev(this);// �g�b�v��Next�̃I�u�W�F��Prev�ɐ�������I�u�W�F��o�^
	//m_pNext = pTop->m_pNext;		   // �g�b�v��Next�𐶐�����I�u�W�F��Next�ɂ���
	//m_pPrev = pTop;;				// ��������I�u�W�F�̑O���g�b�v�ɐݒ�
	//pTop->m_pNext = this;		// �g�b�v��Next�ɐ�������I�u�W�F��o�^
	//
	//m_nDType = OT_2D;
	m_Board.Initialize(nTexNum);
	
	m_vSize.x = m_Board.GetSize().x;	// �e�N�X�`���T�C�Y����T�C�Y�ݒ�
	m_vSize.y = m_Board.GetSize().y;
	m_vRadius.x = m_vSize.x / 2.0f;
	m_vRadius.y = m_vSize.y / 2.0f;
	
	m_nDrawType = DRAWTYPE_2D_NORMAL;
}


CObject2D::~CObject2D(void)
{
	CSceneBase::GetCurScene()->GetObjMgr()->SetbReset();		// �`��p���X�g���Z�b�g�t���OON
}

void CObject2D::Update()
{
	m_Board.SetPosC(m_vPos);		// 2D�|���̍X�V
}

void CObject2D::Draw()
{
	//DrawSetUp();

	CGraphics::GetDevice()->SetTexture(0, m_Board.m_pImage->GetTexture());
	CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_Board.m_verWk, sizeof(VERTEX_2D));// �|���S���`��

	//DrawEnd();
}

void CObject2D::DrawSetUp()
{
	if(m_bAlphaBlend)
	{
		CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z�o�b�t�@���X�V

		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		CGraphics::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		CGraphics::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0);
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);			// ���C�e�B���O���Ȃ�

	}
	else
	{
		CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	// Z�o�b�t�@���X�V���Ȃ�

		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// ���u�����h �s��

		CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);			// ���C�e�B���O���Ȃ�
	}
	
	// ���_�t�H�[�}�b�g�̐ݒ�
	CGraphics::GetDevice()->SetFVF(FVF_VERTEX_2D);

}

void CObject2D::DrawEnd()
{
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);				// ���C�e�B���O����

	// CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			// Z�o�b�t�@���X�V����

	CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);	// ���u�����h �s��

}


//eof