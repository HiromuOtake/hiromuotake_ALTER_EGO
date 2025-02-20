//==============================================
//
// ALTER_EGO[player.cpp]
// Author: hiromu otake
//
//==============================================

#include "player.h"
#include "camera.h"
#include "block.h"
#include "game.h"

bool CPlayer::m_bUse = true;

//==============================================
// コンストラクタ
//==============================================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority), m_max{ 0.0f,0.0f,0.0f }, m_min{ 0.0f,0.0f,0.0f }, m_move{ 0.0f,0.0f,0.0f }
, m_bIsLanding(false), m_bJumping(false), m_Keyboard(nullptr), m_JoyPad(nullptr), m_bIsRight(false), m_bCloneActive(false), m_pCloneCircle(nullptr), m_pClone(nullptr), m_pModelParts{}
, m_nModelIdx(0), m_nTextureIdx(0), m_nLife(0), m_nType(PLAYER_NONE), m_nDeathTimer(0), m_nJumpCnt(0)
{
	m_pCloneCircle = new CCloneCircle();
	m_pCloneCircle->Init();
}

//==============================================
// デストラクタ
//==============================================
CPlayer::~CPlayer()
{

}

//==============================================
// 初期設定
//==============================================
HRESULT CPlayer::Init()
{
	m_bIsRight = true;
	m_nType = PLAYER_NORMAL;

	m_Keyboard = CManager::GetKeyboard();
	m_JoyPad = CManager::GetJoyPad();
	
	m_nLife = m_PLAYER_LIFE;

	int nCnt = 0;

	CCharacter::Init();

	CCharacter::LoadMotion(&nCnt);

	// サイズ計算用の初期化
	m_min = { FLT_MAX, FLT_MAX, FLT_MAX };
	m_max = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

	for (int nCount = 0; nCount < m_NUM_MODEL_PARTS; nCount++)
	{
		D3DXVECTOR3& Partspos = CCharacter::GetModelParts(nCount)->GetPos();
		D3DXVECTOR3& pPos = CCharacter::GetPos();

		D3DXVECTOR3 pWoarldPos = Partspos + pPos;

		if (pWoarldPos.x < m_min.x)
		{
			m_min.x = pWoarldPos.x;
		}
		else if (pWoarldPos.x > m_max.x)
		{
			m_max.x = pWoarldPos.x;
		}

		if (pWoarldPos.y < m_min.y)
		{
			m_min.y = pWoarldPos.y;
		}
		else if (pWoarldPos.y > m_max.y)
		{
			m_max.y = pWoarldPos.y;
		}

		if (pWoarldPos.z < m_min.z)
		{
			m_min.z = pWoarldPos.z;
		}
		else if (pWoarldPos.z > m_max.z)
		{
			m_max.z = pWoarldPos.z;
		}
		m_size = m_max - m_min;
	}
	return S_OK;
}

//==============================================
// 終了処理
//==============================================
void CPlayer::Uninit()
{
	CCharacter::Uninit();
}

//==============================================
// 更新処理
//==============================================
void CPlayer::Update()
{
	CSound* pSound = CManager::GetSound();

	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		// Kキーでクローン選択を開始
		if (m_Keyboard->GetTrigger(DIK_K) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_X) == true)
		{
			m_bCloneActive = !m_bCloneActive;	// 表示切り替え
			if (m_bCloneActive)
			{
				pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_SPAWNSIRCLE);

				m_pCloneCircle->Activate();		// 描画を再有効化
				m_pCloneCircle->SetPlayerPos(GetPos());
			}
			else
			{
				pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DELETECIRCLE);

				m_pCloneCircle->SetDeath();		// リソースの解放
				CManager::SetPaused(false);		// ポーズ解除
			}
		}
	}

	// クローン選択中の操作
	if (m_bCloneActive)
	{
		HandleCloneSelection();				// クローン選択の処理
		m_pCloneCircle->Update();			// クローン位置更新
	}
	else
	{
		// 通常時のプレイヤー処理
		PlayerMovement();
	}
}

//==============================================
// クローン選択処理
//==============================================
void CPlayer::HandleCloneSelection() 
{
	CSound* pSound = CManager::GetSound();

	// 移動キーと十字キーで選択位置を変更
	if (m_Keyboard->GetTrigger(DIK_W) ||m_Keyboard->GetTrigger(DIK_UP) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_UP) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(0);  // 上
	}
	else if (m_Keyboard->GetTrigger(DIK_S) ||m_Keyboard->GetTrigger(DIK_DOWN) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_DOWN) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(1);  // 下
	}
	else if (m_Keyboard->GetTrigger(DIK_D) ||m_Keyboard->GetTrigger(DIK_RIGHT) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_RIGHT) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(2);  // 右
	}
	else if (m_Keyboard->GetTrigger(DIK_A) ||m_Keyboard->GetTrigger(DIK_LEFT) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_LEFT) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(3);  // 左
	}

	// Enterキーでクローン生成
	if (m_Keyboard->GetTrigger(DIK_RETURN) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_B) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DELETECIRCLE);

		GenerateClone();
		m_bCloneActive = false;  // クローン選択を終了
	}
}

//==============================================
// クローン生成処理
//==============================================
void CPlayer::GenerateClone() 
{
	D3DXVECTOR3 clonePos = m_pCloneCircle->GetSelectedPosition();
	CClone::Create(clonePos);  // クローンを生成
}

//==============================================
// 通常更新処理
//==============================================
void CPlayer::PlayerMovement()
{
	CSound* pSound = CManager::GetSound();

	D3DXVECTOR3* pCamera = CCamera::GetRot();

	D3DXVECTOR3& pPos = CCharacter::GetPos();
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();
	D3DXVECTOR3& pRot = CCharacter::GetRot();

	pPosOld = pPos;

	if (CManager::GetMode() == CScene::MODE_TITLE)
	{
		TitlePlayerMovement();
	}
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (m_nType == PLAYER_NORMAL)
		{
			if (m_Keyboard->GetPress(DIK_D) == true || m_JoyPad->GetJoyPadPress(CInput::JOYKEY_RIGHT) == true)
			{
				SetMotion(MOTION_MOVE);

				m_move.x += sinf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_PLAYER_SPEED;
				m_move.z += cosf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_PLAYER_SPEED;

				pRot.y = pCamera->y + D3DX_PI * -0.5f;
			}
			else if (m_Keyboard->GetPress(DIK_A) == true || m_JoyPad->GetJoyPadPress(CInput::JOYKEY_LEFT) == true)
			{
				SetMotion(MOTION_MOVE);

				m_move.x += sinf(pCamera->y + D3DX_PI * -m_LEFTRIGHT) * m_PLAYER_SPEED;
				m_move.z += cosf(pCamera->y + D3DX_PI * -m_LEFTRIGHT) * m_PLAYER_SPEED;

				pRot.y = pCamera->y + D3DX_PI * +0.5f;
			}
			else
			{
				SetMotion(MOTION_NEUTRAL);
			}

			if (m_nJumpCnt <= 0)
			{
				if (m_Keyboard->GetTrigger(DIK_SPACE) == true || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_A) == true)
				{
					m_move.y = +m_PLAYER_JUMP;
					m_nJumpCnt++;

					pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_JUMP);
				}
			}
		}
	}

	m_move.y -= 1.0f;

	//位置を更新
	pPos.z += m_move.z;

	//移動量を更新(減衰させる)
	m_move.x += (0.0f - m_move.x) * 0.1f;
	//m_move.y += (0.0f - m_move.y) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	bool bIsLanding = false;

	pPos.x += m_move.x;

	for (int nCntPrio = 0; nCntPrio < 15; nCntPrio++)
	{// プライオリティ分回す

		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			if (IsBadReadPtr(pObj, sizeof(CObject)))
			{
				break;
			}

			// 左右の当たり判定
			CollisionLEFTRIGHT(pObj);
			pObj = pObj->GetNext();
		}
	}

	pPos.y += m_move.y;

	for (int nCntPrio = 0; nCntPrio < 15; nCntPrio++)
	{// プライオリティ分回す

		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			if (IsBadReadPtr(pObj, sizeof(CObject)))
			{
				break;
			}

			// 上下の当たり判定
			CollisionUPDOWN(bIsLanding, pObj);
			pObj = pObj->GetNext();
		}
	}

	m_bIsLanding = bIsLanding;

	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		if (m_bUse == false)
		{
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_GOAL);

			CManager::SetMode(CScene::MODE::MODE_RESULT);
			m_bUse = true;
		}
	}

	CCharacter::PlayerMotion();

	CCharacter::Update();
}

//==============================================
// タイトルでのプレイヤー処理
//==============================================
void CPlayer::TitlePlayerMovement()
{
	D3DXVECTOR3* pCamera = CCamera::GetRot();

	D3DXVECTOR3& pPos = CCharacter::GetPos();
	D3DXVECTOR3& pRot = CCharacter::GetRot();

	if (m_nType == PLAYER_NORMAL)
	{
		SetMotion(MOTION_MOVE);

		m_move.x += sinf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_PLAYER_SPEED;
		m_move.z += cosf(pCamera->y + D3DX_PI * m_LEFTRIGHT) * m_PLAYER_SPEED;

		pRot.y = pCamera->y + D3DX_PI * -0.5f;

		m_nTitleJump++;

		//if (m_nRandomAction == 1) // ランダム値が1の場合、ジャンプも実行
		{
			if (m_nJumpCnt <= 0)
			{
				if (m_nTitleJump > 30)
				{
					m_move.y = +m_PLAYER_JUMP;
					m_nJumpCnt++;

					m_nTitleJump = 0;
				}
			}
		}
		if (pPos.x > 2500)
		{
			//// ランダムシード設定（必要に応じて）
			//srand(static_cast<unsigned int>(time(nullptr)));

			//// ランダムアクションを一度だけ決定
			//m_nRandomAction = rand() % 2; // 0 または 1 をランダムに設定

			pPos.x = -100;
			pPos.y = -600;
		}
	}
}

//==============================================
// 描画処理
//==============================================
void CPlayer::Draw()
{
	if (CManager::IsPaused())
	{
		// クローン選択中に描画
		if (m_bCloneActive) 
		{
			m_pCloneCircle->Draw();
		}
	}

	if (m_nType == PLAYER_DEATH)
	{

	}
	else
	{
		CCharacter::Draw();
	}
}

//=====================================================
// 上下の当たり判定
//=====================================================
bool CPlayer::CollisionUPDOWN(bool& bIsLanding, CObject* pObj)
{
	// モデルパーツのワールド座標を取得
	//D3DXVECTOR3 pPos = { CCharacter::GetModelParts(1)->GetWoarldMatrix()._41 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._42 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._43 };

	D3DXVECTOR3& pPos = CCharacter::GetPos();
	// プレイヤーの過去の座標を取得
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();
	// モデルパーツのサイズを取得
	D3DXVECTOR3 pSize = CCharacter::GetModelParts(1)->GetSize();

	//D3DXVECTOR3 PartsPosOld = pPosOld + pPos;

	D3DXVECTOR3 PlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	PlayerSize.x = (float(floor(m_size.x)));
	PlayerSize.y = (float(floor(m_size.y)));
	PlayerSize.z = (float(floor(m_size.z)));

	if (pObj != nullptr)
	{// pObjがnullptrじゃないなら

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BLOCK)
		{// typeがBLOCKなら

			CBlock* pBlock = dynamic_cast<CBlock*>(pObj);
			if (pBlock != nullptr)
			{
				CBlock::BLOCK pBlockType = pBlock->GetBlockType();

				D3DXVECTOR3 pBlockPos = pBlock->GetPos();
				D3DXVECTOR3 pBlockMin = pBlock->GetMin();
				D3DXVECTOR3 pBlockMax = pBlock->GetMax();
				D3DXVECTOR3 pBlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				// 少数の位を省く処理
				D3DXVECTOR3 BlockSize = pBlock->GetSize();
				pBlockSize.x = (float)(floor(BlockSize.x));
				pBlockSize.y = (float)(floor(BlockSize.y));
				pBlockSize.z = (float)(floor(BlockSize.z));

				if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
				{
					// X方向およびZ方向の重なりを一度だけチェック
					bool isXOverlap = (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE) &&
						(pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE);

					bool isZOverlap = (pPos.z + PlayerSize.z * m_HALF_SIZE > pBlockPos.z - pBlockSize.z * m_HALF_SIZE) &&
						(pPos.z - PlayerSize.z * m_HALF_SIZE < pBlockPos.z + pBlockSize.z * m_HALF_SIZE);

					if (isXOverlap && isZOverlap)
					{
						// 上側の当たり判定
						if (pPos.y < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
							pPosOld.y >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE)
						{
							// プレイヤーをブロックの上に押し戻し
							pPos.y = pBlockPos.y + pBlockSize.y * m_HALF_SIZE;
							m_move.y = 0.0f;
							bIsLanding = true; // 着地状態を設定
							m_nJumpCnt = 0;
						}
						// 下側の当たり判定
						else if (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y &&
							pPosOld.y + PlayerSize.y <= pBlockPos.y - pBlockSize.y)
						{
							// プレイヤーをブロックの下に押し戻し
							pPos.y = pBlockPos.y - pBlockSize.y - PlayerSize.y;
							m_move.y = 0.0f;
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_DOOR)
				{
					CBlockDoor* pDoor = dynamic_cast<CBlockDoor*>(pObj);
					if (pDoor && pDoor->IsOpen())
					{
						// 扉が開いている場合は当たり判定をスキップ
						return false;
					}

					// X方向およびZ方向の重なりを一度だけチェック
					bool isXOverlap = (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE) &&
						(pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE);

					if (isXOverlap)
					{
						// 上側の当たり判定
						if (pPos.y < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
							pPosOld.y >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE)
						{
							// プレイヤーをブロックの上に押し戻し
							pPos.y = pBlockPos.y + pBlockSize.y * m_HALF_SIZE;
							m_move.y = 0.0f;
							bIsLanding = true; // 着地状態を設定
							m_nJumpCnt = 0;
						}
						// 下側の当たり判定
						else if (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y &&
							pPosOld.y + PlayerSize.y <= pBlockPos.y - pBlockSize.y)
						{
							// プレイヤーをブロックの下に押し戻し
							pPos.y = pBlockPos.y - pBlockSize.y - PlayerSize.y;
							m_move.y = 0.0f;
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_BUTTON)
				{
					// X方向およびZ方向の重なりを一度だけチェック
					bool isXOverlap = (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE) &&
						(pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE);

					if (isXOverlap)
					{
						// 上側の当たり判定
						if (pPos.y < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
							pPosOld.y >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE)
						{
							// プレイヤーをブロックの上に押し戻し
							pPos.y = pBlockPos.y + pBlockSize.y * m_HALF_SIZE;
							m_move.y = 0.0f;
							bIsLanding = true; // 着地状態を設定
							m_nJumpCnt = 0;
						}
						// 下側の当たり判定
						else if (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y &&
							pPosOld.y + PlayerSize.y <= pBlockPos.y - pBlockSize.y)
						{
							// プレイヤーをブロックの下に押し戻し
							pPos.y = pBlockPos.y - pBlockSize.y - PlayerSize.y;
							m_move.y = 0.0f;
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_GOAL)
				{
					// X方向およびZ方向の重なりを一度だけチェック
					bool isXOverlap = (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE) &&
						(pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE);

					if (isXOverlap)
					{
						// 上側の当たり判定
						if (pPos.y < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
							pPosOld.y >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE)
						{
							m_bUse = true;
						}
						// 下側の当たり判定
						else if (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y &&
							pPosOld.y + PlayerSize.y <= pBlockPos.y - pBlockSize.y)
						{
							m_bUse = true;
						}
					}
				}
			}
		}
		if (type == CObject::TYPE::TYPE_ITEM)
		{// typeがBLOCKなら

			CItem* pItem = dynamic_cast<CItem*>(pObj);
			if (pItem != nullptr)
			{
				CItem::ITEM pItemType = pItem->GetItemType();

				D3DXVECTOR3 pItemPos = pItem->GetPos();
				D3DXVECTOR3 pItemMin = pItem->GetMin();
				D3DXVECTOR3 pItemMax = pItem->GetMax();
				D3DXVECTOR3 pItemSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				// 少数の位を省く処理
				D3DXVECTOR3 ItemSize = pItem->GetSize();
				pItemSize.x = (float)(floor(ItemSize.x));
				pItemSize.y = (float)(floor(ItemSize.y));
				pItemSize.z = (float)(floor(ItemSize.z));

				if (pItemType == CItem::ITEM::ITEM_STAR)
				{
					// X方向およびZ方向の重なりを一度だけチェック
					bool isXOverlap = (pPos.x + PlayerSize.x * m_HALF_SIZE > pItemPos.x - pItemSize.x * m_HALF_SIZE) &&
						(pPos.x - PlayerSize.x * m_HALF_SIZE < pItemPos.x + pItemSize.x * m_HALF_SIZE);

					bool isZOverlap = (pPos.z + PlayerSize.z * m_HALF_SIZE > pItemPos.z - pItemSize.z * m_HALF_SIZE) &&
						(pPos.z - PlayerSize.z * m_HALF_SIZE < pItemPos.z + pItemSize.z * m_HALF_SIZE);

					if (isXOverlap && isZOverlap)
					{
						// 上側の当たり判定
						if (pPos.y < pItemPos.y + pItemSize.y * m_HALF_SIZE &&
							pPosOld.y >= pItemPos.y + pItemSize.y * m_HALF_SIZE)
						{
							// プレイヤーをブロックの上に押し戻し
							pPos.y = pItemPos.y + pItemSize.y * m_HALF_SIZE;
							m_move.y = 0.0f;
							bIsLanding = true; // 着地状態を設定
							m_nJumpCnt = 0;
						}
						// 下側の当たり判定
						else if (pPos.y + PlayerSize.y > pItemPos.y - pItemSize.y &&
							pPosOld.y + PlayerSize.y <= pItemPos.y - pItemSize.y)
						{
							// プレイヤーをブロックの下に押し戻し
							pPos.y = pItemPos.y - pItemSize.y - PlayerSize.y;
							m_move.y = 0.0f;
						}
					}
				}
			}
		}
	}
	return bIsLanding;
}

//=====================================================
// 左右の当たり判定
//=====================================================
void CPlayer::CollisionLEFTRIGHT(CObject* pObj)
{
	//D3DXVECTOR3 pPos = { CCharacter::GetModelParts(1)->GetWoarldMatrix()._41 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._42 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._43 };
	D3DXVECTOR3& pPos = CCharacter::GetPos();
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();

	//D3DXVECTOR3 pSize = CCharacter::GetModelParts(1)->GetSize();

	D3DXVECTOR3 PlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	PlayerSize.x = (float(floor(m_size.x)));
	PlayerSize.y = (float(floor(m_size.y)));
	PlayerSize.z = (float(floor(m_size.z)));

	if (pObj != nullptr)
	{// pObjがnullptrじゃないなら

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BLOCK)
		{// typeがBLO CKなら

			CBlock* pBlock = dynamic_cast<CBlock*>(pObj);
			if (pBlock != nullptr)
			{
				CBlock::BLOCK pBlockType = pBlock->GetBlockType();

				D3DXVECTOR3 pBlockPos = pBlock->GetPos();
				D3DXVECTOR3 pBlockMin = pBlock->GetMin();
				D3DXVECTOR3 pBlockMax = pBlock->GetMax();
				D3DXVECTOR3 pBlockSize = pBlock->GetSize();

				// 少数の位を省く処理
				D3DXVECTOR3 BlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				BlockSize.x = (float)(floor(pBlockSize.x));
				BlockSize.y = (float)(floor(pBlockSize.y));
				BlockSize.z = (float)(floor(pBlockSize.z));

				if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
				{
					// Y方向およびZ方向の重なりを一度だけチェック
					bool isYOverlap = (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y * m_HALF_SIZE) &&
						(pPos.y + PlayerSize.y <= pBlockPos.y + pBlockSize.y * m_HALF_SIZE);

					if (isYOverlap)
					{
						//右側の当たり判定
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + PlayerSize.x * m_HALF_SIZE;
						}
						//左側の当たり判定
						else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x - pBlockSize.x * m_HALF_SIZE - PlayerSize.x * m_HALF_SIZE;
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_DOOR)
				{
					CBlockDoor* pDoor = dynamic_cast<CBlockDoor*>(pObj);
					if (pDoor && pDoor->IsOpen())
					{
						// 扉が開いている場合は当たり判定をスキップ
						return;
					}

					// Y方向およびZ方向の重なりを一度だけチェック
					bool isYOverlap = (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y * m_HALF_SIZE) &&
						(pPos.y + PlayerSize.y <= pBlockPos.y + pBlockSize.y * m_HALF_SIZE);

					if (isYOverlap)
					{
						//右側の当たり判定
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + (PlayerSize.x * m_HALF_SIZE);
							m_move.x = 0.0f;
						}
						//左側の当たり判定
						else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x - pBlockSize.x * m_HALF_SIZE - (PlayerSize.x * m_HALF_SIZE);
							m_move.x = 0.0f;
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_BUTTON)
				{
					// Y方向およびZ方向の重なりを一度だけチェック
					bool isYOverlap = (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y * m_HALF_SIZE) &&
						(pPos.y + PlayerSize.y <= pBlockPos.y + pBlockSize.y * m_HALF_SIZE);

					if (isYOverlap)
					{
						//右側の当たり判定
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + (PlayerSize.x * m_HALF_SIZE);
							m_move.x = 0.0f;
						}
						//左側の当たり判定
						else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x - pBlockSize.x * m_HALF_SIZE - (PlayerSize.x * m_HALF_SIZE);
							m_move.x = 0.0f;
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_GOAL)
				{
					// Y方向およびZ方向の重なりを一度だけチェック
					bool isYOverlap = (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y * m_HALF_SIZE - m_GOAL_CORRECTION) &&
						(pPos.y + PlayerSize.y <= pBlockPos.y + pBlockSize.y * m_HALF_SIZE + m_GOAL_CORRECTION);

					if (isYOverlap)
					{
						//右側の当たり判定
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
						{
							m_bUse = false;
						}
						//左側の当たり判定
						else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE)
						{
							m_bUse = false;
						}
					}
				}
			}
		}
		if (type == CObject::TYPE::TYPE_ITEM)
		{// typeがBLO CKなら

			CItem* pItem = dynamic_cast<CItem*>(pObj);
			if (pItem != nullptr)
			{
				CItem::ITEM pItemType = pItem->GetItemType();

				D3DXVECTOR3 pItemPos = pItem->GetPos();
				D3DXVECTOR3 pItemMin = pItem->GetMin();
				D3DXVECTOR3 pItemMax = pItem->GetMax();
				D3DXVECTOR3 pItemSize = pItem->GetSize();

				// 少数の位を省く処理
				D3DXVECTOR3 ItemSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				ItemSize.x = (float)(floor(pItemSize.x));
				ItemSize.y = (float)(floor(pItemSize.y));
				ItemSize.z = (float)(floor(pItemSize.z));

				if (pItemType == CBlock::BLOCK::BLOCK_NORMAL)
				{
					// Y方向およびZ方向の重なりを一度だけチェック
					bool isYOverlap = (pPos.y + PlayerSize.y > pItemPos.y - pItemSize.y * m_HALF_SIZE) &&
						(pPos.y + PlayerSize.y <= pItemPos.y + pItemSize.y * m_HALF_SIZE);

					if (isYOverlap)
					{
						//右側の当たり判定
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pItemPos.x + pItemSize.x * m_HALF_SIZE &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pItemPos.x + pItemSize.x * m_HALF_SIZE)
						{
							pPos.x = pItemPos.x + pItemSize.x * m_HALF_SIZE + PlayerSize.x * m_HALF_SIZE;
						}
						//左側の当たり判定
						else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pItemPos.x - pItemSize.x * m_HALF_SIZE &&
							pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pItemPos.x - pItemSize.x * m_HALF_SIZE)
						{
							pPos.x = pItemPos.x - pItemSize.x * m_HALF_SIZE - PlayerSize.x * m_HALF_SIZE;
						}
					}
				}
			}
		}
	}
}

//=====================================================
// ゴール情報の取得
//=====================================================
bool& CPlayer::GetGoal()
{
	return m_bUse;
}

//=====================================================
// モデルの生成
//=====================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer* pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		pPlayer->SetType(TYPE_PLAYER);
		pPlayer->Init();
		pPlayer->SetPos(pos);
	}
	return  pPlayer;
}

//=========================================
// 死亡フラグ設定処理
//=========================================
void CPlayer::SetDeath()
{
	CObject::SetDeath();
}
