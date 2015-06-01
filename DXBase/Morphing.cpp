#include "Morphing.h"

#define STOP_CNT (120)
#define MORPH_TIME (300)
CMorphing::CMorphing(void)
{
}

CMorphing::~CMorphing(void)
{
}

//----------------------------
// ������
// -------------------------------
void CMorphing::InitializeMorph(int nMeshNum)
{
	// �ό`�X�^�[�g�n�_
	m_nPrevID = 0;
	m_nNextID = 1;


	// �ʒu�̏�����
	m_Obj.x  = m_world._41;		m_Obj.y  = m_world._42;		m_Obj.z  = m_world._43;
	// ��]�p�̏�����
	m_Obj.rotx = 0.0;		m_Obj.roty = 0.0;		m_Obj.rotz = 0.0;
	// ���[�t�B���O�p�ϐ��̏�����
	m_Obj.morph_dir = 0;
	m_Obj.morph_count = 0;
	m_Obj.morph_time[0] = 0;
	m_Obj.morph_time[1] = MORPH_TIME;	// �����ŕό`���Ԃ����܂�
	m_Obj.status = 1;
	m_Obj.StopCnt = STOP_CNT;
		// THRU

	LPD3DXMESH				mesh;			// ���b�V���I�u�W�F�N�g
	LPDIRECT3DVERTEXBUFFER9	vertex_buffer;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	index_buffer;	// �C���f�b�N�X�o�b�t�@

	DWORD			dwNumMaterials = 0L;
//    LPD3DXBUFFER	pD3DXMtrlBuffer, pD3DXEffectInst;
	MORPH_VERTEX*	pVertices;		// ���_�f�[�^�ւ̃|�C���^
	WORD*			pIndices;		// �|���S���\���i���_�����N�j�f�[�^�ւ̃|�C���^
	MORPH_VERTEX*	pVertices_2;
	WORD*			pIndices_2;

	//static LPCTSTR filename[] = {
	//	_T("box.x"), _T("box1.x")		// ���f���i�w�t�@�C���j�̃t�@�C�����i�Q�j
	//};
	int			i;

	for (i = 0; i < nMeshNum; i++) {
	    // �w�t�@�C�����烁�b�V���f�[�^��ǂݍ���
		//D3DXLoadMeshFromX(filename[i], D3DXMESH_SYSTEMMEM, g_pD3DDevice, NULL,	// �����łw�t�@�C�����w��
			//&pD3DXMtrlBuffer, &pD3DXEffectInst, &dwNumMaterials, &mesh);
		
		// �x�[�X���b�V���擾
		mesh = m_pMorpMesh[i].GetBaseMesh();


		mesh->GetVertexBuffer(&vertex_buffer);	// ���_�o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^���Q�b�g
		mesh->GetIndexBuffer(&index_buffer);	// �C���f�b�N�X�o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^���Q�b�g
		m_nVertexNum[i] = m_pMorpMesh[i].GetNumVertex();	// ���_�����Q�b�g
		m_nFaceNum[i]  = m_pMorpMesh[i].GetFaceNum();		// �ʐ����Q�b�g

		// ���_�f�[�^�A�C���f�b�N�X�f�[�^���������ɃR�s�[
		m_pVertex[i] = new MORPH_VERTEX[m_nVertexNum[i]];						// ���_���[�N�̈���m��
		m_dwIndex[i]  = new WORD[m_nFaceNum[i]*3];							// �C���f�b�N�X���[�N�̈���m��
		
		pVertices_2 = m_pVertex[i];
		vertex_buffer->Lock(0, 0, (void**)&pVertices, 0);				// ���_�o�b�t�@�����b�N
		memcpy(pVertices_2, pVertices, sizeof(MORPH_VERTEX)*m_nVertexNum[i]);	// ���_�f�[�^�����[�N�ɃR�s�[
		vertex_buffer->Unlock();										// ���_�o�b�t�@���A�����b�N

		pIndices_2 = m_dwIndex[i];
		index_buffer ->Lock(0, 0, (void**)&pIndices , 0);				// �C���f�b�N�X�o�b�t�@�����b�N
		memcpy(pIndices_2, pIndices, sizeof(WORD)*m_nFaceNum[i]*3);		// �C���f�b�N�X�f�[�^�����[�N�ɃR�s�[
		index_buffer ->Unlock();										// �C���f�b�N�X�o�b�t�@���A�����b�N
	}

	// ���[�t�B���O�p�ɒ��_�o�b�t�@�A�C���f�b�N�X�o�b�t�@���쐬
	m_pMorph_Vertex = new MORPH_VERTEX[m_nVertexNum[0]];						// ���[�t�B���O�p���_���[�N�̈���m��
	m_pwMorph_Index  = new WORD[m_nFaceNum[0]*3];							// ���[�t�B���O�p�C���f�b�N�X���[�N�̈���m��

	vertex_buffer->Lock(0, 0, (void**)&pVertices, 0);				// ���_�o�b�t�@�����b�N
	memcpy(m_pMorph_Vertex, pVertices, sizeof(MORPH_VERTEX)*m_nVertexNum[0]);	// ���_�f�[�^�����[�N�ɃR�s�[
	vertex_buffer->Unlock();										// ���_�o�b�t�@���A�����b�N
	index_buffer ->Lock(0, 0, (void**)&pIndices , 0);				// �C���f�b�N�X�o�b�t�@�����b�N
	memcpy(m_pwMorph_Index, pIndices, sizeof(WORD)*m_nFaceNum[0]*3);		// �C���f�b�N�X�f�[�^�����[�N�ɃR�s�[
	index_buffer ->Unlock();										// �C���f�b�N�X�o�b�t�@���A�����b�N

}

//----------------------------------------
// ���[�t�B���O���ԃf�[�^�쐬
//----------------------------------------
void CMorphing::UpdateMorph()
{
	D3DXMATRIX	matRotateX, matRotateY, matRotateZ;	// ��]�}�g���b�N�X�i�R��j
	D3DXMATRIX	matTrans;							// ���s�ړ��}�g���b�N�X
	MORPH_OBJECT*		pt;									// �I�u�W�F�N�g�ւ̃|�C���^

	//�@�i�P�j�ό`�O���f���̒��_�ւ̃|�C���^�ipt_vertex[0]�j
	//�@�@�@�@�ό`�ヂ�f���̒��_�ւ̃|�C���^�ipt_vertex[1]�j
	//�@�@�@�@�v�Z�ヂ�f���̒��_�ւ̃|�C���^�imorph_vertex�j�����[�N�ϐ��ɃZ�b�g
	MORPH_VERTEX* pt1		= m_pVertex[m_nPrevID];
	MORPH_VERTEX* pt2		= m_pVertex[m_nNextID];
	MORPH_VERTEX* ptWk		= m_pMorph_Vertex;

	//----- �����{��
	pt = &m_Obj;
	

#define ROTATE_SPEED (0.04f)
	// �L�[���͂ɂ���]
	//if (GetAsyncKeyState(VK_UP   ) & 0x8000)
		pt->rotx += ROTATE_SPEED;	// �J�[�\���i��j
	if (GetAsyncKeyState(VK_DOWN ) & 0x8000) 
		pt->rotx -= ROTATE_SPEED;	// �J�[�\���i���j
	//if (GetAsyncKeyState(VK_LEFT ) & 0x8000)
		pt->roty -= ROTATE_SPEED * 2;	// �J�[�\���i���j
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) 
		pt->roty += ROTATE_SPEED;	// �J�[�\���i�E�j
	//if (GetAsyncKeyState(VK_PRIOR) & 0x8000) 
		pt->rotz += ROTATE_SPEED;	// Page Up
	if (GetAsyncKeyState(VK_NEXT ) & 0x8000) 
		pt->rotz -= ROTATE_SPEED;	// Page Down
	// �}�g���b�N�X������
	D3DXMatrixRotationX(&matRotateX, pt->rotx);							// �w����]�}�g���b�N�X�𐶐�
	D3DXMatrixRotationY(&matRotateY, pt->roty);							// �x����]�}�g���b�N�X�𐶐�
	D3DXMatrixRotationZ(&matRotateZ, pt->rotz);							// �y����]�}�g���b�N�X�𐶐�
	D3DXMatrixTranslation(&matTrans, pt->x, pt->y, pt->z);				// ���s�ړ��}�g���b�N�X�𐶐�
	m_world = matRotateX * matRotateY * matRotateZ * matTrans;		// �}�g���b�N�X�������i�����ɒ��ӁI�j

	//**************************************************************************
	//
	//�@�����Ƀ��[�t�B���O�̌v�Z������ǉ�����B
	//
	
		

	for(int i = 0; i < m_nVertexNum[m_nPrevID]; i ++)
	{
		//�@�i�Q�j�ό`�O�̎��Ԃƕό`��̎��Ԃƌ��݂̎��Ԃ��犄�������߂�
		float t = (float)m_Obj.morph_count;
		float t0 = (float)m_Obj.morph_time[0];
		float t1 = (float)m_Obj.morph_time[1]; 
		float trate = (float)((t - t0) / (t1 - t0));
			

		//�@�i�R�j�����ƕό`�O��̍��W�̍�������ό`�ʂ����߂�
		float x, y, z;
		x = pt1->x + (pt2->x - pt1->x) * trate;
		y = pt1->y + (pt2->y - pt1->y) * trate;
		z = pt1->z + (pt2->z - pt1->z) * trate;

		//�@�i�S�j�v�Z�ヂ�f���̒��_���[�N�Ɋi�[
		ptWk->x = x;
		ptWk->y = y;
		ptWk->z = z;
			
		//�@�i�T�j�|�C���^�����ꂼ��{�P
		pt1 ++;
		pt2 ++;
		ptWk ++;

		//�@�i�U�j�ȏ�̏����𒸓_���������[�v���đS�Ă̒��_����������

	}
	//
	//�@���⑫
	//�@�@�ό`�O�̎���    g_Object.morph_time[0]
	//�@�@�ό`��̎���    g_Object.morph_time[1]
	//�@�@���݂̎���      g_Object.morph_count
	//
	//**************************************************************************



	switch (pt->morph_dir) 
	{
	case 0:			// 0 > 1
		if(++(pt->morph_count) >= pt->morph_time[1]) 
		{
			pt->morph_dir = 1;	// �����𔽓]
			/*m_nPrevID = (m_nPrevID + 1) % m_nMorpMeshNum;
			m_nNextID = (m_nNextID + 1) % m_nMorpMeshNum;
			pt->morph_count = 0;*/
		}
		break;
	case 1:			// 1 > 0
		if(--(pt->StopCnt) <= 0                ) 
		{
			pt->morph_dir = 0;	// �����𔽓]
			m_nPrevID = (m_nPrevID + 1) % m_nMorpMeshNum;
			m_nNextID = (m_nNextID + 1) % m_nMorpMeshNum;
			pt->morph_count = 0;
			pt->StopCnt = STOP_CNT;
		}
		break;
	}

}


//-------------------------------------
// ���[�t�B���O�X�V
//--------------------------------------
void CMorphing::Update()
{

}

//-------------------------------
// ���[�t�B���O�`��
//------------------------------
void CMorphing::Draw()
{
	CGraphics::GetDevice()->SetFVF(FVF_VERTEX);							// ���_�t�H�[�}�b�g�w��
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &m_world);	// ���[���h�}�g���N�X���Z�b�g

	//if (g_Wireframe) {
	//	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);				// ���C�g������
	//	g_pD3DDevice->SetTexture(0, NULL);									// �e�N�X�`������
	//	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	// ���C���[�t���[���`��
	//} else {
	//	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);					// ���C�g�L����
	//	g_pD3DDevice->SetTexture(0, g_pD3DTexture);							// �e�N�X�`���ݒ�
	//	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		// �\���b�h�`��
	//}

	CGraphics::GetDevice()->SetTexture(0, m_pD3DTexture);							// �e�N�X�`���ݒ�
	CGraphics::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);		// �\���b�h�`��

	CGraphics::GetDevice()->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,		// ���[�t�B���O���f����`��
				0, m_nVertexNum[0], m_nFaceNum[0], m_pwMorph_Index,
				D3DFMT_INDEX16, m_pMorph_Vertex, sizeof(MORPH_VERTEX));
}