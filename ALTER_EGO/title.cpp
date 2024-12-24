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
// コンストラクタ
//======================================================
CTitle::CTitle() : m_pBg(nullptr)
{

}

//======================================================
// デストラクタ
//======================================================
CTitle::~CTitle()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CTitle::Init()
{
	// 背景を作成
	m_pBg = CBg::Create(CScene::MODE::MODE_TITLE);	
	assert(m_pBg && "背景の作成に失敗しました！");

	CScene::Init();

	CSound* pSound = CManager::GetSound();

	pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_BGM000);

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CTitle::Uninit()
{
	// 背景の解放
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
// 更新処理
//======================================================
void CTitle::Update()
{
	CScene::Update();
}

//======================================================
// 描画処理
//======================================================
void CTitle::Draw()
{
	// 背景を描画
	if (m_pBg)
	{
		m_pBg->Draw();
	}

	// 他のオブジェクトの描画
	CScene::Draw();
}