//==============================================
//
// ALTER_EGO[billboard.cpp]
// Author: hiromu otake
//
//==============================================

#include "billboard.h"
#include "manager.h"

//=====================================
// �R���X�g���N�^
//=====================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority), m_pos{ 0.0f,0.0f,0.0f }, m_min{ 0.0f,0.0f,0.0f }, m_max{ 0.0f,0.0f,0.0f }, m_size{ 0.0f,0.0f,0.0f }
, m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pMesh(nullptr), m_pBuffMat(nullptr), m_nNumVtx(0), m_sizeFVF(0)
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CBillboard::~CBillboard()
{

}

//=====================================
//�r���{�[�h�̏����ݒ�
//=====================================
HRESULT CBillboard::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//�f�o�C�X�ւ̃|�C���^

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx;          //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_BILLBOARD_SIZE, m_BILLBOARD_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_BILLBOARD_SIZE, m_BILLBOARD_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_BILLBOARD_SIZE, -m_BILLBOARD_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_BILLBOARD_SIZE, -m_BILLBOARD_SIZE, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_size.x = m_BILLBOARD_SIZE;
	m_size.y = m_BILLBOARD_SIZE;

	return S_OK;
}

//=====================================
//�v���C���[�̏I������
//=====================================
void CBillboard::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=====================================
//�v���C���[�̍X�V����
//=====================================
void CBillboard::Update()
{
	
}

//=====================================
//�|���S���̕`�揈��
//=====================================
void CBillboard::Draw()
{
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;				//�r���[�}�g���b�N�X�擾�p
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//�f�o�C�X�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);		//�t��������߂�
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//======================================================
// �e�N�X�`������
//======================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//======================================================
// �ʒu�̐ݒ�
//======================================================
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//======================================================
// �ʒu�̐ݒ�
//======================================================
void CBillboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//======================================================
// �ʒu�̎擾
//======================================================
D3DXVECTOR3& CBillboard::GetPos()
{
	return m_pos;
}

//======================================================
// �ߋ��̈ʒu�̎擾
//======================================================
D3DXVECTOR3& CBillboard::GetPosOld()
{
	return m_posold;
}

//======================================================
// �����̎擾
//======================================================
D3DXVECTOR3& CBillboard::GetRot()
{
	return m_rot;
}

//======================================================
// �傫���̎擾
//======================================================
D3DXVECTOR3& CBillboard::GetSize()
{
	return m_size;
}

//======================================================
// �ŏ��̎擾
//======================================================
D3DXVECTOR3& CBillboard::GetMin()
{
	return m_min;
}

//======================================================
// �ő�̎擾
//======================================================
D3DXVECTOR3& CBillboard::GetMax()
{
	return m_max;
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBillboard::SetDeath()
{
	CObject::SetDeath();
}