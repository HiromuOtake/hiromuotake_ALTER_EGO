//==============================================
//
// ALTER_EGO[tutorial.cpp]
// Author: hiromu otake
//
//==============================================

#include "tutorial.h"
#include "bg.h"

//======================================================
// �R���X�g���N�^
//======================================================
CTutorial::CTutorial() : m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pNumber(nullptr)
{

}

//======================================================
// �f�X�g���N�^
//======================================================
CTutorial::~CTutorial()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CTutorial::Init()
{
	CScene::Init();

	CBg::Create(CScene::MODE::MODE_TUTORIAL1);

	return S_OK;
}

//======================================================
// �I������
//======================================================
void CTutorial::Uninit()
{
	CScene::Uninit();
}

//======================================================
// �X�V����
//======================================================
void CTutorial::Update()
{
	CScene::Update();
}

//======================================================
// �`�揈��
//======================================================
void CTutorial::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	CRenderer* pRenderer = CManager::GetRenderere();

	//�f�o�C�X�̎擾
	pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}