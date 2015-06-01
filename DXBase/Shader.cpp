//=======================================================================================
//
//	�V�F�[�_����
//
//=======================================================================================

//-------- �w�b�_
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include "Shader.h"
#include "Window.h"
#include "Graphics.h"
//-------- �萔
#define PATH_FXTEST		_T("../data/shader/test.fx")
//#define PATH_TEXDIFFUSE	_T("../data/texture/earth.bmp")
//#define PATH_TEXNORMAL	_T("../data/texture/earthnormal.bmp")

D3DXVECTOR3	CShader::m_vLight = D3DXVECTOR3(0, 0, 0);
D3DXVECTOR3	CShader::m_vCamera = D3DXVECTOR3(0, 0, 0);
D3DXMATRIX	CShader::m_mView;
D3DXMATRIX	CShader::m_mProj;
//-------- �O���[�o���ϐ�

CShader* CShader::m_pThis = NULL;

CShader::CShader()
{
	
}

CShader::~CShader()
{

}

// �V�F�[�_����
void CShader::Create()
{
	m_pThis = new CShader();

	m_pThis->InitShader();
}

//---------------------------------------------------------------------------------------
// �V�F�[�_������
//---------------------------------------------------------------------------------------
HRESULT CShader::InitShader()
{
	m_nTech = 0;
	// �V�F�[�_�ǂݍ���
	HRESULT hr = D3DXCreateEffectFromFile(CGraphics::GetDevice(),
		PATH_FXTEST, NULL, NULL, 0, NULL, &m_pFX, NULL);
	if (FAILED(hr)) {
		TCHAR szMsg[1024];
		_stprintf(szMsg, _T("�V�F�[�_(%s)�ǂݍ��݃G���["),
			PATH_FXTEST);
		MessageBox(GETWND, szMsg, _T("error"), MB_OK);
		return hr;
	}
	// �e�N�X�`���ǂݍ���
	/*hr = D3DXCreateTextureFromFile(m_pDevice,
			PATH_TEXDIFFUSE, &m_pTex);
	hr = D3DXCreateTextureFromFile(m_pDevice,
			PATH_TEXNORMAL, &m_pTexNorm);*/


	// �n���h���擾
	struct _param {
		LPCSTR		pszName;
		D3DXHANDLE*	pHandle;
	} paramS[] = {
		{"WORLDVIEWPROJECTION", &m_hMatWVP},
		{"WORLD",				&m_hMatW},
		{"CAMERAPOSITION",		&m_hCamera},
		{"MATERIALDIFFUSE",		&m_hDiffuse},
		{"MATERIALSPECULAR",	&m_hSpecular},
		{"MATERIALPOWER",		&m_hPower},
		{"MATERIALAMBIENT",		&m_hAmbient},
		{"MATERIALTEXTURE",		&m_hTexture},
		{"MATERIALTEXTUREVALID", &m_hTexEnable},
	};
	for (int i = 0; i < _countof(paramS); i++) {
		*paramS[i].pHandle =
			m_pFX->GetParameterBySemantic(NULL,
									paramS[i].pszName);
	}
	/*struct _param paramG[] =
	{
		{"light", &m_hLight},
		{"texNormal", &m_hTexNormal}
	};
	for(int i = 0; i < _countof(paramG); i++)
	{
		*paramG[i].pHandle = 
			m_pFX->GetParameterByName(NULL, paramG[i].pszName);
	}*/
	m_hLight = m_pFX->GetParameterByName(NULL, "light");
	m_hTech = m_pFX->GetTechnique(0);

	return hr;
}

//---------------------------------------------------------------------------------------
// �J�������ݒ�
//---------------------------------------------------------------------------------------
void CShader::SetCamera(LPD3DXVECTOR3 pCamera,
	LPD3DXMATRIX pView, LPD3DXMATRIX pProj)
{
	m_vCamera = *pCamera;
	m_mView = *pView;
	m_mProj = *pProj;
}

//---------------------------------------------------------------------------------------
// �����x�N�g���ݒ�
//---------------------------------------------------------------------------------------
void CShader::SetLight(LPD3DXVECTOR3 pLight)
{
	m_vLight = *pLight;
}

//---------------------------------------------------------------------------------------
// �V�F�[�_�J�n
//---------------------------------------------------------------------------------------
void CShader::BeginShader()
{
	// �e�N�j�b�N�ݒ�
	m_pFX->SetTechnique(m_hTech);
	m_pFX->Begin(NULL, 0);
	// �p�X�J�n
	m_pFX->BeginPass(0);
}

//---------------------------------------------------------------------------------------
// ���[���h�ϊ��s��ݒ�(&�V�F�[�_�֐ݒ�)
//---------------------------------------------------------------------------------------
void CShader::SetWorldMatrix(LPD3DXMATRIX pWorld)
{
	m_pFX->SetMatrix(m_hMatWVP,
		&(*pWorld * m_mView * m_mProj));		// �|�����z
	m_pFX->SetMatrix(m_hMatW, pWorld);			// �P�Ƃ�
	m_pFX->SetFloatArray(m_hLight, &m_vLight.x, 3);
	m_pFX->SetFloatArray(m_hCamera, &m_vCamera.x, 3);
}

//---------------------------------------------------------------------------------------
// �}�e���A���ݒ�(&�R�~�b�g)
//---------------------------------------------------------------------------------------
void CShader::SetMaterial(D3DMATERIAL9* pMaterial,
	LPDIRECT3DTEXTURE9 pTexture)
{
	m_pFX->SetVector(m_hDiffuse,
		(LPD3DXVECTOR4)&pMaterial->Diffuse);
	m_pFX->SetVector(m_hSpecular,
		(LPD3DXVECTOR4)&pMaterial->Specular);
	m_pFX->SetFloat(m_hPower, pMaterial->Power);
	m_pFX->SetVector(m_hAmbient,
		(LPD3DXVECTOR4)&pMaterial->Ambient);
	if (pTexture) {
		m_pFX->SetTexture(m_hTexture, pTexture);
		m_pFX->SetBool(m_hTexEnable, TRUE);
	} else {
		m_pFX->SetBool(m_hTexEnable, FALSE);
	}
	/*m_pFX->SetTexture(m_hTexture, m_pTex);
	m_pFX->SetTexture(m_hTexNormal, m_pTexNorm);*/
	m_pFX->CommitChanges();
}

//---------------------------------------------------------------------------------------
// �V�F�[�_�I��
//---------------------------------------------------------------------------------------
void CShader::EndShader()
{
	// �p�X�I��
	m_pFX->EndPass();
	// �e�N�j�b�N�I��
	m_pFX->End();
}

//---------------------------------------------------------------------------------------
// �V�F�[�_���
//---------------------------------------------------------------------------------------
void CShader::FinShader()
{
	SAFE_RELEASE(m_pFX);
	SAFE_DELETE(m_pTex);
	SAFE_DELETE(m_pTexNorm);
}


void CShader::UpdateShader()
{
	if((GetAsyncKeyState(VK_RETURN) & 0x0001) ||
		(GetAsyncKeyState('Q') & 0x0001))
	{
		m_nTech = (m_nTech + 1) % 4;
		m_hTech = m_pFX->GetTechnique(m_nTech);
	}
}


//=======================================================================================
//	End of File
//=======================================================================================