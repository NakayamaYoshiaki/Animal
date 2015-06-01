// ���[�t�B���O�I�u�W�F�N�g�x�[�X�N���X
#pragma once
#include "object3d.h"

#define MORPMODEL_MAX	(10)	// �o�^�ł��郂�f���� 

struct MORPH_VERTEX {
	float x, y, z;				// ���_���W�i���W�ϊ�����j
	D3DXVECTOR3	vNromVec;			// �@���x�N�g��
	float		tu, tv;				// �e�N�X�`�����W
};
#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

//----- �\���̒�`
struct MORPH_OBJECT {			//--- �I�u�W�F�N�g�p�\����
	int			status;				// �X�e�[�^�X
	float		x, y, z;			// ���W
	float		rotx, roty, rotz;	// �p�x
	D3DXMATRIX	matrix;				// �ϊ��}�g���b�N�X
	int			morph_count;		// ���[�t�B���O�v�Z�p���ԃJ�E���g�l
	int			morph_dir;			// ���[�t�B���O�̕���
	int			morph_time[2];		// ���[�t�B���O�ɗv���鎞��
	int			StopCnt;			// ��ԗ��߃J�E���^
};

class CMorphing :
	public CObject3D
{
protected:
	// ���[�t�B���O�p���b�V������
	CMesh m_pMorpMesh[MORPMODEL_MAX];

	// ���[�t�B���O�ɕK�v�ȃX�e�[�^�X
	int m_nMorpMeshNum;		// �o�^���Ă郁�b�V����
	int m_nPrevID;			// �ό`���̃��b�V��ID
	int m_nNextID;			// �ό`��̃��b�V��ID

	// ���[�t�B���O�p�ۑ��f�[�^
	LPDIRECT3DTEXTURE9			m_pD3DTexture;			// Direct3DTexture8 �I�u�W�F�N�g
	MORPH_OBJECT	m_Obj;							// �I�u�W�F�f�[�^
	MORPH_VERTEX*	m_pVertex[MORPMODEL_MAX];		// ���_�f�[�^
	WORD*			m_dwIndex[MORPMODEL_MAX];		// �C���f�b�N�X
	int				m_nVertexNum[MORPMODEL_MAX];		// ���_��
	int				m_nFaceNum[MORPMODEL_MAX];		// �ʐ�
	MORPH_VERTEX*	m_pMorph_Vertex;				// ���[�t�B���O�p���_�f�[�^
	WORD*			m_pwMorph_Index;					// ���[�t�B���O�p�C���f�b�N�X

private:


public:
	CMorphing(void);
	CMorphing(int n);
	virtual ~CMorphing(void);

	virtual void InitializeMorph(int nMeshNum);

	void UpdateMorph();
	virtual void Update();
	virtual void Draw();
	virtual void Release(){};
};

