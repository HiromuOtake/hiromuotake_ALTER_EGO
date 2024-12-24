//==============================================
//
// ALTER_EGO[bg.cpp]
// Author: hiromu otake
//
//==============================================

#include "bg.h"
#include "texture.h"

//======================================================
// コンストラクタ
//======================================================
CBg::CBg(int nPriority) : CObject2D(nPriority), m_pVtxBuff(nullptr), m_pTexture(nullptr), m_nTexIdx(0), m_texScrollSpeed01(0.0f), m_texScrollSpeed02(SCREEN_WIDTH)
{

}

//======================================================
// デストラクタ
//======================================================
CBg::~CBg()
{

}

//======================================================
// 初期設定
//======================================================
HRESULT CBg::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();;		//デバイスへのポインタ

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// サイズをスクリーン全体に設定
	CObject2D::SetWidthHeight((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	// テクスチャの初期設定
	CObject2D::SetTexture(1.0f);
	// 中央に配置
	CObject2D::SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));

	CObject2D::Init();

	return S_OK;
}

//======================================================
// 終了処理
//======================================================
void CBg::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	CObject2D::Uninit();
}

//======================================================
// 更新処理
//======================================================
void CBg::Update()
{
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		// 背景1を左に移動
		m_texScrollSpeed01 -= 2.0f;
		if (m_texScrollSpeed01 <= -SCREEN_WIDTH) // 背景1が画面外に出たらリセット
		{
			m_texScrollSpeed01 = SCREEN_WIDTH;
		}

		// 背景2を左に移動
		m_texScrollSpeed02 -= 1.0f;
		if (m_texScrollSpeed02 <= -SCREEN_WIDTH) // 背景2が画面外に出たらリセット
		{
			m_texScrollSpeed02 = SCREEN_WIDTH;
		}

		// 背景1と背景2の位置を設定
		SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f + m_texScrollSpeed01, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	CObject2D::Update();
}

//======================================================
// 描画処理
//======================================================
void CBg::Draw()
{
	CObject2D::Draw();
}

//=====================================================
// 背景の生成
//=====================================================
CBg* CBg::Create(CScene::MODE mode)
{
	CBg* pBg = new CBg;
	
	int nId = 0;

	if (pBg != nullptr)
	{
		switch (mode)
		{
		case CScene::MODE::MODE_TITLE:
			nId = CManager::GetTexture()->Regist("data\\Texture\\title.png");
			break;

		case CScene::MODE::MODE_GAME:
			nId = CManager::GetTexture()->Regist("data\\Texture\\game.png");
			break;

		case CScene::MODE::MODE_RESULT:
			nId = CManager::GetTexture()->Regist("data\\Texture\\result.png");
			break;

		default:
			break;
		}

		if (nId == -1)
		{
			OutputDebugStringA("テクスチャのロードに失敗しました。\n");
			delete pBg;
			return nullptr;
		}
		else
		{
			char debugMessage[256];
			sprintf(debugMessage, "テクスチャロード成功: ID = %d\n", nId);
			OutputDebugStringA(debugMessage);
		}

		pBg->SetType(TYPE_BG);
		pBg->BindTexture(CManager::GetTexture()->GetAddress(nId));
		pBg->Init();
		pBg->SetUseDeath(true);
	}
	return  pBg;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CBg::SetDeath()
{
	CObject::SetDeath();
}