//=======================================================================================
//
//	  ���b�V�� �N���X
//
//=======================================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <stdio.h>
#include "define.h"

#include "Mesh.h"
#include "Graphics.h"

//---------------------------------------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------------------------------------
CMesh::CMesh()
{
	m_pD3DMesh = NULL;
	m_dwNumMaterial = 0;
	m_pMaterial = NULL;
	m_ppTexture = NULL;

	m_pAttr = NULL;
	m_dwAttr = 0;
	m_dwVtx = 0;
	m_pVtx = NULL;
	m_dwIdx = 0;
	m_pIdx = NULL;

	m_vHalf = D3DXVECTOR3(0, 0, 0);
	m_vCenter = D3DXVECTOR3(0, 0, 0);
	m_fRadius = 0;
	m_pSphere = NULL;

	m_pPiece = NULL;
	m_pPieceVtx = NULL;
	m_nBombCnt = 0;

	
}

//---------------------------------------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------------------------------------
CMesh::~CMesh()
{
	//Finalize();
}

bool CMesh::Initialize(LPCTSTR pszFName, int nType)
{
	switch(nType)
	{
	case MESH_N:
		InitializeNorm(pszFName);
		break;

	case MESH_S:
		InitializeSkin(pszFName);
		break;
	}

	return true;
}

//---------------------------------------------------------------------------------------
// ���b�V��������
//---------------------------------------------------------------------------------------
bool CMesh::InitializeNorm(LPCTSTR pszFName)
{
	TCHAR			szMsg[MAX_PATH + 32];
	TCHAR			szDir[_MAX_DIR];
	TCHAR			szCurrentDir[_MAX_PATH];

	LPD3DXBUFFER	pD3DXMtrlBuffer = NULL;

	// ���b�V���^�C�v�̐ݒ�
	m_nMeshType = MESH_N;

	// �t�H���_���𒊏o
	_tsplitpath(pszFName, NULL, szDir, NULL, NULL);

	

	// �w�t�@�C�����烁�b�V���f�[�^��ǂݍ���
	HRESULT hr = D3DXLoadMeshFromX(pszFName, D3DXMESH_SYSTEMMEM, CGraphics::GetDevice(),
		NULL, &pD3DXMtrlBuffer, NULL, &m_dwNumMaterial, &m_pD3DMesh);
	
	
	
	if (FAILED(hr)) {
		_stprintf(szMsg, _T("X�t�@�C��(%s)�̓ǂݍ��݂Ɏ��s���܂����B"), pszFName);
		MessageBox(NULL, szMsg, NULL, MB_OK);
		return false;
	}

	// FVF�`����␳(���_�t�H�[�}�b�g��ϊ�)
	LPD3DXMESH pMeshTmp;
	DWORD dwFVF = m_pD3DMesh->GetFVF();
	if (dwFVF != FVF_BVERTEX) {
		hr = m_pD3DMesh->CloneMeshFVF(m_pD3DMesh->GetOptions(), FVF_BVERTEX,
			CGraphics::GetDevice(), &pMeshTmp);
		SAFE_RELEASE(m_pD3DMesh);
		if (FAILED(hr)) {
			SAFE_RELEASE(pD3DXMtrlBuffer);
			return false;
		}
		// �@���������ꍇ�͋����I�ɒǉ�
		if ((dwFVF & D3DFVF_NORMAL) == 0) {
			D3DXComputeNormals(pMeshTmp, NULL);
		}
		m_pD3DMesh = pMeshTmp;
	}

	// �����e�[�u���𐶐����邽�߂̍œK��
	hr = m_pD3DMesh->Optimize(D3DXMESHOPT_ATTRSORT, NULL, NULL, NULL, NULL, &pMeshTmp);
	if (SUCCEEDED(hr)) {
		m_pD3DMesh->Release();
		m_pD3DMesh = pMeshTmp;
	} else {
		SAFE_RELEASE(pD3DXMtrlBuffer);
		return false;
	}
	// �����e�[�u���擾
	hr = m_pD3DMesh->GetAttributeTable(NULL, &m_dwAttr);
	if (FAILED(hr)) {
		SAFE_RELEASE(pD3DXMtrlBuffer);
		SAFE_RELEASE(m_pD3DMesh);
		return false;
	}
	m_pAttr = new D3DXATTRIBUTERANGE[m_dwAttr];
	hr = m_pD3DMesh->GetAttributeTable(m_pAttr, &m_dwAttr);
	// ���_�o�b�t�@/�C���f�b�N�X�o�b�t�@�Œ�
	LPVOID pVtx;
	m_pD3DMesh->LockVertexBuffer(D3DLOCK_READONLY, &pVtx);
	LPVOID pIdx;
	m_pD3DMesh->LockIndexBuffer(D3DLOCK_READONLY, &pIdx);
	// ���o�ꏊ�̊m��
	m_dwVtx = m_pD3DMesh->GetNumVertices();
	m_pVtx = new BVERTEX[m_dwVtx];
	m_dwFace = m_pD3DMesh->GetNumFaces();
	m_dwIdx = m_dwFace * 3;
	m_pIdx = new WORD[m_dwIdx];
	m_pPiece = new PARTICLE[m_dwFace];
	m_pPieceVtx = new BVERTEX[m_dwIdx];
	// �R�s�[
	CopyMemory(m_pVtx, pVtx, sizeof(BVERTEX) * m_dwVtx);
	CopyMemory(m_pIdx, pIdx, sizeof(WORD) * m_dwIdx);
	// ���_�o�b�t�@/�C���f�b�N�X�o�b�t�@���
	m_pD3DMesh->UnlockVertexBuffer();
	m_pD3DMesh->UnlockIndexBuffer();

	// �J�����g�f�B���N�g����ύX
	if (szDir[0]) {
		GetCurrentDirectory(_MAX_PATH, szCurrentDir);
		SetCurrentDirectory(szDir);
	}

	// �}�e���A���ǂݍ���
	D3DXMATERIAL* pD3DMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMaterial = new D3DMATERIAL9[m_dwNumMaterial];
	m_ppTexture = new LPDIRECT3DTEXTURE9[m_dwNumMaterial];
	for (DWORD i = 0; i < m_dwNumMaterial; i++) { 
		m_pMaterial[i] = pD3DMaterials[i].MatD3D;
		m_pMaterial[i].Ambient = m_pMaterial[i].Diffuse;
		m_ppTexture[i] = NULL;
		if (pD3DMaterials[i].pTextureFilename && pD3DMaterials[i].pTextureFilename[0]) {
			// �e�N�X�`���t�@�C����ǂݍ���
			if (FAILED(D3DXCreateTextureFromFileA(CGraphics::GetDevice(),
				pD3DMaterials[i].pTextureFilename, &m_ppTexture[i]))) {
				_stprintf(szMsg, _T("�e�N�X�`��(%hs)�̓ǂݍ��݂Ɏ��s���܂����B"),
					pD3DMaterials[i].pTextureFilename);
				MessageBox(NULL, szMsg, NULL, MB_OK);
			}
		}
	}

	// �J�����g�f�B���N�g�������ɖ߂�
	if (szDir[0])
		SetCurrentDirectory(szCurrentDir);

	pD3DXMtrlBuffer->Release();

	// ���E�{�b�N�X����
	D3DXVECTOR3 vMin = m_pVtx[0].pos;
	D3DXVECTOR3 vMax = vMin;
	BVERTEX* pBVtx = m_pVtx + 1;
	for (DWORD i = 1; i < m_dwVtx; i++, pBVtx++) {
		if (vMin.x > pBVtx->pos.x)
			vMin.x = pBVtx->pos.x;
		if (vMin.y > pBVtx->pos.y)
			vMin.y = pBVtx->pos.y;
		if (vMin.z > pBVtx->pos.z)
			vMin.z = pBVtx->pos.z;
		if (vMax.x < pBVtx->pos.x)
			vMax.x = pBVtx->pos.x;
		if (vMax.y < pBVtx->pos.y)
			vMax.y = pBVtx->pos.y;
		if (vMax.z < pBVtx->pos.z)
			vMax.z = pBVtx->pos.z;
	}
	m_vHalf = (vMax - vMin) / 2.0f;
	m_vCenter = (vMax + vMin) / 2.0f;

	// ���E���̐���
	m_fRadius = 0.0f;
	float fR;
	for (DWORD i = 0; i < m_dwVtx; i++) {
		fR = D3DXVec3Length(&(m_pVtx[i].pos - m_vCenter));
		if (m_fRadius < fR)
			m_fRadius = fR;
	}

	// ���E���C���[�W�̐���
	D3DXCreateSphere(CGraphics::GetDevice(),
 		m_fRadius, 32, 16, &m_pSphere, NULL);

	// ���E�{�b�N�X�C���[�W�̐���
	D3DXCreateBox(CGraphics::GetDevice(),
		vMax.x - vMin.x, vMax.y - vMin.y, vMax.z - vMin.z, &m_pBox, NULL);

	return true;
}

//----------------------------------------------
// �X�L�����b�V���A�j���p������
//--------------------------------------------------
bool CMesh::InitializeSkin(LPCTSTR pszFName)
{
	// �f�B���N�g�����o
	TCHAR szDir[_MAX_PATH];
	TCHAR szDirWk[_MAX_DIR];
	_tsplitpath(pszFName, szDir, szDirWk, NULL, NULL);
	lstrcat(szDir, szDirWk);
	m_Hierarchy.SetDirectory(szDir);

	// ���b�V���^�C�v�̐ݒ�
	m_nMeshType = MESH_S;

	// �A�j���[�V�������胁�b�V���ǂݍ���
	// �K�w�\�����b�V���̓ǂݍ���
	HRESULT hr = D3DXLoadMeshHierarchyFromX(pszFName,
		D3DXMESH_MANAGED, CGraphics::GetDevice(),
		&m_Hierarchy, NULL,
		&m_pFrameRoot, &m_pAnimCtrl);
	if (FAILED(hr)) return false;
	//if (!m_pAnimCtrl) return false;
	// �{�[���ƃt���[���̊֘A�t��
	hr = AllocAllBoneMatrix(m_pFrameRoot);
	if (FAILED(hr)) return false;

	// �A�j���[�V�����Z�b�g�擾
	m_uNumAnimSet = 0;
	if (m_pAnimCtrl)
	{
		m_uNumAnimSet = m_pAnimCtrl->GetNumAnimationSets();
		
		if (m_uNumAnimSet > 0) 
		{
			//m_ppAnimSet = new LPD3DXANIMATIONSET[m_uNumAnimSet];
			m_pAnim = new HLANIM_DESC[m_uNumAnimSet];

			for (DWORD u = 0; u < m_uNumAnimSet; ++u) {
				//m_pAnimCtrl->GetAnimationSet(u, &m_ppAnimSet[u]);
				m_pAnimCtrl->GetAnimationSet(u, &m_pAnim[u].pAnimSet);
				m_pAnim[u].m_uiAnimID = u;
				m_pAnim[u].fCurWeightTime = 0.0f;
				m_pAnim[u].fLoopTime = 1.0f;
				m_pAnim[u].fShiftTime = 120.0f;
				m_pAnim[u].fTrackSpeed = 1.0f;
				m_uiCurID = u;
			}
		}
	}



	// �o�ߎ��Ԍv���p�����ݒ�
	m_dwPrev = ::timeGetTime();
	return SUCCEEDED(hr);
	//*********************************************
}


//---------------------------------------------------------------------------------------
// ���b�V�����
//---------------------------------------------------------------------------------------
void CMesh::Finalize()
{
	if(m_nMeshType == MESH_N)
	{
		// ���E���C���[�W�̉��
		SAFE_RELEASE(m_pSphere);

		SAFE_DELETE_ARRAY(m_pPiece);
		SAFE_DELETE_ARRAY(m_pPieceVtx);

		SAFE_DELETE_ARRAY(m_pVtx);
		SAFE_DELETE_ARRAY(m_pIdx);

		SAFE_DELETE_ARRAY(m_pAttr);

		// �e�N�X�`�� �I�u�W�F�N�g�����
		if (m_ppTexture) {
			for (DWORD i = 0; i < m_dwNumMaterial; i++) {
				SAFE_RELEASE(m_ppTexture[i]);
			}
			SAFE_DELETE_ARRAY(m_ppTexture);
		}
		SAFE_DELETE_ARRAY(m_pMaterial);

		SAFE_RELEASE(m_pD3DMesh);	// ���b�V�� �I�u�W�F�N�g�����
	}
	
	if(m_nMeshType == MESH_S)
	{
		if (m_pAnim) {
		for (DWORD u = 0; u < m_uNumAnimSet; ++u) {
			SAFE_RELEASE(m_pAnim[u].pAnimSet);
		}
		SAFE_DELETE_ARRAY(m_pAnim);
	}

	SAFE_RELEASE(m_pAnimCtrl);

	// ���b�V���j��
	if (m_pFrameRoot) {
		D3DXFrameDestroy(m_pFrameRoot, &m_Hierarchy);
		m_pFrameRoot = NULL;
	}
	}
	
}

//---------------------------------------------------------------------------------------
// ���b�V���`��
//---------------------------------------------------------------------------------------
void CMesh::Draw(D3DXMATRIX& world)
{
	// ���[���h �}�g���b�N�X�ݒ�
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
    pDevice->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD id = m_pAttr[i].AttribId;
        // �A���t�@�l���`�F�b�N
        D3DMATERIAL9 mtrl = m_pMaterial[id];
		if (mtrl.Diffuse.a < 1.0f)
			continue;
		pDevice->SetMaterial(&mtrl);
		pDevice->SetTexture(0, m_ppTexture[id]);	// �e�N�X�`����ݒ�
//		m_pD3DMesh->DrawSubset(id);								// �`������s
		pDevice->SetFVF(FVF_BVERTEX);
		pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0,
			m_dwVtx, m_pAttr[i].FaceCount, &m_pIdx[m_pAttr[i].FaceStart * 3],
			D3DFMT_INDEX16, m_pVtx, sizeof(BVERTEX));
	}

	// �A���t�@ �u�����h�L����
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD id = m_pAttr[i].AttribId;
        // �A���t�@�l���`�F�b�N
        D3DMATERIAL9 mtrl = m_pMaterial[id];
		if (mtrl.Diffuse.a >= 1.0f)
			continue;
		pDevice->SetMaterial(&mtrl);
		pDevice->SetTexture(0, m_ppTexture[id]);	// �e�N�X�`����ݒ�
		
//		m_pD3DMesh->DrawSubset(id);								// �`������s
		pDevice->SetFVF(FVF_BVERTEX);
		pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0,
			m_dwVtx, m_pAttr[i].FaceCount, &m_pIdx[m_pAttr[i].FaceStart * 3],
			D3DFMT_INDEX16, m_pVtx, sizeof(BVERTEX));
	}

    // �A���t�@ �u�����h������
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CMesh::Draw(D3DXMATRIX& world, float fAlpha)
{
    // ���[���h �}�g���b�N�X�ݒ�
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
    pDevice->SetTransform(D3DTS_WORLD, &world);

    // �A���t�@ �u�����h�L����
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    for (DWORD i = 0; i < m_dwAttr; i++) {
        DWORD id = m_pAttr[i].AttribId;

        // �A���t�@�l��ύX
        D3DMATERIAL9 mtrl = m_pMaterial[id];
        mtrl.Diffuse.a *= fAlpha;
        pDevice->SetMaterial(&mtrl);

        pDevice->SetTexture(0, m_ppTexture[id]);
        pDevice->SetFVF(FVF_BVERTEX);
//		pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0,
//			m_dwVtx, m_pAttr[i].FaceCount, &m_pIdx[m_pAttr[i].FaceStart * 3],
//			D3DFMT_INDEX16, m_pVtx, sizeof(BVERTEX));
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_pAttr[i].FaceCount,
			&m_pPieceVtx[m_pAttr[i].FaceStart * 3],
			sizeof(BVERTEX));
    }

    // �A���t�@ �u�����h������
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
// �f�Ђ̏�����
void CMesh::InitParticle()
{
	// ���_���W�A�e�N�X�`�����W���R�s�[
	for (DWORD i = 0; i < m_dwIdx; ++i) {
		m_pPieceVtx[i].pos = m_pVtx[m_pIdx[i]].pos;
		m_pPieceVtx[i].tex = m_pVtx[m_pIdx[i]].tex;
	}
	D3DXVECTOR3 v0, v1, n;
	for (DWORD i = 0; i < m_dwFace; ++i) {
		// �@���x�N�g���𐶐�
		v0 = m_pPieceVtx[i * 3 + 1].pos
			- m_pPieceVtx[i * 3 + 0].pos;
		v1 = m_pPieceVtx[i * 3 + 2].pos
			- m_pPieceVtx[i * 3 + 1].pos;
		D3DXVec3Cross(&n, &v0, &v1);
		D3DXVec3Normalize(&n, &n);
		m_pPieceVtx[i * 3 + 0].nor = n;
		m_pPieceVtx[i * 3 + 1].nor = n;
		m_pPieceVtx[i * 3 + 2].nor = n;
		// ���x�A�����x�̏�����
		m_pPiece[i].spd = n * INIT_SPD;
		m_pPiece[i].acl =
			D3DXVECTOR3(0.0f, -GRAVITY, 0.0f);
	}
}

// �f�Ђ̈ړ�
bool CMesh::UpdateParticle()
{
	for (DWORD i = 0; i < m_dwFace; ++i) {
		m_pPieceVtx[i * 3 + 0].pos += m_pPiece[i].spd;
		m_pPieceVtx[i * 3 + 1].pos += m_pPiece[i].spd;
		m_pPieceVtx[i * 3 + 2].pos += m_pPiece[i].spd;
		m_pPiece[i].spd += m_pPiece[i].acl;
	}
	m_nBombCnt ++;

	if(m_nBombCnt == 120)
		return true;;

	return false;
}

// ���E���̕`��
void CMesh::DrawSphere(D3DXMATRIX& world, D3DCOLORVALUE color)
{
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	// ���[���h �}�g���b�N�X�ݒ�
	D3DXMATRIX m;
	D3DXMatrixTranslation(&m, m_vCenter.x, m_vCenter.y, m_vCenter.z);
	m *= world;
    pDevice->SetTransform(D3DTS_WORLD, &m);

    // �A���t�@ �u�����h�L����
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    //pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���b�V���`��
	D3DMATERIAL9 mtrl = {
		color,//Diffuse
		color,//Ambient
		{1.0f, 1.0f, 1.0f, 1.0f},//Specular
		{0.0f, 0.0f, 0.0f, 1.0f},//Emissive
		1.0f//Power
	};
	pDevice->SetMaterial(&mtrl);
	pDevice->SetTexture(0, NULL);
	pDevice->SetFVF(D3DFVF_XYZ |
		D3DFVF_NORMAL | D3DFVF_TEX1);
	m_pSphere->DrawSubset(0);

    // �A���t�@ �u�����h������
    //pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

// ���E�{�b�N�X�̕`��
void CMesh::DrawBox(D3DXMATRIX& world, D3DCOLORVALUE color)
{
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	// ���[���h �}�g���b�N�X�ݒ�
	D3DXMATRIX m;
	D3DXMatrixTranslation(&m, m_vCenter.x, m_vCenter.y, m_vCenter.z);
	m *= world;
    pDevice->SetTransform(D3DTS_WORLD, &m);

    // �A���t�@ �u�����h�L����
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ���b�V���`��
	D3DMATERIAL9 mtrl = {
		color,//Diffuse
		color,//Ambient
		{1.0f, 1.0f, 1.0f, 1.0f},//Specular
		{0.0f, 0.0f, 0.0f, 1.0f},//Emissive
		1.0f//Power
	};
	pDevice->SetMaterial(&mtrl);
	pDevice->SetTexture(0, NULL);
	pDevice->SetFVF(D3DFVF_XYZ |
		D3DFVF_NORMAL | D3DFVF_TEX1);
	m_pBox->DrawSubset(0);

    // �A���t�@ �u�����h������
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

//---------------------------------------------------------------------------------------
// ���b�V���s���������̂ݕ`��
//---------------------------------------------------------------------------------------
void CMesh::DrawNoAlpha(D3DXMATRIX& world)
{
	// ���[���h �}�g���b�N�X�ݒ�
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
    pDevice->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD id = m_pAttr[i].AttribId;
        // �A���t�@�l���`�F�b�N
        D3DMATERIAL9 mtrl = m_pMaterial[id];
		if (mtrl.Diffuse.a < 1.0f)
			continue;
		pDevice->SetMaterial(&mtrl);
		pDevice->SetTexture(0, m_ppTexture[id]);	// �e�N�X�`����ݒ�
		m_pD3DMesh->DrawSubset(id);								// �`������s
	}
}

//---------------------------------------------------------------------------------------
// ���b�V�������������̂ݕ`�� (�A���t�@�L����/�������Ȃ�)
//---------------------------------------------------------------------------------------
void CMesh::DrawAlpha(D3DXMATRIX& world)
{
	// ���[���h �}�g���b�N�X�ݒ�
    LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
    pDevice->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD id = m_pAttr[i].AttribId;
        // �A���t�@�l���`�F�b�N
        D3DMATERIAL9 mtrl = m_pMaterial[id];
		if (mtrl.Diffuse.a >= 1.0f)
			continue;
		pDevice->SetMaterial(&mtrl);
		pDevice->SetTexture(0, m_ppTexture[id]);	// �e�N�X�`����ݒ�
		m_pD3DMesh->DrawSubset(id);					// �`������s
	}
}

// ���C�ƃ��b�V���̌�_�����߂�
// true�c��_����Afalse�c��_�Ȃ�
//bool CMesh::Intersect(
//	LPD3DXVECTOR3 pPos,		//�n�_
//	LPD3DXVECTOR3 pDir,		//����
//	LPD3DXVECTOR3 pCross,	//��_
//	LPD3DXVECTOR3 pNormal)	//��_�̖@��
//{
//	// �S�Ă̎O�p�`��T��
//	for (DWORD i = 0; i < m_dwIdx; ) {
//		// �O�p�`��3���_���擾
//		D3DXVECTOR3& v0 = m_pVtx[m_pIdx[i++]].pos;
//		D3DXVECTOR3& v1 = m_pVtx[m_pIdx[i++]].pos;
//		D3DXVECTOR3& v2 = m_pVtx[m_pIdx[i++]].pos;
//		// �O�p�`�̖@���x�N�g�������߂�
//		D3DXVECTOR3 n;
//		D3DXVec3Cross(&n, &(v1 - v0), &(v2 - v1));
//		D3DXVec3Normalize(&n, &n);
//		// �����̃`�F�b�N
//		float base = D3DXVec3Dot(&n, pDir);
//		if (base >= 0.0f) continue;
//		// �O�p�`�̓��O����(���C�ɕ��s�ȎO�p����)
//		D3DXVECTOR3 np;
//		D3DXVec3Cross(&np, &(v1 - v0), pDir);
//		if (D3DXVec3Dot(&np, &(*pPos - v0)) < 0.0f)
//			continue;//���̊O
//		D3DXVec3Cross(&np, &(v2 - v1), pDir);
//		if (D3DXVec3Dot(&np, &(*pPos - v1)) < 0.0f)
//			continue;//���̊O
//		D3DXVec3Cross(&np, &(v0 - v2), pDir);
//		if (D3DXVec3Dot(&np, &(*pPos - v2)) < 0.0f)
//			continue;//���̊O
//		// ��_�̌v�Z
//		float t = D3DXVec3Dot(&n, &(v0 - *pPos)) / base;
//		//if (t < 0.0f) continue;//���C����O
//		//if (t > 1.0f) continue;//���C����
//		// ��_�Ɩ@���x�N�g����Ԃ�
//		if (pCross) *pCross = *pPos + t * *pDir;
//		if (pNormal) *pNormal = n;
//		return true;	// ��_����
//	}
//	return false;	// ��_�Ȃ�
//}

// �A�j���֘A
//---------------------------------------------------------------------------------------
// �t���[���̃}�g���b�N�X���X�V
//---------------------------------------------------------------------------------------
void CMesh::UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	// �e�̃}�g���b�N�X���|�����킹��
	if (pParentMatrix) {
		pFrame->CombinedTransformationMatrix =
			pFrame->TransformationMatrix * *pParentMatrix;
	} else {
		pFrame->CombinedTransformationMatrix =
			pFrame->TransformationMatrix;
	}
	// �Z��t���[��������΃}�g���b�N�X���X�V
	if (pFrame->pFrameSibling) {
		UpdateFrameMatrices(pFrame->pFrameSibling, pParentMatrix);
	}
	// �q�t���[��������΃}�g���b�N�X���X�V
	if (pFrame->pFrameFirstChild) {
		// �������e�ƂȂ�̂ŁA�����̃}�g���b�N�X��n��
		UpdateFrameMatrices(pFrame->pFrameFirstChild,
			&pFrame->CombinedTransformationMatrix);
	}
}

//---------------------------------------------------------------------------------------
// �t���[���̕`��
//---------------------------------------------------------------------------------------
void CMesh::DrawFrame(LPD3DXFRAME pFrame)
{
	LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer) {
		// ���b�V���R���e�i�̕`��
		RenderMeshContainer(pMeshContainer, pFrame);
		// ���̃��b�V���R���e�i
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}
	// �Z��t���[��������ΌZ��t���[����`��
	if (pFrame->pFrameSibling)
		DrawFrame(pFrame->pFrameSibling);
	// �q�t���[��������Ύq�t���[����`��
	if (pFrame->pFrameFirstChild)
		DrawFrame(pFrame->pFrameFirstChild);
}

//---------------------------------------------------------------------------------------
// ���b�V���R���e�i�̕`��
//---------------------------------------------------------------------------------------
void CMesh::RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase)
{
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	if (pMeshContainer->pSkinInfo) {
		// �X�L�����b�V�����f��
		LPD3DXBONECOMBINATION pBoneCombi =
			(LPD3DXBONECOMBINATION)
			pMeshContainer->pBoneBuffer->GetBufferPointer();

		DWORD dwPrevBoneID = UINT_MAX;
		DWORD dwBlendMatrix;
		for (DWORD i = 0; i < pMeshContainer->dwBone; ++i) {
			dwBlendMatrix = 0;
			for (DWORD k = 0; k < pMeshContainer->dwWeight; ++k) {
				if (pBoneCombi[i].BoneId[k] != UINT_MAX)
					dwBlendMatrix = k;
			}
			CGraphics::GetDevice()->SetRenderState(
				D3DRS_VERTEXBLEND, dwBlendMatrix);	// ���_�u�����f�B���O
			for (DWORD k = 0; k < pMeshContainer->dwWeight; ++k) {
				DWORD id = pBoneCombi[i].BoneId[k];
				if (id != UINT_MAX) {
					CGraphics::GetDevice()->SetTransform(
						D3DTS_WORLDMATRIX(k),
						&(pMeshContainer->pBoneOffsetMatrix[id] *
						*pMeshContainer->ppBoneMatrix[id]));
				}
			}
			CGraphics::GetDevice()->SetMaterial(
&pMeshContainer->pMaterials[pBoneCombi[i].AttribId].MatD3D);
			CGraphics::GetDevice()->SetTexture(0,
pMeshContainer->ppTextures[pBoneCombi[i].AttribId]);
			dwPrevBoneID = pBoneCombi[i].AttribId;
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
		return;
	}
	// �X�L���������f��
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &pFrame->CombinedTransformationMatrix);
	for (DWORD iAttrib = 0; iAttrib < pMeshContainer->NumMaterials; ++iAttrib) {
		DWORD dwAttrib = pMeshContainer->pAttributeTable[iAttrib].AttribId;
		CGraphics::GetDevice()->SetMaterial(&pMeshContainer->pMaterials[dwAttrib].MatD3D);
		CGraphics::GetDevice()->SetTexture(0, pMeshContainer->ppTextures[dwAttrib]);
		pMeshContainer->MeshData.pMesh->DrawSubset(dwAttrib);
	}
}

//---------------------------------------------------------------------------------------
// �{�[���p���[���h�E�}�g���b�N�X�̈�m��
//---------------------------------------------------------------------------------------
HRESULT CMesh::AllocBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	MYMESHCONTAINER* pMeshContainer = (MYMESHCONTAINER*)pMeshContainerBase;
	if (pMeshContainer->pSkinInfo == NULL)
		return S_OK;	// �X�L����񂪖�����Ή������Ȃ�
	DWORD dwBoneNum = pMeshContainer->pSkinInfo->GetNumBones();
	pMeshContainer->ppBoneMatrix = new LPD3DXMATRIX[dwBoneNum];
	for (DWORD i = 0; i < dwBoneNum; ++i) {
		MYFRAME* pFrame = (MYFRAME*)D3DXFrameFind(m_pFrameRoot,
			pMeshContainer->pSkinInfo->GetBoneName(i));
		if (pFrame == NULL)
			return E_FAIL;
		pMeshContainer->ppBoneMatrix[i] =
			&pFrame->CombinedTransformationMatrix;
	}
	return S_OK;
}

HRESULT CMesh::AllocAllBoneMatrix(LPD3DXFRAME pFrameBase)
{
	MYFRAME* pFrame = (MYFRAME*)pFrameBase;
	HRESULT hr = S_OK;
	if (pFrame->pMeshContainer) {
		hr = AllocBoneMatrix(pFrame->pMeshContainer);
		if (FAILED(hr))
			return hr;
	}
	if (pFrame->pFrameSibling) {
		hr = AllocAllBoneMatrix(pFrame->pFrameSibling);
		if (FAILED(hr))
			return hr;
	}
	if (pFrame->pFrameFirstChild) {
		hr = AllocAllBoneMatrix(pFrame->pFrameFirstChild);
	}
	return hr;
}

//---------------------------------------------------------------------------------------
// �A�j���[�V�����ؑ�
//---------------------------------------------------------------------------------------
void CMesh::SwitchAnimSet(UINT uAnimSet)
{
	if (uAnimSet >= m_uNumAnimSet || m_pAnimCtrl == NULL) return;
	m_pAnimCtrl->SetTrackAnimationSet(0, m_ppAnimSet[uAnimSet]);
}

//---------------------------------------------------------------------------------------
// �A�j���[�V�����J�n���Ԑݒ�
//---------------------------------------------------------------------------------------
void CMesh::SetTime(double dTime)
{
	if (m_pAnimCtrl == NULL) return;
	for (DWORD i = 0;i < m_pAnimCtrl->GetMaxNumTracks(); ++i) {
		m_pAnimCtrl->SetTrackPosition(i, 0);
	}
	m_pAnimCtrl->ResetTime();
	m_pAnimCtrl->AdvanceTime(dTime, NULL);
}

//---------------------------------------------------------------------------------------
// �A�j���[�V�����R���g���[�����擾
//---------------------------------------------------------------------------------------
void CMesh::GetAnimationController( ID3DXAnimationController **ppAnimCont )
{
		
}

//---------------------------------------------------------------------------------------
// �A�j���[�V�����X�s�[�h�ݒ�ݒ�(�����F�A�j����No,�@�b )
//---------------------------------------------------------------------------------------
void CMesh::SetLoopTime(int nNo, float fSec)
{
	//float fAdj = m_ppAnimSet[nNo]->GetPeriod();
	float fAdj = (float)m_pAnim[nNo].pAnimSet->GetPeriod();

	fAdj /= fSec;
	
	m_pAnimCtrl->SetTrackSpeed(nNo, fAdj);	
}

//---------------------------------------------------------------------------------------
// ����J�n�ɂ����鎞�Ԃ�ݒ�
//---------------------------------------------------------------------------------------
void CMesh::SetShiftTime( UINT animID, FLOAT interval )
{
	// �V�t�g���Ԃ�o�^
	m_pAnim[animID].fShiftTime = interval;

}

//---------------------------------------------------------------------------------------
// �A�j���[�V������؂�ւ�
//---------------------------------------------------------------------------------------
void CMesh::ChangeAnimation( UINT animID )
{
   // �قȂ�A�j���[�V�����ł��邩���`�F�b�N
   if( m_uiCurID == animID )
       return;

    // ���݂̃A�j���[�V�����Z�b�g�̐ݒ�l���擾
   D3DXTRACK_DESC TD;   // �g���b�N�̔\��
   m_pAnimCtrl->GetTrackDesc( 0, &TD );

    // ���̃A�j���[�V�������g���b�N1�Ɉڍs��
   // �g���b�N�̐ݒ�l���ڍs
   m_pAnimCtrl->SetTrackAnimationSet( 1, m_pAnim[m_uiCurID].pAnimSet);
   m_pAnimCtrl->SetTrackDesc( 1, &TD );

    // �V�����A�j���[�V�����Z�b�g���g���b�N0�ɐݒ�
   m_pAnimCtrl->SetTrackAnimationSet( 0, m_pAnim[animID].pAnimSet );

    // �g���b�N0�̃X�s�[�h�̐ݒ�
   m_pAnimCtrl->SetTrackSpeed( 0, m_pAnim[animID].fTrackSpeed );

    // �g���b�N�̍���������
   m_pAnimCtrl->SetTrackEnable( 0, true );
   m_pAnimCtrl->SetTrackEnable( 1, true );

    // �E�F�C�g���Ԃ�������
   m_pAnim[animID].fCurWeightTime = 0.0f;

    // ���݂̃A�j���[�V�����ԍ���؂�ւ�
   m_uiPreID = m_uiCurID;
   m_uiCurID = animID;

	
}

//---------------------------------------------------------------------------------------
// �A�j���[�V�������X�V
//---------------------------------------------------------------------------------------
void CMesh::AdvanceTime( FLOAT time )
{
	// ���������ۂ��𔻒�
   m_pAnim[m_uiCurID].fCurWeightTime += time;
    if( m_pAnim[m_uiCurID].fCurWeightTime <= m_pAnim[m_uiCurID].fShiftTime )
    {
       // �������B�E�F�C�g���Z�o
      FLOAT Weight = m_pAnim[m_uiCurID].fCurWeightTime / m_pAnim[m_uiCurID].fShiftTime;
       // �E�F�C�g��o�^
      m_pAnimCtrl->SetTrackWeight( 0, Weight );       // ���݂̃A�j���[�V����
     m_pAnimCtrl->SetTrackWeight( 1, 1 - Weight );   // �O�̃A�j���[�V����
   }
    else
    {
       // �����I�����B�ʏ�A�j���[�V����������Track0�̃E�F�C�g���ő�l��
      m_pAnimCtrl->SetTrackWeight( 0, 1.0f );       // ���݂̃A�j���[�V����
	  m_pAnimCtrl->SetTrackEnable( 1, false );      // �O�̃A�j���[�V�����𖳌��ɂ���
   }

    // ���Ԃ��X�V
	m_pAnimCtrl->AdvanceTime( time, NULL );

}

//---------------------------------------------------------------------------------------
// ���b�V���`��
//---------------------------------------------------------------------------------------
void CMesh::DrawSkin(D3DXMATRIX& world)
{
	// �A�j���[�V�����X�V
	DWORD dwNow = ::timeGetTime();
	double d = (dwNow - m_dwPrev) / 1000.0;
	m_dwPrev = dwNow;
	//if(m_pAnimCtrl)
		//m_pAnimCtrl->AdvanceTime(d, NULL);
	AdvanceTime((float)d);

	// �}�g���b�N�X�X�V
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &world);
	if (m_pFrameRoot) {
		UpdateFrameMatrices(m_pFrameRoot, &world);
		// �t���[���`��
		DrawFrame(m_pFrameRoot);
	}
}

// ���C�ƃ��b�V���̌�_�����߂�
// true�c��_����Afalse�c��_�Ȃ�
bool CMesh::Intersect(
	LPD3DXVECTOR3 pPos,		//�n�_
	LPD3DXVECTOR3 pDir,		//����
	LPD3DXVECTOR3 pCross,	//��_
	LPD3DXVECTOR3 pNormal)	//��_�̖@��
{
	// �S�Ă̎O�p�`��T��
	for (DWORD i = 0; i < m_dwIdx; ) {
		// �O�p�`��3���_���擾
		D3DXVECTOR3& v0 = m_pVtx[m_pIdx[i++]].pos;
		D3DXVECTOR3& v1 = m_pVtx[m_pIdx[i++]].pos;
		D3DXVECTOR3& v2 = m_pVtx[m_pIdx[i++]].pos;
		// �O�p�`�̖@���x�N�g�������߂�
		D3DXVECTOR3 n;
		D3DXVec3Cross(&n, &(v1 - v0), &(v2 - v1));
		D3DXVec3Normalize(&n, &n);
		// �����̃`�F�b�N
		float base = D3DXVec3Dot(&n, pDir);
		if (base >= 0.0f) continue;
		// �O�p�`�̓��O����(���C�ɕ��s�ȎO�p����)
		D3DXVECTOR3 np;
		D3DXVec3Cross(&np, &(v1 - v0), pDir);
		if (D3DXVec3Dot(&np, &(*pPos - v0)) < 0.0f)
			continue;//���̊O
		D3DXVec3Cross(&np, &(v2 - v1), pDir);
		if (D3DXVec3Dot(&np, &(*pPos - v1)) < 0.0f)
			continue;//���̊O
		D3DXVec3Cross(&np, &(v0 - v2), pDir);
		if (D3DXVec3Dot(&np, &(*pPos - v2)) < 0.0f)
			continue;//���̊O
		// ��_�̌v�Z
		float t = D3DXVec3Dot(&n, &(v0 - *pPos)) / base;
		//if (t < 0.0f) continue;//���C����O
		//if (t > 1.0f) continue;//���C����
		// ��_�Ɩ@���x�N�g����Ԃ�
		if (pCross) *pCross = *pPos + t * *pDir;
		if (pNormal) *pNormal = n;
		return true;	// ��_����
	}
	return false;	// ��_�Ȃ�
}

//=======================================================================================
//	End of File
//=======================================================================================