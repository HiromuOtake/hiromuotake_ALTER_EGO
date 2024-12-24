//==============================================
//
// ALTER_EGO[title.cpp]
// Author: hiromu otake
//
//==============================================

#include "title.h"
#include "bg.h"
#include "block.h"

//======================================================
// �R���X�g���N�^
//======================================================
CTitle::CTitle() : m_pBg(nullptr)
{

}

//======================================================
// �f�X�g���N�^
//======================================================
CTitle::~CTitle()
{

}

//======================================================
// �����ݒ�
//======================================================
HRESULT CTitle::Init()
{
	// �w�i���쐬
	m_pBg = CBg::Create(CScene::MODE::MODE_TITLE);	
	assert(m_pBg && "�w�i�̍쐬�Ɏ��s���܂����I");

	CScene::Init();

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);

	return S_OK;
}

//======================================================
// �I������
//======================================================
void CTitle::Uninit()
{
	// �w�i�̉��
	if (m_pBg)
	{
		m_pBg->SetDeath();
		m_pBg = nullptr;
	}

	CSound* pSound = CManager::GetSound();

	pSound->StopSound(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);

	CScene::Uninit();
}

//======================================================
// �X�V����
//======================================================
void CTitle::Update()
{
	CScene::Update();
}

//======================================================
// �`�揈��
//======================================================
void CTitle::Draw()
{
	// �w�i��`��
	if (m_pBg)
	{
		m_pBg->Draw();
	}

	// ���̃I�u�W�F�N�g�̕`��
	CScene::Draw();
}