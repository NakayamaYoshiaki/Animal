// �J���� �N���X��`
#pragma once

#include <d3d9.h>	// DirectX Graphics �֘A�̃w�b�_
#include <d3dx9.h>	// DirectX Graphics �֘A�̃w�b�_

// �J�������
enum ECameraType {
	CT_FIXED = 0,		// ��_
	CT_FIRSTPERSON,		// ��l��
	CT_THIRDPERSON,		// �O�l��

	MAX_CT				// �J������ʐ�
};

// �J�������o�^�C�v
enum
{
	C_EFFECT_NORMAL = 0,
	C_EFFECT_ROUND,

	C_EFFECT_ALL
};

// �J����
class CCamera
{
public:
	CCamera(void);
	virtual ~CCamera(void);

private:
	static CCamera* m_pThis;

	int			m_nEffectType;

	D3DXVECTOR3	m_vPos;		// ���_���W
	D3DXVECTOR3	m_vLook;	// �������W
	D3DXVECTOR3	m_vUp;		// �����
	int			m_nType;	// �J�������
	D3DXVECTOR3	m_vNewPos;	// �����_���W
	D3DXVECTOR3	m_vNewLook;	// ���������W
	D3DXVECTOR3	m_vNewUp;	// �������
	D3DXVECTOR3 m_vAngle;	// �p�x

	D3DXMATRIX  m_matView;	// �r���[�}�g���b�N�X

	D3DXVECTOR3 m_vAdPos;	// �J�����ʒu����
	D3DXVECTOR3	m_vAdLook;

public:
	void Update(D3DXMATRIX* pBase);
	void Draw(void);
	D3DXVECTOR3& GetPos() {return m_vPos;};
	D3DXMATRIX GetMatView(){return m_matView;};

	// �Z�b�^�[
	void SetAdjustPos(D3DXVECTOR3 vPos){m_vAdPos = vPos;};		// �J�������W�Z�b�g
	void SetLookPos(D3DXVECTOR3 vPos){m_vAdLook = vPos;};
	void SetEffect(int nType){m_nEffectType = nType;};

	void UpdateEffect();		// �G�t�F�N�g�X�V�܂Ƃ�
	void Round();				// ��]

	// �Q�b�^�[
	static CCamera* GetThis(){return m_pThis;};
};

