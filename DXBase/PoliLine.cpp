#include "PoliLine.h"
#include "SceneBase.h"
#include "Camera.h"

#define ADD_RATE (1.0f / LINEPOINT_MAX)

CPoliLine::CPoliLine(void)
{
}


CPoliLine::~CPoliLine(void)
{
}

CPoliLine* CPoliLine::Create(int nTexNum, D3DXVECTOR3 vInitPos, D3DXVECTOR3 vDestPos, float fWidth)
{
	CPoliLine*	pLine = new CPoliLine();

	pLine->m_vInitPos = vInitPos;
	pLine->m_vDestPos = vDestPos;
	pLine->m_fLineWidth = fWidth;

	pLine->Initialize(nTexNum);
	
	return pLine;
}

void CPoliLine::Initialize(int nImage)
{
	// �e�N�X�`���ݒ�
	m_Board.Initialize(nImage);

	// �X�e�[�^�X������

	// ���ԓ_
	CalcLine();

	// �i�s�����x�N�g��
	CalcDirVec();

	// �J�����ւ̕����x�N�g��
	CalcCameraVec();

	// �L��������̃x�N�g��
	CalcDiffVec();

	// �l�p�`�ւƍL����
	CalcSquare();

	D3DXMatrixIdentity(&m_world);

}

// �X�V
void CPoliLine::Update()
{
	SetPosLine();
}

void CPoliLine::DrawSetUp()
{
	// �J�����O�I�t
	CGraphics::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ���C�g�I�t
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	if(m_bAlphaBlend)
	{
		CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z�o�b�t�@���X�V

		CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		CGraphics::GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		CGraphics::GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	
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
}

void CPoliLine::DrawEnd()
{
	// ���C�g�I��
	CGraphics::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);

	CGraphics::GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	CGraphics::GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		// Z�o�b�t�@���X�V����

	//CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//CGraphics::GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

// �`��
void CPoliLine::Draw()
{
	//// ���[���h�}�g���b�N�X���Z�b�g
	if (m_world) 
		CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);

	// �`��
	CGraphics::GetDevice()->SetFVF(FVF_DVERTEX);
	CGraphics::GetDevice()->SetTexture(0, m_Board.m_pImage->GetTexture());						// �e�N�X�`����o�^

	CGraphics::GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, (LINEPOINT_MAX * 2) - 2, m_verWk, sizeof(DVERTEX));// �|���S���`��

}

// ���C���v�Z
void CPoliLine::CalcLine()
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vVec = m_vDestPos - m_vInitPos;		// �����x�N�g��

	// �n�_�I�_���璆�ԓ_�v�Z
	for(int i = 0; i < LINEPOINT_MAX; i ++)
	{
		vPos = vVec * m_fRate;					// �ړ���
		m_vLinePos[i] = m_vInitPos + vPos;		// �ړ�
		m_fRate += ADD_RATE;					// ���[�g�X�V
	}
}

// �i�s�����v�Z
void CPoliLine::CalcDirVec()
{
	D3DXVECTOR3 vVec;		// ���[�N

	// �i�s�����̃x�N�g�����擾
	for(int i = 0; i < LINEPOINT_MAX - 1; i ++)
	{
		vVec = m_vLinePos[i + 1] - m_vLinePos[i];		// �����x�N�g���v�Z
		D3DXVec3Normalize(&vVec, &vVec);		// �P�ʉ�
		m_vDirVec[i] = vVec;		
	}

	// �I�_�ɂ͈�O�Ɠ������̂�
	m_vDirVec[LINEPOINT_MAX - 1] = m_vDirVec[LINEPOINT_MAX - 2];
}

// �J�����ւ̃x�N�g���v�Z
void CPoliLine::CalcCameraVec()
{
	// �J�����̍��W���擾
	D3DXVECTOR3 vCamPos = CCamera::GetThis()->GetPos();
	D3DXVECTOR3 vVec;
	// �e�_����J�����̕����ւ̃x�N�g�����v�Z
	for(int i = 0; i < LINEPOINT_MAX; i ++)
	{
		vVec = vCamPos - m_vLinePos[i];
		D3DXVec3Normalize(&vVec, &vVec);		// �P�ʉ�
		m_vCameraVec[i] = vVec;
	}

}

// �g�U�����v�Z
void CPoliLine::CalcDiffVec()
{
	D3DXVECTOR3 vVec;

	// �i�s�����ƃJ���������̃x�N�g���̊O�ς��琂���̃x�N�g�����v�Z
	for(int i = 0; i < LINEPOINT_MAX; i ++)
	{
		D3DXVec3Cross(&vVec, &m_vDirVec[i], &m_vCameraVec[i]);
		D3DXVec3Normalize(&vVec, &vVec);		// �P�ʉ�
		m_vDiffVec[i] = vVec;
	}
}

// �l�p�`�v�Z
void CPoliLine::CalcSquare()
{
	float fW = m_fLineWidth;
	float fU = 1.0f / (float)((LINEPOINT_MAX -1));
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vMov;
	D3DXVECTOR3 vMovDir, vMovDiff, vVec;

	vPos = m_vLinePos[0];

	for(int i = 0; i < LINEPOINT_MAX; i ++)
	{
		
		vMovDir.x = fW * m_vDirVec[i].x;
		vMovDir.y = fW * m_vDirVec[i].y;
		vMovDir.z = fW * m_vDirVec[i].z;
		
		vMovDiff.x = fW * m_vDiffVec[i].x;
		vMovDiff.y = fW * m_vDiffVec[i].y;
		vMovDiff.z = fW * m_vDiffVec[i].z;

		// ����̈ړ���
		vVec = /*vMovDir +*/ vMovDiff;
		
		m_verWk[i * 2    ].x = vPos.x + vVec.x;
		m_verWk[i * 2    ].y = vPos.y + vVec.y;
		m_verWk[i * 2    ].z = vPos.z + vVec.z;
		
		m_verWk[i * 2 + 1].x = vPos.x - vVec.x;
		m_verWk[i * 2 + 1].y = vPos.y - vVec.y;
		m_verWk[i * 2 + 1].z = vPos.z - vVec.z;

		m_verWk[i * 2    ].nx = 0.0f;
		m_verWk[i * 2    ].ny = 0.0f;
		m_verWk[i * 2    ].nz = -1.0f;
		
		m_verWk[i * 2 + 1].nx = 0.0f;
		m_verWk[i * 2 + 1].ny = 0.0f;
		m_verWk[i * 2 + 1].nz = -1.0f;
		
		

		//���_�J���[�E���`�����l���̐ݒ�
		m_verWk[i * 2    ].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		m_verWk[i * 2 + 1].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		//m_vLineWk[i * 4 + 2].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		//m_vLineWk[i * 4 + 3].diffuse = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

		//�e�N�X�`�����W�̐ݒ�
		
		m_verWk[i * 2    ].tu = fU * i;
		m_verWk[i * 2    ].tv = 0.0f;
		m_verWk[i * 2 + 1].tu = fU * i;
		m_verWk[i * 2 + 1].tv = 1.0f;
		//m_vLineWk[i * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//m_vLineWk[i * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// �����o���܂ł̎��Ԃ�ݒ�
		m_Point[i * 2    ].m_nTimer = 20 * i;
		m_Point[i * 2 + 1].m_nTimer = 20 * i;
		
	}

	// 
}

void CPoliLine::SetPosLine()
{
	for(int i = 0; i < LINEPOINT_MAX * 2; i++)
	{
		m_verWk[i].x = m_verWk[i].x + 1.0f;
	}
}
