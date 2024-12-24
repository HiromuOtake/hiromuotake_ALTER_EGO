//======================================================
//
// ALTER_EGO [object2D.cpp]
// Auther : ��|�
//
//======================================================

#include "object2D.h"
#include "manager.h"

//======================================================
// �R���X�g���N�^
//======================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority), m_pVtxBuff(nullptr), m_pTexture(nullptr), m_fHeight(0.0f), m_fWidth(0.0f), m_fTexture(0.0f),
m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), m_posold(D3DXVECTOR3(0.0f, 0.0f, 0.0f)), m_colorFade(0.0f), m_fAnglePlayer(0.0f), m_fLengthPlayer(0.0f)
{

}

//======================================================
// �f�X�g���N�^
//======================================================
CObject2D::~CObject2D()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CObject2D::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//�f�o�C�X�ւ̃|�C���^

	m_colorFade = 1.0f;

	//�Ίp���̒������Z�o����
	m_fLengthPlayer = sqrtf(m_fWidth * m_fWidth + m_fHeight * m_fHeight) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	m_fAnglePlayer = atan2f(m_fWidth, m_fHeight);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx;				//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̎w��
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAnglePlayer)* m_fLengthPlayer;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAnglePlayer)* m_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_fTexture, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fTexture, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//======================================================
// �I������
//======================================================
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//======================================================
// �X�V����
//======================================================
void CObject2D::Update()
{
	VERTEX_2D* pVtx;				//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̎w��
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAnglePlayer)) * m_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAnglePlayer) * m_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_colorFade);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_colorFade);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_colorFade);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_colorFade);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_fTexture, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fTexture, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//======================================================
// �`�揈��
//======================================================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	CRenderer* pRenderer = CManager::GetRenderere();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	// Z �o�b�t�@�𖳌���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// Z �o�b�t�@���ēx�L����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

//======================================================
// �e�N�X�`������
//======================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexture = pTex;
}

//======================================================
// �ʒu�̐ݒ�
//======================================================
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//======================================================
// �T�C�Y�̐ݒ�
//======================================================
void CObject2D::SetWidthHeight(float fWidth, float fHeidht)
{
	m_fWidth = fWidth;
	m_fHeight = fHeidht;	
}

//======================================================
// �F�̐ݒ�
//======================================================
void CObject2D::SetColor(float fColor)
{
	m_colorFade = fColor;
}

//======================================================
// �F�̐ݒ�
//======================================================
void CObject2D::SetTexture(float fTexture)
{
	m_fTexture = fTexture;
}

//======================================================
// �ʒu�̎擾
//======================================================
D3DXVECTOR3& CObject2D::GetPos()
{
	return m_pos; 
}

//======================================================
// �ʒu�̎擾
//======================================================
D3DXVECTOR3* CObject2D::GetPosOld()
{
	return &m_posold; 
}

//======================================================
// �����̎擾
//======================================================
D3DXVECTOR3* CObject2D::GetRot()
{
	return &m_rot; 
}
