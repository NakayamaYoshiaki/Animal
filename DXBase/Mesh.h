//=======================================================================================
//
//	  ���b�V�� �N���X��`
//
//=======================================================================================
#pragma once
#include <windows.h>		// Windows�v���O�����ɂ͂����t����
#include <tchar.h>			// �ėp�e�L�X�g �}�b�s���O
#include <d3d9.h>			// DirectX Graphics �֘A�̃w�b�_
#include <d3dx9.h>			// DirectX Graphics �֘A�̃w�b�_
#include <dxerr.h>			// DirectX Graphics �֘A�̃w�b�_

#include "MyHierarchy.h"

//enum
//{
//	MESH_PLAYER,
//	MESH_ENEMY,
//	MESH_SKY,
//	MESH_BULLET,
//
//
//
//	MAX_MESH
//};

struct BVERTEX {
	D3DXVECTOR3	pos;
	D3DXVECTOR3	nor;
	D3DXVECTOR2	tex;
};
#define FVF_BVERTEX		(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

struct PARTICLE {
	D3DXVECTOR3 acl;	// �����x
	D3DXVECTOR3 spd;	// ���x
};

#define INIT_SPD	3.0f	// ����(�v����)
#define GRAVITY		0.098f	// �d�͉����x(�v����)

// �A�j���[�V�����X�e�[�^�X
struct HLANIM_DESC
{
	UINT m_uiAnimID;                 // �A�j���[�V����ID
	ID3DXAnimationSet *pAnimSet;   // �A�j���[�V�����Z�b�g
	FLOAT fLoopTime;               // 1���[�v�̎���
	FLOAT fTrackSpeed;             // �g���b�N�X�s�[�h���ߒl
	FLOAT fShiftTime;              // �V�t�g����̂ɂ����鎞��
	FLOAT fCurWeightTime;          // ���݂̃E�F�C�g����
};

enum
{
	MESH_N,
	MESH_S,
};

class CMesh
{
private:
	int		m_nMeshType;

	// �A�j���֘A
	LPD3DXFRAME					m_pFrameRoot;	// ���[�g �t���[�� �I�u�W�F�N�g
	LPD3DXANIMATIONCONTROLLER	m_pAnimCtrl;	// �A�j���[�V���� �R���g���[�� �I�u�W�F�N�g
	UINT						m_uNumAnimSet;	// �A�j���[�V���� �Z�b�g��
	LPD3DXANIMATIONSET*			m_ppAnimSet;	// �A�j���[�V���� �Z�b�g
	CMyHierarchy				m_Hierarchy;	// �K�w�������m��/����N���X
	DWORD						m_dwPrev;		// ���O�̎���
	HLANIM_DESC*				m_pAnim;			// �A�j���p�����[�^
	UINT m_uiPreID;			// �O��h�c
	UINT m_uiCurID;			 // ���݃A�j��ID

	//---------------------------------------------------------------------------------------

	LPD3DXMESH			m_pD3DMesh;			// D3DXMesh �I�u�W�F�N�g
	DWORD				m_dwNumMaterial;	// �}�e���A����
	D3DMATERIAL9*		m_pMaterial;		// �}�e���A��
	LPDIRECT3DTEXTURE9*	m_ppTexture;		// �e�N�X�`��

	D3DXATTRIBUTERANGE*	m_pAttr;			// �����e�[�u��
	DWORD				m_dwAttr;			// ������
	DWORD				m_dwVtx;			// ���_��
	BVERTEX*			m_pVtx;				// ���_�z��
	DWORD				m_dwIdx;			// �C���f�b�N�X��
	WORD*				m_pIdx;				// �C���f�b�N�X�z��

	D3DXVECTOR3			m_vHalf;			// ���E�{�b�N�X �n�[�t�T�C�Y
	D3DXVECTOR3			m_vCenter;			// ���E�{�b�N�X(���E��)���S���W
	float				m_fRadius;			// ���E�����a
	LPD3DXMESH			m_pSphere;			// ���E���\���p���b�V��
	LPD3DXMESH			m_pBox;				// ���E�{�b�N�X�\���p���b�V��

	PARTICLE*			m_pPiece;			// �f�Ђ̐���p
	BVERTEX*			m_pPieceVtx;
	DWORD				m_dwFace;			// �ʐ�

	int					m_nBombCnt;

public:
	// �A�j���֘A
	void SwitchAnimSet(UINT uAnimSet);		// �A�j���[�V�����ؑ�
	void SetTime(double dTime);				// �A�j���[�V�����J�n���Ԑݒ�
	void SetAnimationController(ID3DXAnimationController* pAnimCont);// �A�j���[�V�����R���g���[����ݒ�
	void GetAnimationController( ID3DXAnimationController **ppAnimCont );// �A�j���[�V�����R���g���[�����擾
	void SetLoopTime(int nNo, float fSec);	// �A�j���[�V�����̃X�s�[�h�ݒ�
	void SetShiftTime( UINT animID, FLOAT interval );// ����J�n�ɂ����鎞�Ԃ�ݒ�
	void ChangeAnimation( UINT animID );// �A�j���[�V������؂�ւ�
	void AdvanceTime( FLOAT time );// �A�j���[�V�������X�V


	CMesh();								// �R���X�g���N�^
	virtual ~CMesh();						// �f�X�g���N�^
	bool Initialize(LPCTSTR pszFName, int nType);		// ���b�V��������
	bool InitializeNorm(LPCTSTR pszFName);
	bool InitializeSkin(LPCTSTR pszFName);	// �X�L�����b�V��������
	void Finalize();						// ���b�V�����
	void Draw(D3DXMATRIX& world);			// ���b�V���`��
	void Draw(D3DXMATRIX& world, float fAlpha);
	void DrawSkin(D3DXMATRIX& world);		// �X�L���A�j���p�`��
	DWORD GetNumVertex() {return m_dwVtx;}	// ���_���擾
	BVERTEX* GetVertex() {return m_pVtx;}	// ���_�z��擾
	DWORD GetNumIndex() {return m_dwIdx;}	// �C���f�b�N�X���擾
	WORD* GetIndex() {return m_pIdx;}		// �C���f�b�N�X�z��擾
	DWORD GetFaceNum(){return m_dwFace;};
	D3DXVECTOR3& GetHalfSize() {return m_vHalf;}	// �{�b�N�X�n�[�t�T�C�Y�擾
	D3DXVECTOR3& GetCenter() {return m_vCenter;}	// ���E�{�b�N�X/�����S���W�擾
	float GetRadius() {return m_fRadius;}	// ���E�����a�擾
	void InitParticle();					// �f�Ђ̏�����
	bool UpdateParticle();					// �f�Ђ̈ړ�
	void DrawSphere(D3DXMATRIX& world, D3DCOLORVALUE color);
	void DrawBox(D3DXMATRIX& world, D3DCOLORVALUE color);

	void DrawNoAlpha(D3DXMATRIX& world);
	void DrawAlpha(D3DXMATRIX& world);

	// �ǉ��Q�b�^�[
	LPD3DXMESH GetBaseMesh(){return m_pD3DMesh;};

	// �����蔻��
	bool CMesh::Intersect(LPD3DXVECTOR3 pPos,		//�n�_
						 LPD3DXVECTOR3 pDir,		//����
						 LPD3DXVECTOR3 pCross,	    //��_
						 LPD3DXVECTOR3 pNormal);    //��_�̖@��
private:
	// �A�j���֘A
	void RenderMeshContainer(LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase);
	void UpdateFrameMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
	void DrawFrame(LPD3DXFRAME pFrame);
	HRESULT AllocBoneMatrix(LPD3DXMESHCONTAINER pMeshContainerBase);
	HRESULT AllocAllBoneMatrix(LPD3DXFRAME pFrameBase);

};

//=======================================================================================
//	End of File
//=======================================================================================