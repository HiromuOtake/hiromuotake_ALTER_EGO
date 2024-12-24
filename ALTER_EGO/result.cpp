//==============================================
//
// ALTER_EGO[result.cpp]
// Author: hiromu otake
//
//==============================================

#include "result.h"
#include "bg.h"

//======================================================
// �R���X�g���N�^
//======================================================
CResult::CResult() : m_pTexture(nullptr), m_pVtxBuff(nullptr), m_pNumber(nullptr)
{

}

//======================================================
// �f�X�g���N�^
//======================================================
CResult::~CResult()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CResult::Init()
{
	CScene::Init();

	CBg::Create(CScene::MODE::MODE_RESULT);

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);

	return S_OK;
}

//======================================================
// �I������
//======================================================
void CResult::Uninit()
{
	CSound* pSound = CManager::GetSound();

	pSound->StopAllSound();

	CScene::Uninit();
}

//======================================================
// �X�V����
//======================================================
void CResult::Update()
{
	CScene::Update();
}

//======================================================
// �`�揈��
//======================================================
void CResult::Draw()
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