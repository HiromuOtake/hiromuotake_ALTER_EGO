//==============================================
//
// ALTER_EGO[block.cpp]
// Author: hiromu otake
//
//==============================================

#include "block.h"
#include "objectX.h"
#include "manager.h"
#include "camera.h"
#include "texture.h"
#include "model.h"
#include "bullet.h"
#include "particlemanager.h"
#include <random>

CBlockButton::BUTTON_COLOR CBlockButton::m_LastPressedButton = CBlockButton::BUTTON_NORMAL;

//==============================================
// �R���X�g���N�^
//==============================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority), m_BlockType(BLOCK_NONE), m_Keyboard(nullptr), m_pVtxBuff(nullptr), m_bOpen(false)
, m_nModelIdx(0), m_nTimer(0), m_nTexIdx(0), m_move{ 0.0f,0.0f,0.0f }
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockNeedle::CBlockNeedle(int nPriority) : CBlock(nPriority), m_nModelIdx(0), m_nTexIdx(0)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockButton::CBlockButton(int nPriority) : CBlock(nPriority), m_nModelIdx(0), m_nTexIdx(0), m_bOpen(false), m_bColliderActive(false), m_bResetPending(false), m_bPressedOnce(false), m_Color(BUTTON_NORMAL)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockRedButton::CBlockRedButton(int nPriority) : CBlockButton(nPriority), m_Color(BUTTON_RED), m_nModelIdx(0), m_nTexIdx(0)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockBlueButton::CBlockBlueButton(int nPriority) : CBlockButton(nPriority), m_Color(BUTTON_BLUE), m_nModelIdx(0), m_nTexIdx(0)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockDoor::CBlockDoor(int nPriority, DOOR_COLOR color) : CBlock(nPriority), m_Color(color), m_deleteDoor(1.0f), m_nModelIdx(0), m_nTexIdx(0)
, m_Keyboard(nullptr), m_pPlayer(nullptr), m_bOpen(false), m_bColliderActive(true), m_bVisible(true)
{
	m_Timer = 0;
}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockRedDoor::CBlockRedDoor(int nPriority) : CBlockDoor(nPriority), m_color(DOOR_RED), m_nModelIdx(0), m_nTexIdx(0), m_bOpen(false),m_bColliderActive(false)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockBlueDoor::CBlockBlueDoor(int nPriority) : CBlockDoor(nPriority), m_color(DOOR_BLUE), m_nModelIdx(0), m_nTexIdx(0)
{

}

//==============================================
// �R���X�g���N�^
//==============================================
CBlockGoal::CBlockGoal(int nPriority) : CBlock(nPriority), m_nModelIdx(0), m_nTexIdx(0), m_fGoalRot(0.0f)
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlock::~CBlock()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockNeedle::~CBlockNeedle()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockButton::~CBlockButton()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockRedButton::~CBlockRedButton()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockBlueButton::~CBlockBlueButton()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockDoor::~CBlockDoor()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockRedDoor::~CBlockRedDoor()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockBlueDoor::~CBlockBlueDoor()
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CBlockGoal::~CBlockGoal()
{

}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlock::Init()
{
	SetType(TYPE_BLOCK);

	m_Keyboard = CManager::GetKeyboard();

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\neonblock.x");
	m_nTexIdx = CManager::GetTexture()->Regist("data\\Texture\\neonblock.png");

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockNeedle::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\neonneedle.x");
	m_nTexIdx = CManager::GetTexture()->Regist("data\\Texture\\needle.png");

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockButton::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\switch.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	m_bOpen = false;				// ������Ԃ͕������
	m_bColliderActive = true;		// ������Ԃ͓����蔻���L���ɂ���

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockRedButton::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\switch_R.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	m_bOpen = false;				// ������Ԃ͕������
	m_bColliderActive = true;		// ������Ԃ͓����蔻���L���ɂ���

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockBlueButton::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\switch_B.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	m_bOpen = false;				// ������Ԃ͕������
	m_bColliderActive = true;		// ������Ԃ͓����蔻���L���ɂ���

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockDoor::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\door.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	m_bOpen = false;				// ������Ԃ͕������
	m_bColliderActive = true;		// ������Ԃ͓����蔻���L���ɂ���

	D3DXVECTOR3& move = GetMove();
	move = D3DXVECTOR3(0.0f, 0.3f, 0.0f);

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockRedDoor::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\door_R.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	m_bOpen = false;				// ������Ԃ͕������
	m_bColliderActive = true;		// ������Ԃ͓����蔻���L���ɂ���

	D3DXVECTOR3& move = GetMove();
	move = D3DXVECTOR3(0.0f, 0.3f, 0.0f);

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockBlueDoor::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\door_B.x");
	m_nTexIdx = -1;

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	m_bOpen = false;				// ������Ԃ͕������
	m_bColliderActive = true;		// ������Ԃ͓����蔻���L���ɂ���

	D3DXVECTOR3& move = GetMove();
	move = D3DXVECTOR3(0.0f, 0.3f, 0.0f);

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �����ݒ�
//==============================================
HRESULT CBlockGoal::Init()
{
	SetType(TYPE_BLOCK);

	CModel* pModel = CManager::GetModel();

	m_nModelIdx = pModel->Regist("data\\MODEL\\x\\goal.x");
	m_nTexIdx = CManager::GetTexture()->Regist("data\\Texture\\potal3.png");

	CObjectX::BindModel(pModel->GetBuffMat(m_nModelIdx),
		pModel->GetNumMat(m_nModelIdx),
		pModel->GetMesh(m_nModelIdx));

	BindTexture(CManager::GetTexture()->GetAddress(m_nTexIdx));

	CObjectX::Init();

	return S_OK;
}

//==============================================
// �I������
//==============================================
void CBlock::Uninit()
{
	CObjectX::Uninit();
}

//==============================================
// �I������
//==============================================
void CBlockNeedle::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// �I������
//==============================================
void CBlockButton::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// �I������
//==============================================
void CBlockDoor::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// �I������
//==============================================
void CBlockGoal::Uninit()
{
	CBlock::Uninit();
}

//==============================================
// �X�V����
//==============================================
void CBlock::Update()
{
	// ��]�s���K�p
	if (m_fRotation != 0.0f)
	{
		D3DXMATRIX matRotation;
		D3DXMatrixRotationY(&matRotation, D3DXToRadian(m_fRotation));  // Y����]

		// ���[���h�s��ɉ�]��K�p
		D3DXMatrixMultiply(&m_matWorld, &matRotation, &m_matWorld);
	}

	CObjectX::Update();
}

//==============================================
// �X�V����
//==============================================
void CBlockNeedle::Update()
{
	CBlock::Update();
}

//==============================================
// �X�V����
//==============================================
void CBlockButton::Update()
{
	CSound* pSound = CManager::GetSound();
	D3DXVECTOR3 pos = CBlockButton::GetPos();
	D3DXVECTOR3 buttonPos = GetPos();                // �{�^���̃��[���h���W

	// NORMAL�{�^�������łɈ�x������Ă����ꍇ�͉������Ȃ�
	if (m_Color == BUTTON_NORMAL && m_bPressedOnce)
	{
		CBlock::Update();
		return;
	}

	// �{�^����������
	bool bPressed = false;

	// �v���C���[��N���[���Ƃ̏Փ˔���
	for (const auto& object : CObject::GetAllObjects())
	{
		if (object->GetType() == TYPE_PLAYER)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(object);
			if (player != nullptr && IsCollisionPlayer(player))
			{
				bPressed = true;
				break;
			}
		}
		else if (object->GetType() == TYPE_CLONE)
		{
			CClone* clone = dynamic_cast<CClone*>(object);
			if (clone != nullptr && IsCollisionClone(clone))
			{
				bPressed = true;
				break;
			}
		}
	}

	// �{�^���������ꂽ�ꍇ�̏���
	if (bPressed && !m_bOpen)
	{
		if (m_Color == BUTTON_NORMAL)
		{
			m_bOpen = true;
			m_bPressedOnce = true;  // NORMAL�{�^������x�����ꂽ���Ƃ��L�^

			// �ʏ�̔����J��
			for (auto* object : CObject::GetAllObjects())
			{
				if (CBlockDoor* door = dynamic_cast<CBlockDoor*>(object))
				{
					if (door->GetColor() == CBlockDoor::DOOR_NORMAL)
					{
						door->OpenAndClose(true);  // �ʏ�̔����J��
					}
				}
			}

			// �p�[�e�B�N�������ƌ��ʉ�
			CParticleManager* pParticleManager = CManager::GetParticleManager();
			pParticleManager->EmitParticles(buttonPos, 40, 1.0f, 3.0f, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
			pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_BUTON);
		}
		else
		{
			// ���̐F�̃{�^���̏ꍇ�̏����i�Ԃ�̌��݉�������j
			if ((m_Color == BUTTON_RED && m_LastPressedButton != BUTTON_RED) ||
				(m_Color == BUTTON_BLUE && m_LastPressedButton != BUTTON_BLUE))
			{
				m_bOpen = true;
				m_LastPressedButton = m_Color;  // �Ō�ɉ����ꂽ�{�^�����L�^
				m_bResetPending = true;  // ���Z�b�g�҂���Ԃɐݒ�

				// ���̊J����
				for (auto* object : CObject::GetAllObjects())
				{
					if (CBlockDoor* door = dynamic_cast<CBlockDoor*>(object))
					{
						if (m_Color == BUTTON_RED && door->GetColor() == CBlockDoor::DOOR_RED)
						{
							door->OpenAndClose(true);  // �Ԃ������J��
						}
						else if (m_Color == BUTTON_BLUE && door->GetColor() == CBlockDoor::DOOR_BLUE)
						{
							door->OpenAndClose(true);  // �������J��
						}
						else if (m_Color == BUTTON_RED && door->GetColor() == CBlockDoor::DOOR_BLUE)
						{
							door->OpenAndClose(false);  // ���������
						}
						else if (m_Color == BUTTON_BLUE && door->GetColor() == CBlockDoor::DOOR_RED)
						{
							door->OpenAndClose(false);  // �Ԃ��������
						}
					}
				}

				// �p�[�e�B�N�������ƌ��ʉ�
				CParticleManager* pParticleManager = CManager::GetParticleManager();
				pParticleManager->EmitParticles(buttonPos, 40, 1.0f, 3.0f, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
				pSound->PlaySound(CSound::SOUND_LABEL::SOUND_LABEL_SE_BUTON);
			}
		}
	}
	// �{�^���̏�Ԃ����Z�b�g����
	if (!bPressed)
	{
		m_bOpen = false;
	}

	CBlock::Update();
}

//==============================================
// �X�V����
//==============================================
void CBlockDoor::Update()
{
	if (!m_bColliderActive)
	{
		return;
	}

	bool bOpenDoor = false;

	// �L�[�̎擾
	const std::string& key = GetPairKey();

	// �L�[�����݂���
	if (key != "none")
	{ 
		// �L�[�ɑΉ�����S�ẴI�u�W�F�N�g�ɑ΂��ď������s��
		for (const auto& object : CObject::GetPair()[key])
		{
			if (object == nullptr)
			{ // �󂾂���
				continue;
			}

			if (this == object)
			{ // �������g������
				continue;
			}

			if (CBlockButton* button = dynamic_cast<CBlockButton*>(object))
			{
				if (button->GetOpenDoor())
				{
					bOpenDoor = true;
					break;
				}
			}
			else
			{
				break;
			}
		}
	}

	if (bOpenDoor == true)
	{
		//m_deleteDoor--;

		//CBlockDoor::SetScale(D3DXVECTOR3(m_deleteDoor, m_deleteDoor, m_deleteDoor));

		m_Timer++;
		if (m_Timer >= 20)
		{
			Uninit();
			CObject::SetDeath();
		}
	}
	CBlock::Update();
}

//==============================================
// �X�V����
//==============================================
void CBlockGoal::Update()
{
	m_fGoalRot += 0.01f;
	
	CObjectX::SetRot(D3DXVECTOR3(0.0f, 0.0f, m_fGoalRot));

	CBlock::Update();
}

//==============================================
// �`�揈��
//==============================================
void CBlock::Draw()
{
	CObjectX::Draw();
}

//==============================================
// �`�揈��
//==============================================
void CBlockNeedle::Draw()
{
	CBlock::Draw();
}

//==============================================
// �`�揈��
//==============================================
void CBlockButton::Draw()
{
	CBlock::Draw();
}

//==============================================
// �`�揈��
//==============================================
void CBlockDoor::Draw()
{
	// �����J���Ă���ꍇ�͕`�悵�Ȃ�
	if (!m_bOpen)
	{
		CBlock::Draw();
	}
}

//==============================================
// �`�揈��
//==============================================
void CBlockGoal::Draw()
{
	CBlock::Draw();
}

//==============================================
// �{�^���ƃv���C���[�̓����蔻��
//==============================================
bool CBlockButton::IsCollisionPlayer(CPlayer* player)
{
	D3DXVECTOR3 playerPos = player->GetPos();		// �v���C���[�̃��[���h���W
	D3DXVECTOR3 buttonPos = GetPos();				// �{�^���̃��[���h���W

	// �v���C���[�ƃ{�^���̑��Έʒu���v�Z
	D3DXVECTOR3 relativePos = playerPos - buttonPos;

	// �{�^���̉�]�s����쐬�i�t��]�j
	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(-m_fRotation));	// �t��]�Ń��[�J�����W�ɖ߂�

	// ���Έʒu���{�^���̃��[�J�����W�n�ɕϊ�
	D3DXVECTOR3 transformedPos;
	D3DXVec3TransformCoord(&transformedPos, &relativePos, &matRotationZ);

	// �{�^���̃T�C�Y���擾
	D3DXVECTOR3 buttonSize = GetSize();

	// �I�t�Z�b�g�l�̐ݒ�iX����Z���͏����߁AY���͂��̂܂܁j
	const float offsetXZ = 10.0;	// X����Z���̃I�t�Z�b�g�l�i�����蔻����k���j
	const float offsetY = 20.0f;	// Y���̃I�t�Z�b�g�i�K�v�Ȃ�������j

	// �ϊ���̍��W���g���ē����蔻����s��
	bool isOnTop = (transformedPos.y > 0.0f + offsetY && transformedPos.y < buttonSize.y - offsetY);

	// X����Z���͈͓̔��ɂ��邩�𔻒�i�I�t�Z�b�g��K�p�j
	return (transformedPos.x > -buttonSize.x + offsetXZ &&
		transformedPos.x < buttonSize.x - offsetXZ &&
		transformedPos.z > -buttonSize.z + offsetXZ &&
		transformedPos.z < buttonSize.z - offsetXZ &&
		isOnTop);
}

//==============================================
// �{�^���ƃN���[���̓����蔻��
//==============================================
bool CBlockButton::IsCollisionClone(CClone* clone)
{
	D3DXVECTOR3 clonePos = clone->GetPos();			// �v���C���[�̃��[���h���W
	D3DXVECTOR3 buttonPos = GetPos();				// �{�^���̃��[���h���W

	// �v���C���[�ƃ{�^���̑��Έʒu���v�Z
	D3DXVECTOR3 relativePos = clonePos - buttonPos;

	// �{�^���̉�]�s����쐬�i�t��]�j
	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(-m_fRotation));	// �t��]�Ń��[�J�����W�ɖ߂�

	// ���Έʒu���{�^���̃��[�J�����W�n�ɕϊ�
	D3DXVECTOR3 transformedPos;
	D3DXVec3TransformCoord(&transformedPos, &relativePos, &matRotationZ);

	// �{�^���̃T�C�Y���擾
	D3DXVECTOR3 buttonSize = GetSize();

	// �I�t�Z�b�g�l�̐ݒ�iX����Z���͏����߁AY���͂��̂܂܁j
	const float offsetXZ = 20.0;	// X����Z���̃I�t�Z�b�g�l�i�����蔻����k���j
	const float offsetY = 20.0f;	// Y���̃I�t�Z�b�g�i�K�v�Ȃ�������j

	// �ϊ���̍��W���g���ē����蔻����s��
	bool isOnTop = (transformedPos.y > 0.0f + offsetY && transformedPos.y < buttonSize.y - offsetY);

	// X����Z���͈͓̔��ɂ��邩�𔻒�i�I�t�Z�b�g��K�p�j
	return (transformedPos.x > -buttonSize.x + offsetXZ &&
		transformedPos.x < buttonSize.x - offsetXZ &&
		transformedPos.z > -buttonSize.z + offsetXZ &&
		transformedPos.z < buttonSize.z - offsetXZ &&
		isOnTop);
}

//==============================================
// �u���b�N�̃^�C�v�ݒ菈��
//==============================================
void CBlock::SetBlockType(BLOCK BlockType)
{
	m_BlockType = BlockType;
}

//==============================================
// �u���b�N�̃^�C�v�擾����
//==============================================
CBlock::BLOCK CBlock::GetBlockType()
{
	return m_BlockType;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlock* CBlock::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlock* pBlock = new CBlock();

	if (pBlock != nullptr)
	{
		pBlock->SetBlockType(nType);
		pBlock->Init();
		pBlock->SetPos(pos);
		pBlock->SetUseDeath(true);
	}
	return  pBlock;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockNeedle* CBlockNeedle::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockNeedle* pBlockNeedle = new CBlockNeedle();

	if (pBlockNeedle != nullptr)
	{
		pBlockNeedle->SetBlockType(nType);
		pBlockNeedle->Init();
		pBlockNeedle->SetPos(pos);
		pBlockNeedle->SetUseDeath(true);
	}
	return  pBlockNeedle;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockButton* CBlockButton::Create(D3DXVECTOR3 pos, BLOCK nType, BUTTON_COLOR color)
{
	CBlockButton* pBlockButton = new CBlockButton();

	if (pBlockButton != nullptr)
	{
		pBlockButton->SetBlockType(nType);
		pBlockButton->SetColor(color);  // �F��ݒ�
		pBlockButton->Init();
		pBlockButton->SetPos(pos);
		pBlockButton->SetUseDeath(true);
	}
	return  pBlockButton;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockRedButton* CBlockRedButton::Create(D3DXVECTOR3 pos, BUTTON_COLOR color)
{
	CBlockRedButton* pBlockButton = new CBlockRedButton();
	if (pBlockButton != nullptr)
	{
		pBlockButton->SetBlockType(BLOCK_BUTTON);
		pBlockButton->SetColor(color);  // �F��ݒ�
		pBlockButton->Init();
		pBlockButton->SetPos(pos);
		pBlockButton->SetUseDeath(true);
	}
	return pBlockButton;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockBlueButton* CBlockBlueButton::Create(D3DXVECTOR3 pos, BUTTON_COLOR color)
{
	CBlockBlueButton* pBlockButton = new CBlockBlueButton();
	if (pBlockButton != nullptr)
	{
		pBlockButton->SetBlockType(BLOCK_BUTTON);
		pBlockButton->SetColor(color);  // �F��ݒ�
		pBlockButton->Init();
		pBlockButton->SetPos(pos);
		pBlockButton->SetUseDeath(true);
	}
	return pBlockButton;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockDoor* CBlockDoor::Create(D3DXVECTOR3 pos, BLOCK nType, DOOR_COLOR color)
{
	CBlockDoor* pBlockDoor = new CBlockDoor(3, color);

	if (pBlockDoor != nullptr)
	{
		pBlockDoor->SetBlockType(nType);
		//pBlockDoor->SetColor(color);  // �F��ݒ�
		pBlockDoor->Init();
		pBlockDoor->SetPos(pos);
		pBlockDoor->SetUseDeath(true);
	}
	return  pBlockDoor;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockRedDoor* CBlockRedDoor::Create(D3DXVECTOR3 pos, DOOR_COLOR color)
{
	CBlockRedDoor* pBlockDoor = new CBlockRedDoor();
	if (pBlockDoor != nullptr)
	{
		pBlockDoor->SetBlockType(BLOCK_DOOR);
		pBlockDoor->SetColor(color);  // �F��ݒ�
		pBlockDoor->Init();
		pBlockDoor->SetPos(pos);
		pBlockDoor->SetUseDeath(true);
	}
	return pBlockDoor;
}

//=====================================================
// ���f���̐���
//=====================================================
CBlockBlueDoor* CBlockBlueDoor::Create(D3DXVECTOR3 pos, DOOR_COLOR color)
{
	CBlockBlueDoor* pBlockDoor = new CBlockBlueDoor();
	if (pBlockDoor != nullptr)
	{
		pBlockDoor->SetBlockType(BLOCK_DOOR);
		pBlockDoor->SetColor(color);  // �F��ݒ�
		pBlockDoor->Init();
		pBlockDoor->SetPos(pos);
		pBlockDoor->SetUseDeath(true);
	}
	return pBlockDoor;
}
//=====================================================
// ���f���̐���
//=====================================================
CBlockGoal* CBlockGoal::Create(D3DXVECTOR3 pos, BLOCK nType)
{
	CBlockGoal* pBlockGial = new CBlockGoal();

	if (pBlockGial != nullptr)
	{
		pBlockGial->SetBlockType(nType);
		pBlockGial->Init();
		pBlockGial->SetPos(pos);
		pBlockGial->SetUseDeath(true);
	}
	return  pBlockGial;
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBlock::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBlockNeedle::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBlockButton::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBlockDoor::SetDeath()
{
	CObject::SetDeath();
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CBlockGoal::SetDeath()
{
	CObject::SetDeath();
}

//==============================================
// ���̏�Ԏ擾����
//==============================================
bool& CBlockButton::GetOpenDoor()
{
	return m_bOpen;
}

//==============================================
// �{�^���̃}�e���A���J���[�ύX����
//==============================================
void CBlockButton::SetMatColor(D3DMATERIAL9* pMat, int nMatIdx)
{
	// �}�e���A���̌����ڂ̏�����
	if (nMatIdx == 2)
	{
		pMat->Diffuse.g = pMat->Diffuse.b = pMat->Diffuse.r = 1.0f;
	}

	// �{�^���������Ȃ���ԂȂ�D�F�ɂ���
	if ((m_Color == BUTTON_RED && m_LastPressedButton == BUTTON_RED) ||
		(m_Color == BUTTON_BLUE && m_LastPressedButton == BUTTON_BLUE))
	{
		if (nMatIdx == 2)
		{
			pMat->Diffuse.g = pMat->Diffuse.b = pMat->Diffuse.r = 0.5f;
		}
		return; // �����ŏ������I�����A�{�^���̐F���D�F�ɌŒ肷��
	}
	else if (GetColor() == CBlockButton::BUTTON_NORMAL)
	{
		if (m_bOpen == true)
		{
			if (nMatIdx == 2)
			{
				pMat->Diffuse.g = pMat->Diffuse.b = pMat->Diffuse.r = 0.5f;
			}
			return; // �����ŏ������I�����A�{�^���̐F���D�F�ɌŒ肷��
		}
	}

	// �Ԃ��{�^����������
	if (GetColor() == CBlockButton::BUTTON_RED)
	{
		if (m_bOpen == false)
		{
			if (nMatIdx == 2)
			{
				pMat->Diffuse.g = pMat->Diffuse.b = 0.0f;
			}
		}
	}
	// ���{�^����������
	else if (GetColor() == CBlockButton::BUTTON_BLUE)
	{
		if (m_bOpen == false)
		{
			if (nMatIdx == 2)
			{
				pMat->Diffuse.g = pMat->Diffuse.r = 0.0f;
			}
		}
	}
	// �ʏ�̃{�^����������
	else if(GetColor() == CBlockButton::BUTTON_NORMAL)
	{
		if (m_bOpen == false)
		{
			if (nMatIdx == 2)
			{
				pMat->Diffuse.g = pMat->Diffuse.b = 0.0f;
			}
		}
	}
}

//=========================================
// ���̊J����
//=========================================
void CBlockDoor::OpenAndClose(bool open)
{
	m_bOpen = open;
	m_bColliderActive = !open;	// �J�����瓖���蔻��𖳌��ɂ���
	m_bVisible = !open;			// ���̕\���E��\���𐧌䂷��
}