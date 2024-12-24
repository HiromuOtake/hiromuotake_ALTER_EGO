//==============================================
//
// ALTER_EGO[number.cpp]
// Author: hiromu otake
//
//==============================================

#include "number.h"
#include "texture.h"

//======================================================
// �R���X�g���N�^
//======================================================
CNumber::CNumber(int nPriority) : CObject2D(nPriority)
{

}

//======================================================
// �f�X�g���N�^
//======================================================
CNumber::~CNumber()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CNumber::Init()
{
	int nId = 0;

	CObject2D::SetTexture(0.1f);

	nId = CManager::GetTexture()->Regist("data\\Texture\\number4.png");

	BindTexture(CManager::GetTexture()->GetAddress(nId));

	CObject2D::Init();

	return S_OK;
}

//======================================================
// �I������
//======================================================
void CNumber::Uninit()
{
	CObject2D::Uninit();
}

//======================================================
// �X�V����
//======================================================
void CNumber::Update()
{

	VERTEX_2D* pVtx;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = CObject2D::GetBuffer();

	CObject2D::Update();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * m_nTexPos), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * m_nTexPos), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * m_nTexPos), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * m_nTexPos), 1.0f);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Unlock();

}

//======================================================
// �`�揈��
//======================================================
void CNumber::Draw()
{
	CObject2D::Draw();
}

//======================================================
// �e�N�X�`�����W�̐ݒ�
//======================================================
void CNumber::SetTexturePos(int nTexPos)
{
	m_nTexPos = nTexPos;
}


//=====================================================
// �w�i�̐���
//=====================================================
CNumber* CNumber::Create(D3DXVECTOR3 pos, float fsizeX, float fsizeY)
{
	CNumber* pNumber = new CNumber;

	if (pNumber != nullptr)
	{
		pNumber->SetPos(pos);
		pNumber->SetWidthHeight(fsizeX, fsizeY);
		pNumber->Init();
		pNumber->SetUseDeath(true);
	}
	return  pNumber;
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CNumber::SetDeath()
{
	CObject::SetDeath();
}

