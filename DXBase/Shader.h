//=======================================================================================
//
//	�V�F�[�_��`
//
//=======================================================================================
#ifndef _H_SHADER
#define _H_SHADER

//-------- �w�b�_
#include "main.h"
#include "define.h"
//

#define GETSHADER (CShader::GetThis())

// �e�N�j�b�N��
enum
{
	SHADER_NONE = 0, // �g��Ȃ��i���ʂ́j

	SHADER_1,

	SHADER_ALL
};

//-------- �V�F�[�_�N���X
class CShader
{
protected:


private:
	static CShader*		m_pThis;

	LPD3DXEFFECT	m_pFX;		// �G�t�F�N�g �I�u�W�F�N�g
	D3DXHANDLE		m_hMatWVP;	// ���[���h�~�r���[�~�ˉe
	D3DXHANDLE		m_hMatW;	// ���[���h �}�g���b�N�X
	D3DXHANDLE		m_hCamera;	// ���_���W
	D3DXHANDLE		m_hLight;	// �����x�N�g��
	D3DXHANDLE		m_hDiffuse;	// (�}�e���A��)�g�U�F
	D3DXHANDLE		m_hSpecular;// (�}�e���A��)���ʔ��ːF
	D3DXHANDLE		m_hPower;	// (�}�e���A��)���ʔ��ˎw��
	D3DXHANDLE		m_hAmbient;	// (�}�e���A��)���F
	D3DXHANDLE		m_hTexture;	// �e�N�X�`��
	D3DXHANDLE		m_hTexEnable;// �e�N�X�`���L��
	D3DXHANDLE		m_hTech;	// �e�N�j�b�N

	D3DXHANDLE		m_hTexNormal;	// �@���}�b�v�e�N�X�`��
	LPDIRECT3DTEXTURE9 m_pTex;
	LPDIRECT3DTEXTURE9 m_pTexNorm;

	static D3DXVECTOR3	m_vLight;
	static D3DXVECTOR3	m_vCamera;
	static D3DXMATRIX	m_mView;
	static D3DXMATRIX	m_mProj;

	int m_nTech;

public:
	CShader();
	~CShader();

	void Create();

	HRESULT InitShader();	// ������
	void UpdateShader();
	void BeginShader();		// �V�F�[�_�J�n
	void SetCamera(LPD3DXVECTOR3 pCamera,
	LPD3DXMATRIX pView, LPD3DXMATRIX pProj);
	void SetLight(LPD3DXVECTOR3 pLight);
	void SetWorldMatrix(LPD3DXMATRIX pWorld);
	void SetMaterial(D3DMATERIAL9* pMaterial,
	LPDIRECT3DTEXTURE9 pTexture);
	void EndShader();		// �V�F�[�_�I��
	void FinShader();		// ���

	// �Q�b�^�[
	static CShader* GetThis(){return m_pThis;};
};


#endif

//=======================================================================================
//	End of File
//=======================================================================================