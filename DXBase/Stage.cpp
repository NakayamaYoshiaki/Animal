// �X�e�[�W�Ǘ��N���X

// �C���N���[�h
#include "define.h"
#include "Stage.h"
#include "GameMgr.h"
#include "Input.h"

CStage* CStage::m_pThis = NULL;

int g_n = 0;
// �R���X�g���N�^
CStage::CStage(void)
{
	m_pThis = this;
}

// �f�X�g���N�^
CStage::~CStage(void)
{
}

//--------------------------------------------------------
// �X�e�[�W����
//--------------------------------------------------------
void CStage::Create()
{
	CStage* pStage = new CStage();		// �^�C�g���C���X�^���X����

	pStage->Initialize();
}

//--------------------------------------------------------
// �X�e�[�W������
//--------------------------------------------------------
void CStage::Initialize()
{
	// �X�e�[�W�Ɏg�����̗p��
	
	// �e�N�X�`���ǂݍ���

	// �e�N�X�`�����ǂݍ���

	// �QD�I�u�W�F����
	//m_pTest2D->Create(TEX_MOON);

	// �r���{�[�h

	// ���b�V���ǂݍ���
	
	// �J����
	m_pCameraBase = m_pCameraBase->Create();
	D3DXMATRIX mat = m_pCameraBase->GetMatrix();
	D3DXVECTOR3 vAdPos = D3DXVECTOR3(0.0f, 5.0f, 20.0f);
	D3DXVECTOR3 vLookPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_camera.SetAdjustPos(vAdPos);
	m_camera.SetLookPos(vLookPos);
	m_camera.SetEffect(C_EFFECT_NORMAL);

	// �t�F�[�h
	m_pFadeIn->Create(S_TEX_CARTEN);
}

void CStage::InitReturn()
{
	// �t�F�[�h
	m_pFadeIn->Create(S_TEX_CARTEN);
}

// �X�V
void CStage::Update()
{
	if(m_bSC)
	{
		if(m_pFadeOut->AskFin())
		{
			CGameMgr::GetThis()->SetScene(SCENE_RESULT);

			//m_pGlassPoint = m_pGlassPoint->OrgCreate();
			//m_pGlassPoint->GlassCreate();
		}
	}
	else
	{
		if(GETINPUT->GetKey(KEY_TRG, DIK_SPACE))
		{
			m_pFadeOut = m_pFadeOut->Create(S_TEX_CARTEN);
			m_bSC = true;
		}
	}

	// �S�I�u�W�F�N�g�X�V
	m_pObjMgr->AllUpdate();		// 3D2D�܂Ƃ߂čX�V
	
	// �r���{�[�h�I�u�W�F�ւ̃r���[�}�g���b�N�X�Z�b�g
	//CTestBill::SetMatView(m_camera.GetMatView());		
	
	// �J�������W�Z�b�g
	m_camera.Update(&m_pCameraBase->GetMatrix());

}

void CStage::Draw()
{
	m_szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���
	TCHAR	str[256];

	// �J����
	m_camera.Draw();

	// �S�I�u�W�F�N�g�`��
	m_pObjMgr->AllDraw();		// �QD�RD�܂Ƃ߂ĕ`��

	_stprintf(str, _T("�X�e�[�W\n"));
	lstrcat(m_szDebug, str);
	
	// �f�o�b�O������`��
	m_pGraph->DrawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, m_szDebug);
	
	
}

//----------------------------------
// �������
//-------------------------------------
void CStage::Release()
{
	// �e�N�X�`�����
	m_pTexMgr->Release();

	// ���f�����
	for(int i = 0; i < S_MESH_MAX; i++)
	{
		m_ppMesh[i]->Finalize();
	}
	SAFE_DELETE_ARRAY(m_ppMesh);		// ���ꕨ���
	
	// �}�l�[�W�����
	m_pObjMgr->Release();
	SAFE_DELETE(m_pObjMgr);

	// �J�����x�[�X���
	SAFE_DELETE(m_pCameraBase);

	//m_pFadeIn->Create();
	//m_pFadeOut->Release();
}



// EOF