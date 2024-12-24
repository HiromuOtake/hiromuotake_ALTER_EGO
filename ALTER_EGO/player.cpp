//==============================================
//
// ALTER_EGO[player.cpp]
// Author: hiromu otake
//
//==============================================

#include "player.h"
#include "manager.h"
#include "camera.h"
#include "block.h"
#include "field.h"
#include "item.h"
#include "bullet.h"
#include "game.h"
#include "Tutorial.h"
#include "clonecircle.h"

bool CPlayer::m_bUse = true;

//==============================================
// �R���X�g���N�^
//==============================================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority), m_max{ 0.0f,0.0f,0.0f }, m_min{ 0.0f,0.0f,0.0f }, m_move{ 0.0f,0.0f,0.0f }
, m_bIsLanding(false), m_bJumping(false), m_Keyboard(nullptr), m_JoyPad(nullptr), m_bIsRight(false), m_bCloneActive(false), m_pCloneCircle(nullptr), m_pClone(nullptr), m_pModelParts{}
, m_nModelIdx(0), m_nTextureIdx(0), m_nLife(0), m_nType(PLAYER_NONE), m_nDeathTimer(0), m_JumpCnt(0)
{
	m_pCloneCircle = new CCloneCircle();
	m_pCloneCircle->Init();
}

//==============================================
// �f�X�g���N�^
//==============================================
CPlayer::~CPlayer()
{

}

//==============================================
// �����ݒ�
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

	// �T�C�Y�v�Z�p�̏�����
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
// �I������
//==============================================
void CPlayer::Uninit()
{
	CCharacter::Uninit();
}

//==============================================
// �X�V����
//==============================================
void CPlayer::Update()
{
	CSound* pSound = CManager::GetSound();

	// K�L�[�ŃN���[���I�����J�n
	if (m_Keyboard->GetTrigger(DIK_K) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_X) == true)
	{
		m_bCloneActive = !m_bCloneActive;	// �\���؂�ւ�
		if (m_bCloneActive)
		{
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_SPAWNSIRCLE);

			m_pCloneCircle->Activate();		// �`����ėL����
			m_pCloneCircle->SetPlayerPos(GetPos());
		}
		else
		{
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DELETECIRCLE);

			// �N���[���I�����I�������ꍇ
			m_pCloneCircle->SetDeath();		// ���\�[�X�̉��
			CManager::SetPaused(false); // �|�[�Y����
		}
	}

	// �N���[���I�𒆂̑���
	if (m_bCloneActive)
	{
		HandleCloneSelection();				// �N���[���I���̏���
		m_pCloneCircle->Update();			// �N���[���ʒu�X�V
	}
	else
	{
		// �ʏ펞�̃v���C���[����
		PlayerMovement();
	}
}

//==============================================
// �N���[���I������
//==============================================
void CPlayer::HandleCloneSelection() 
{
	CSound* pSound = CManager::GetSound();

	// WASD�L�[�Ə\���őI���ʒu��ύX
	if (m_Keyboard->GetTrigger(DIK_W) ||m_Keyboard->GetTrigger(DIK_UP) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_UP) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(0);  // ��
	}
	else if (m_Keyboard->GetTrigger(DIK_S) ||m_Keyboard->GetTrigger(DIK_DOWN) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_DOWN) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(1);  // ��
	}
	else if (m_Keyboard->GetTrigger(DIK_D) ||m_Keyboard->GetTrigger(DIK_RIGHT) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_RIGHT) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(2);  // �E
	}
	else if (m_Keyboard->GetTrigger(DIK_A) ||m_Keyboard->GetTrigger(DIK_LEFT) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_LEFT) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_CHOOSECLONE);

		m_pCloneCircle->SetSelectedIndex(3);  // ��
	}

	// Enter�L�[�ŃN���[������
	if (m_Keyboard->GetTrigger(DIK_RETURN) || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_B) == true)
	{
		pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_DELETECIRCLE);

		GenerateClone();
		m_bCloneActive = false;  // �N���[���I�����I��
	}
}

//==============================================
// �N���[����������
//==============================================
void CPlayer::GenerateClone() 
{
	D3DXVECTOR3 clonePos = m_pCloneCircle->GetSelectedPosition();
	CClone::Create(clonePos);  // �N���[���𐶐�
}

//==============================================
// �ʏ�X�V����
//==============================================
void CPlayer::PlayerMovement()
{
	CSound* pSound = CManager::GetSound();

	D3DXVECTOR3* pCamera = CCamera::GetRot();

	D3DXVECTOR3& pPos = CCharacter::GetPos();
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();
	D3DXVECTOR3& pRot = CCharacter::GetRot();

	pPosOld = pPos;

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

		if (m_JumpCnt <= 0)
		{
			if (m_Keyboard->GetTrigger(DIK_SPACE) == true || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_A) == true)
			{
				m_move.y = +m_PLAYER_JUMP;
				m_JumpCnt++;

				pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_JUMP);
			}
		}
	}

	m_move.y -= 1.0f;

	//�ʒu���X�V
	pPos.z += m_move.z;

	//�ړ��ʂ��X�V(����������)
	m_move.x += (0.0f - m_move.x) * 0.1f;
	//m_move.y += (0.0f - m_move.y) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	bool bIsLanding = false;

	pPos.x += m_move.x;

	for (int nCntPrio = 0; nCntPrio < 15; nCntPrio++)
	{// �v���C�I���e�B����

		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			if (IsBadReadPtr(pObj, sizeof(CObject)))
			{
				break;
			}

			// ���E�̓����蔻��
			CollisionLEFTRIGHT(pObj);
			pObj = pObj->GetNext();
		}
	}

	pPos.y += m_move.y;

	for (int nCntPrio = 0; nCntPrio < 15; nCntPrio++)
	{// �v���C�I���e�B����

		CObject* pObj = CObject::GetTop(nCntPrio);

		while (pObj != nullptr)
		{
			if (IsBadReadPtr(pObj, sizeof(CObject)))
			{
				break;
			}

			// �㉺�̓����蔻��
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
// �`�揈��
//==============================================
void CPlayer::Draw()
{
	if (CManager::IsPaused())
	{
		// �N���[���I�𒆂ɕ`��
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
// �㉺�̓����蔻��
//=====================================================
bool CPlayer::CollisionUPDOWN(bool& bIsLanding, CObject* pObj)
{
	// ���f���p�[�c�̃��[���h���W���擾
	//D3DXVECTOR3 pPos = { CCharacter::GetModelParts(1)->GetWoarldMatrix()._41 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._42 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._43 };

	D3DXVECTOR3& pPos = CCharacter::GetPos();
	// �v���C���[�̉ߋ��̍��W���擾
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();
	// ���f���p�[�c�̃T�C�Y���擾
	D3DXVECTOR3 pSize = CCharacter::GetModelParts(1)->GetSize();

	//D3DXVECTOR3 PartsPosOld = pPosOld + pPos;

	D3DXVECTOR3 PlayerSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	PlayerSize.x = (float(floor(m_size.x)));
	PlayerSize.y = (float(floor(m_size.y)));
	PlayerSize.z = (float(floor(m_size.z)));

	if (pObj != nullptr)
	{// pObj��nullptr����Ȃ��Ȃ�

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BLOCK)
		{// type��BLOCK�Ȃ�

			CBlock* pBlock = dynamic_cast<CBlock*>(pObj);
			if (pBlock != nullptr)
			{
				CBlock::BLOCK pBlockType = pBlock->GetBlockType();

				D3DXVECTOR3 pBlockPos = pBlock->GetPos();
				D3DXVECTOR3 pBlockMin = pBlock->GetMin();
				D3DXVECTOR3 pBlockMax = pBlock->GetMax();
				D3DXVECTOR3 pBlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				// �����̈ʂ��Ȃ�����
				D3DXVECTOR3 BlockSize = pBlock->GetSize();
				pBlockSize.x = (float)(floor(BlockSize.x));
				pBlockSize.y = (float)(floor(BlockSize.y));
				pBlockSize.z = (float)(floor(BlockSize.z));

				if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
				{
					// X���������Z�����̏d�Ȃ����x�����`�F�b�N
					bool isXOverlap = (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE) &&
						(pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE);

					bool isZOverlap = (pPos.z + PlayerSize.z * m_HALF_SIZE > pBlockPos.z - pBlockSize.z * m_HALF_SIZE) &&
						(pPos.z - PlayerSize.z * m_HALF_SIZE < pBlockPos.z + pBlockSize.z * m_HALF_SIZE);

					if (isXOverlap && isZOverlap)
					{
						// �㑤�̓����蔻��
						if (pPos.y < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
							pPosOld.y >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE)
						{
							// �v���C���[���u���b�N�̏�ɉ����߂�
							pPos.y = pBlockPos.y + pBlockSize.y * m_HALF_SIZE;
							m_move.y = 0.0f;
							bIsLanding = true; // ���n��Ԃ�ݒ�
							m_JumpCnt = 0;
						}
						// �����̓����蔻��
						else if (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y &&
							pPosOld.y + PlayerSize.y <= pBlockPos.y - pBlockSize.y)
						{
							// �v���C���[���u���b�N�̉��ɉ����߂�
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
						// �����J���Ă���ꍇ�͓����蔻����X�L�b�v
						return false;
					}

					// X���������Z�����̏d�Ȃ����x�����`�F�b�N
					bool isXOverlap = (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE) &&
						(pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE);

					if (isXOverlap)
					{
						// �㑤�̓����蔻��
						if (pPos.y < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
							pPosOld.y >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE)
						{
							// �v���C���[���u���b�N�̏�ɉ����߂�
							pPos.y = pBlockPos.y + pBlockSize.y * m_HALF_SIZE;
							m_move.y = 0.0f;
							bIsLanding = true; // ���n��Ԃ�ݒ�
							m_JumpCnt = 0;
						}
						// �����̓����蔻��
						else if (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y &&
							pPosOld.y + PlayerSize.y <= pBlockPos.y - pBlockSize.y)
						{
							// �v���C���[���u���b�N�̉��ɉ����߂�
							pPos.y = pBlockPos.y - pBlockSize.y - PlayerSize.y;
							m_move.y = 0.0f;
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_BUTTON)
				{
					// X���������Z�����̏d�Ȃ����x�����`�F�b�N
					bool isXOverlap = (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE) &&
						(pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE);

					if (isXOverlap)
					{
						// �㑤�̓����蔻��
						if (pPos.y < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
							pPosOld.y >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE)
						{
							// �v���C���[���u���b�N�̏�ɉ����߂�
							pPos.y = pBlockPos.y + pBlockSize.y * m_HALF_SIZE;
							m_move.y = 0.0f;
							bIsLanding = true; // ���n��Ԃ�ݒ�
							m_JumpCnt = 0;
						}
						// �����̓����蔻��
						else if (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y &&
							pPosOld.y + PlayerSize.y <= pBlockPos.y - pBlockSize.y)
						{
							// �v���C���[���u���b�N�̉��ɉ����߂�
							pPos.y = pBlockPos.y - pBlockSize.y - PlayerSize.y;
							m_move.y = 0.0f;
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_GOAL)
				{
					// X���������Z�����̏d�Ȃ����x�����`�F�b�N
					bool isXOverlap = (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE) &&
						(pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE);

					if (isXOverlap)
					{
						// �㑤�̓����蔻��
						if (pPos.y < pBlockPos.y + pBlockSize.y * m_HALF_SIZE &&
							pPosOld.y >= pBlockPos.y + pBlockSize.y * m_HALF_SIZE)
						{
							m_bUse = true;
						}
						// �����̓����蔻��
						else if (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y &&
							pPosOld.y + PlayerSize.y <= pBlockPos.y - pBlockSize.y)
						{
							m_bUse = true;
						}
					}
				}
			}
		}
	}
	return bIsLanding;
}

//=====================================================
// ���E�̓����蔻��
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
	{// pObj��nullptr����Ȃ��Ȃ�

		CObject::TYPE type = pObj->GetType();

		if (type == CObject::TYPE::TYPE_BLOCK)
		{// type��BLO CK�Ȃ�

			CBlock* pBlock = dynamic_cast<CBlock*>(pObj);
			if (pBlock != nullptr)
			{
				CBlock::BLOCK pBlockType = pBlock->GetBlockType();

				D3DXVECTOR3 pBlockPos = pBlock->GetPos();
				D3DXVECTOR3 pBlockMin = pBlock->GetMin();
				D3DXVECTOR3 pBlockMax = pBlock->GetMax();
				D3DXVECTOR3 pBlockSize = pBlock->GetSize();

				// �����̈ʂ��Ȃ�����
				D3DXVECTOR3 BlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				BlockSize.x = (float)(floor(pBlockSize.x));
				BlockSize.y = (float)(floor(pBlockSize.y));
				BlockSize.z = (float)(floor(pBlockSize.z));

				if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
				{
					// Y���������Z�����̏d�Ȃ����x�����`�F�b�N
					bool isYOverlap = (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y * m_HALF_SIZE) &&
						(pPos.y + PlayerSize.y <= pBlockPos.y + pBlockSize.y * m_HALF_SIZE);

					if (isYOverlap)
					{
						//�E���̓����蔻��
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + PlayerSize.x * m_HALF_SIZE;
						}
						//�����̓����蔻��
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
						// �����J���Ă���ꍇ�͓����蔻����X�L�b�v
						return;
					}

					// Y���������Z�����̏d�Ȃ����x�����`�F�b�N
					bool isYOverlap = (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y * m_HALF_SIZE) &&
						(pPos.y + PlayerSize.y <= pBlockPos.y + pBlockSize.y * m_HALF_SIZE);

					if (isYOverlap)
					{
						//�E���̓����蔻��
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + (PlayerSize.x * m_HALF_SIZE);
							m_move.x = 0.0f;
						}
						//�����̓����蔻��
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
					// Y���������Z�����̏d�Ȃ����x�����`�F�b�N
					bool isYOverlap = (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y * m_HALF_SIZE) &&
						(pPos.y + PlayerSize.y <= pBlockPos.y + pBlockSize.y * m_HALF_SIZE);

					if (isYOverlap)
					{
						//�E���̓����蔻��
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + (PlayerSize.x * m_HALF_SIZE);
							m_move.x = 0.0f;
						}
						//�����̓����蔻��
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
					// Y���������Z�����̏d�Ȃ����x�����`�F�b�N
					bool isYOverlap = (pPos.y + PlayerSize.y > pBlockPos.y - pBlockSize.y * m_HALF_SIZE - m_GOAL_CORRECTION) &&
						(pPos.y + PlayerSize.y <= pBlockPos.y + pBlockSize.y * m_HALF_SIZE + m_GOAL_CORRECTION);

					if (isYOverlap)
					{
						//�E���̓����蔻��
						if (pPos.x - PlayerSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x - PlayerSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
						{
							m_bUse = false;
						}
						//�����̓����蔻��
						else if (pPos.x + PlayerSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x + PlayerSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE)
						{
							m_bUse = false;
						}
					}
				}
			}
		}
	}
}

//=====================================================
// �S�[�����̎擾
//=====================================================
bool& CPlayer::GetGoal()
{
	return m_bUse;
}

//=====================================================
// ���f���̐���
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
// ���S�t���O�ݒ菈��
//=========================================
void CPlayer::SetDeath()
{
	CObject::SetDeath();
}
