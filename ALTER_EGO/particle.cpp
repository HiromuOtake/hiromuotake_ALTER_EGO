//==============================================
//
// ALTER_EGO[particle.cpp]
// Author: hiromu otake
//
//==============================================

#include "particle.h"

// �ÓI�����o������
LPDIRECT3DTEXTURE9 CParticle::m_pTextureTemp = nullptr;

//==============================================
// �R���X�g���N�^
//==============================================
CParticle::CParticle() : m_bUse(false), m_nLife(m_MAXLIFE), m_move{ 0.0f,0.0f,0.0f }, m_size(1.0f), m_speed(1.0f), m_color{ 1.0f, 1.0f, 1.0f, 1.0f }, m_pTexture(nullptr), m_pVtxBuff(nullptr)
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CParticle::~CParticle()
{

}

//==============================================
// �����ݒ�
//==============================================
HRESULT CParticle::Init()
{
	CBillboard::Init();

	return S_OK;
}

//==============================================
// �I������
//==============================================
void CParticle::Uninit()
{
	CBillboard::Uninit();

	CObject::SetUseDeath(true);
}

//==============================================
// �X�V����
//==============================================
void CParticle::Update()
{
	D3DXVECTOR3& pPos = CBillboard::GetPos();

	//�ʒu���X�V
	pPos += m_move;

	if (m_nLife > 0)
	{
		m_nLife--;
	}
	if (m_nLife <= 0 || m_bUse == true)
	{
		Uninit();
		CObject::SetDeath();
		return;
	}

	CBillboard::Update();
}

//==============================================
// �`�揈��
//==============================================
void CParticle::Draw()
{
	if (m_pTextureTemp == nullptr)
	{
		return;  // �e�N�X�`�����ǂݍ��܂�Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
	}

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//�f�o�C�X�ւ̃|�C���^

	// Z�o�b�t�@���ꎞ�I�ɖ�����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �F�̐ݒ�
	pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_COLORVALUE(m_color.r, m_color.g, m_color.b, m_color.a));

	CBillboard::Draw();

	//���u�����f�B���O�����Ƃɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z�o�b�t�@�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

//=====================================================
// �p�[�e�B�N���̐����֐�
//=====================================================
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size, float speed, D3DXCOLOR color)
{
	CParticle* pParticle = new CParticle;

	if (pParticle != nullptr)
	{
		pParticle->Init();
		pParticle->SetPos(pos);
		pParticle->m_move = move * speed;
		pParticle->BindTexture(m_pTextureTemp);
		pParticle->SetSize(size);
		pParticle->SetColor(color);
		pParticle->SetUseDeath(true);
	}

	return pParticle;
}
//======================================================
// �e�N�X�`���̐ݒ�
//======================================================
HRESULT CParticle::Load()
{
	if (m_pTextureTemp == nullptr)
	{
		LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

		CRenderer* pRenderer = CManager::GetRenderere();

		//�f�o�C�X�̎擾
		pDevice = pRenderer->GetDevice();

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\Texture\\effect000.jpg",
			&m_pTextureTemp);
	}
	return S_OK;
}

//======================================================
// �e�N�X�`���̔j��
//======================================================
void CParticle::Unload()
{
	//�e�N�X�`����j��
	if (m_pTextureTemp != NULL)
	{
		m_pTextureTemp->Release();
		m_pTextureTemp = NULL;
	}
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CParticle::SetDeath()
{
	CObject::SetDeath();
}
