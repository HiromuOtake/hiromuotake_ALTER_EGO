//==============================================
//
// ALTER_EGO[clone.cpp]
// Author: hiromu otake
//
//==============================================

#include "clone.h"
#include "manager.h"
#include "camera.h"
#include "block.h"
#include "field.h"
#include "item.h"
#include "bullet.h"
#include "game.h"
#include "Tutorial.h"
#include "character.h"

bool CClone::m_bUse = true;

//==============================================
// �R���X�g���N�^
//==============================================
CClone::CClone(int nPriority) : CCharacter(nPriority), m_bIsLanding(false), m_bJumping(false), m_bIsRight(false), m_Keyboard(nullptr), m_JoyPad(nullptr), m_pModelParts{}
, m_nModelIdx(0), m_nTextureIdx(0), m_nLife(0), m_nType(PLAYER_NONE), m_nDeathTimer(0), m_JumpCnt(0)
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CClone::~CClone()
{

}

//==============================================
// �����ݒ�
//==============================================
HRESULT CClone::Init()
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
void CClone::Uninit()
{
	CCharacter::Uninit();
}

//==============================================
// �X�V����
//==============================================
void CClone::Update()
{
	if (CManager::IsPaused())
	{
		if (m_Keyboard->GetTrigger(DIK_RETURN) || m_JoyPad->GetJoyPadPress(CInput::JOYKEY_B) == true)
		{
			CManager::SetPaused(false); // �|�[�Y����
		}

		return;
	}

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
			CCharacter::SetMotion(MOTION_NEUTRAL);
		}

		if (m_JumpCnt <= 0)
		{
			if (m_Keyboard->GetTrigger(DIK_SPACE) == true || m_JoyPad->GetJoyPadTrigger(CInput::JOYKEY_A) == true)
			{
				m_move.y = +m_PLAYER_JUMP;
				m_JumpCnt++;

				CSound* pSound = CManager::GetSound();

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

	CCharacter::PlayerMotion();

	CCharacter::Update();
}

//==============================================
// �`�揈��
//==============================================
void CClone::Draw()
{
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
bool CClone::CollisionUPDOWN(bool& bIsLanding, CObject* pObj)
{
	D3DXVECTOR3& pPos = CCharacter::GetPos();
	// �v���C���[�̉ߋ��̍��W���擾
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();
	// ���f���p�[�c�̃T�C�Y���擾
	D3DXVECTOR3 pSize = CCharacter::GetModelParts(1)->GetSize();

	D3DXVECTOR3 CloneSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CloneSize.x = (float(floor(m_size.x)));
	CloneSize.y = (float(floor(m_size.y)));
	CloneSize.z = (float(floor(m_size.z)));

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
					bool isXOverlap = (pPos.x + CloneSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE) &&
						(pPos.x - CloneSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE);

					bool isZOverlap = (pPos.z + CloneSize.z * m_HALF_SIZE > pBlockPos.z - pBlockSize.z * m_HALF_SIZE) &&
						(pPos.z - CloneSize.z * m_HALF_SIZE < pBlockPos.z + pBlockSize.z * m_HALF_SIZE);

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
						else if (pPos.y + CloneSize.y > pBlockPos.y - pBlockSize.y &&
							pPosOld.y + CloneSize.y <= pBlockPos.y - pBlockSize.y)
						{
							// �v���C���[���u���b�N�̉��ɉ����߂�
							pPos.y = pBlockPos.y - pBlockSize.y - CloneSize.y;
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
					bool isXOverlap = (pPos.x + CloneSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE) &&
						(pPos.x - CloneSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE);

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
						else if (pPos.y + CloneSize.y > pBlockPos.y - pBlockSize.y &&
							pPosOld.y + CloneSize.y <= pBlockPos.y - pBlockSize.y)
						{
							// �v���C���[���u���b�N�̉��ɉ����߂�
							pPos.y = pBlockPos.y - pBlockSize.y - CloneSize.y;
							m_move.y = 0.0f;
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_BUTTON)
				{
					// X���������Z�����̏d�Ȃ����x�����`�F�b�N
					bool isXOverlap = (pPos.x + CloneSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE) &&
						(pPos.x - CloneSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE);

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
						else if (pPos.y + CloneSize.y > pBlockPos.y - pBlockSize.y &&
							pPosOld.y + CloneSize.y <= pBlockPos.y - pBlockSize.y)
						{
							// �v���C���[���u���b�N�̉��ɉ����߂�
							pPos.y = pBlockPos.y - pBlockSize.y - CloneSize.y;
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
// ���E�̓����蔻��
//=====================================================
void CClone::CollisionLEFTRIGHT(CObject* pObj)
{
	//D3DXVECTOR3 pPos = { CCharacter::GetModelParts(1)->GetWoarldMatrix()._41 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._42 ,CCharacter::GetModelParts(1)->GetWoarldMatrix()._43 };
	D3DXVECTOR3& pPos = CCharacter::GetPos();
	D3DXVECTOR3& pPosOld = CCharacter::GetPosOld();

	//D3DXVECTOR3 pSize = CCharacter::GetModelParts(1)->GetSize();

	D3DXVECTOR3 CloneSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CloneSize.x = (float(floor(m_size.x)));
	CloneSize.y = (float(floor(m_size.y)));
	CloneSize.z = (float(floor(m_size.z)));

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
				D3DXVECTOR3 pBlockSize = pBlock->GetSize();

				// �����̈ʂ��Ȃ�����
				D3DXVECTOR3 BlockSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				BlockSize.x = (float)(floor(pBlockSize.x));
				BlockSize.y = (float)(floor(pBlockSize.y));
				BlockSize.z = (float)(floor(pBlockSize.z));

				if (pBlockType == CBlock::BLOCK::BLOCK_NORMAL)
				{
					// Y���������Z�����̏d�Ȃ����x�����`�F�b�N
					bool isYOverlap = (pPos.y + CloneSize.y > pBlockPos.y - pBlockSize.y * m_HALF_SIZE) &&
						(pPos.y + CloneSize.y <= pBlockPos.y + pBlockSize.y * m_HALF_SIZE);

					if (isYOverlap)
					{
						//�E���̓����蔻��
						if (pPos.x - CloneSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x - CloneSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + CloneSize.x * m_HALF_SIZE;
						}
						//�����̓����蔻��
						else if (pPos.x + CloneSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x + CloneSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x - pBlockSize.x * m_HALF_SIZE - CloneSize.x * m_HALF_SIZE;
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
					bool isYOverlap = (pPos.y + CloneSize.y > pBlockPos.y - pBlockSize.y * m_HALF_SIZE) &&
						(pPos.y + CloneSize.y <= pBlockPos.y + pBlockSize.y * m_HALF_SIZE);

					if (isYOverlap)
					{
						//�E���̓����蔻��
						if (pPos.x - CloneSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x - CloneSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + (CloneSize.x * m_HALF_SIZE);
							m_move.x = 0.0f;
						}
						//�����̓����蔻��
						else if (pPos.x + CloneSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x + CloneSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x - pBlockSize.x * m_HALF_SIZE - (CloneSize.x * m_HALF_SIZE);
							m_move.x = 0.0f;
						}
					}
				}
				else if (pBlockType == CBlock::BLOCK::BLOCK_BUTTON)
				{
					// Y���������Z�����̏d�Ȃ����x�����`�F�b�N
					bool isYOverlap = (pPos.y + CloneSize.y > pBlockPos.y - pBlockSize.y * m_HALF_SIZE) &&
						(pPos.y + CloneSize.y <= pBlockPos.y + pBlockSize.y * m_HALF_SIZE);

					if (isYOverlap)
					{
						//�E���̓����蔻��
						if (pPos.x - CloneSize.x * m_HALF_SIZE < pBlockPos.x + pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x - CloneSize.x * m_HALF_SIZE >= pBlockPos.x + pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x + pBlockSize.x * m_HALF_SIZE + (CloneSize.x * m_HALF_SIZE);
							m_move.x = 0.0f;
						}
						//�����̓����蔻��
						else if (pPos.x + CloneSize.x * m_HALF_SIZE > pBlockPos.x - pBlockSize.x * m_HALF_SIZE &&
							pPosOld.x + CloneSize.x * m_HALF_SIZE <= pBlockPos.x - pBlockSize.x * m_HALF_SIZE)
						{
							pPos.x = pBlockPos.x - pBlockSize.x * m_HALF_SIZE - (CloneSize.x * m_HALF_SIZE);
							m_move.x = 0.0f;
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
bool& CClone::GetGoal()
{
	return m_bUse;
}

//=====================================================
// ���f���̐���
//=====================================================
CClone* CClone::Create(D3DXVECTOR3 pos)
{
	CClone* pClone = new CClone;

	if (pClone != nullptr)
	{
		pClone->SetType(TYPE_CLONE);
		pClone->Init();
		pClone->SetPos(pos);
		pClone->SetUseDeath(true);
	}
	return  pClone;
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CClone::SetDeath()
{
	CObject::SetDeath();
}
