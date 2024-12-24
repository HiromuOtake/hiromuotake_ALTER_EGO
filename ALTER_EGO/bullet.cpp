////==============================================
////
//// ALTER_EGO[bullet.cpp]
//// Author: hiromu otake
////
////==============================================
//
//#include "bullet.h"
//
//// �ÓI�����o������
//LPDIRECT3DTEXTURE9 CBullet::m_pTextureTemp = nullptr;
//
////==============================================
//// �R���X�g���N�^
////==============================================
//CBullet::CBullet() : m_bUse(false), m_nLife(m_MAXLIFE), m_move{ 0.0f,0.0f,0.0f }, m_pTexture(nullptr), m_pVtxBuff(nullptr)
//{
//
//}
//
////==============================================
//// �f�X�g���N�^
////==============================================
//CBullet::~CBullet()
//{
//
//}
//
////==============================================
//// �����ݒ�
////==============================================
//HRESULT CBullet::Init()
//{
//	CBillboard::Init();
//
//	CBullet::Load();
//
//	return S_OK;
//}
//
////==============================================
//// �I������
////==============================================
//void CBullet::Uninit()
//{
//	CBillboard::Uninit();
//
//	CObject::SetUseDeath(true);
//}
//
////==============================================
//// �X�V����
////==============================================
//void CBullet::Update()
//{
//	D3DXVECTOR3& pPos = CBillboard::GetPos();
//
//	//�ʒu���X�V
//	pPos += m_move;
//
//	if (m_nLife > 0)
//	{
//		m_nLife--;
//	}
//	if (m_nLife <= 0 || m_bUse == true)
//	{
//		Uninit();
//		CObject::SetDeath();
//		return;
//	}
//
//	CBillboard::Update();
//}
//
////==============================================
//// �`�揈��
////==============================================
//void CBullet::Draw()
//{
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//�f�o�C�X�ւ̃|�C���^
//
//	//�A���t�@�e�X�g��L��
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
//	pDevice->SetRenderState(D3DRS_ALPHAREF, 5);
//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
//
//	CBillboard::Draw();
//
//	//�A���t�@�e�X�g�𖳌��ɖ߂�
//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
//
//	////Z�̔�r���@�ύX
//	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
//	////Z�̃o�b�t�@�ɏ�������
//	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
//}
//
////=====================================================
//// �e�̐ݒ菈��(�g���Ă邩���Ȃ���)
////=====================================================
//void CBullet::SetUse(bool bUse)
//{
//	m_bUse = bUse;
//}
//
////=====================================================
//// �t�B�[���h�̐���
////=====================================================
//CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
//{
//	CBullet* pBullet = new CBullet;
//
//	if (pBullet != nullptr)
//	{
//		pBullet->SetType(TYPE_BULLET);
//		pBullet->Init();
//		pBullet->SetPos(pos);
//		pBullet->BindTexture(m_pTextureTemp);
//		pBullet->m_move = move;
//		pBullet->SetUseDeath(true);
//	}
//	return  pBullet;
//}
//
////======================================================
//// �e�N�X�`���̐ݒ�
////======================================================
//HRESULT CBullet::Load()
//{
//	if (m_pTextureTemp == nullptr)
//	{
//		LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
//
//		CRenderer* pRenderer = CManager::GetRenderere();
//
//		//�f�o�C�X�̎擾
//		pDevice = pRenderer->GetDevice();
//
//		//�e�N�X�`���̓ǂݍ���
//		D3DXCreateTextureFromFile(pDevice,
//			"data\\Texture\\bullet000.png",
//			&m_pTextureTemp);
//	}
//	return S_OK;
//}
//
////======================================================
//// �e�N�X�`���̔j��
////======================================================
//void CBullet::Unload()
//{
//	//�e�N�X�`����j��
//	if (m_pTextureTemp != NULL)
//	{
//		m_pTextureTemp->Release();
//		m_pTextureTemp = NULL;
//	}
//}
//
////======================================================
//// �ړ��ʂ̎擾
////======================================================
//D3DXVECTOR3* CBullet::GetMove()
//{
//	return &m_move;
//}
//
////=========================================
//// ���S�t���O�ݒ菈��
////=========================================
//void CBullet::SetDeath()
//{
//	CObject::SetDeath();
//}
