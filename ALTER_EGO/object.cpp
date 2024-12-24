//======================================================
//
// ALTER_EGO [object.cpp]
// Auther : ��|�
//
//======================================================

#include "object.h"

// �ÓI�����o������
int CObject::m_nNumAll = 0;
CObject* CObject::m_pTop[m_MAXPRIORITY] = { nullptr };
CObject* CObject::m_pCur[m_MAXPRIORITY] = { nullptr };

// �ÓI�I�u�W�F�N�g
std::unordered_map<std::string, std::vector<CObject*>> CObject::m_pair;

//======================================================
// �R���X�g���N�^ (�������g�̓o�^)
//======================================================
CObject::CObject(int nPriority) : m_nPriority(0), m_Type(TYPE_NONE), m_Death(false),m_bUseDeath(false)
{
	m_nPriority = nPriority;

	m_nNumAll++;							// �������J�E���g�A�b�v

	if (m_pTop[nPriority] == nullptr)
	{
		m_pTop[nPriority] = this;					// �I�u�W�F�N�g(���g)�����X�g�ɒǉ�
		m_pCur[nPriority] = this;					// �I�u�W�F�N�g(���g)�����X�g�ɒǉ�
		m_pPrev = nullptr;							// ��ԍŏ��̃I�u�W�F�N�g�Ȃ̂őO����������
		m_pNext = nullptr;							// ��ԍŏ��̃I�u�W�F�N�g�Ȃ̂őO����������
	}
	else
	{
		CObject* pCur = m_pCur[nPriority];
		pCur->SetNext(this);
		m_pPrev = pCur;								// �J�����g���X�V����O�Ƀv���r���[�ɏ���n��
		m_pCur[nPriority] = this;					// �������ŐV�Ȃ̂Ŏ����̏��������
		m_pNext = nullptr;							// ��ԍŐV�̃I�u�W�F�N�g�Ȃ̂Ŏ��͖���
	}
}

//======================================================
// �f�X�g���N�^
//======================================================
CObject::~CObject()
{

}

//======================================================
// �S�I�u�W�F�N�g���
//======================================================
void CObject::ReleaseAll()
{
	m_pair.clear();

	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->SetDeath();
			pObj = pNext;
		}
	}
}

//======================================================
// �S�I�u�W�F�N�g�X�V
//======================================================
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];		// �擪�擾
	
		// �ő吔���s���Ȃ̂�While���g�p
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			if (pObj != nullptr)  // nullptr�`�F�b�N
			{
				pObj->Update();
			}
			pObj = pNext;
		}
	}
	DeleateProcess();
}

//======================================================
// �S�I�u�W�F�N�g�`��
//======================================================
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];
	
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			pObj->Draw();
			pObj = pNext;
		}
	}
}

//======================================================
// �������g�̉��
//======================================================
void CObject::Release()
{
	if (this == nullptr) return;

	
	if (m_pPrev != nullptr)
	{
		m_pPrev->m_pNext = m_pNext;
	}
	else 
	{
		m_pTop[m_nPriority] = m_pNext;
	}

	if (m_pNext != nullptr) 
	{
		m_pNext->m_pPrev = m_pPrev;
	}
	else 
	{
		m_pCur[m_nPriority] = m_pPrev;
	}

	m_pNext = nullptr;
	m_pPrev = nullptr;

	m_nNumAll--;	// �������J�E���g�_�E��

	delete this;
}

//======================================================
// ���S�t���O�̐ݒ�
//======================================================
void CObject::SetDeath()
{
	if (m_bUseDeath == true)
	{
		m_Death = true;
	}
}

//======================================================
// ���S�t���O���g�p���邩�ǂ���
//======================================================
void CObject::SetUseDeath(bool bUseDeath)
{
	m_bUseDeath = bUseDeath;
}

//======================================================
// ���S�t���O��������
//======================================================
void CObject::DeleateProcess()
{
	for (int nCnt = 0; nCnt < m_MAXPRIORITY; nCnt++)
	{
		CObject* pObj = m_pTop[nCnt];		// �擪�擾

		// �ő吔���s���Ȃ̂�While���g�p
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;
			if (pObj->m_Death == true)
			{
				pObj->Uninit();
				pObj->Release();
			}
			pObj = pNext;
		}
	}
}

//======================================================
// �^�C�v�̐ݒ�
//======================================================
void CObject::SetType(TYPE type)
{
	m_Type = type;
}

//======================================================
// �^�C�v�̎擾
//======================================================
CObject::TYPE CObject::GetType()
{
	return m_Type;
}

//======================================================
// �I�u�W�F�N�g�̎擾
//======================================================
CObject* CObject::GetTop(int nPrio)
{
	return m_pTop[nPrio];
}

//======================================================
// ���̃I�u�W�F�N�g�̐ݒ�
//======================================================
void CObject::SetNext(CObject* pObject)
{
	m_pNext = pObject;
}

//======================================================
// ���̃I�u�W�F�N�g�̎擾
//======================================================
CObject* CObject::GetNext()
{
	return m_pNext;
}

//======================================================
// �y�A�ɃI�u�W�F�N�g��ǉ�
//======================================================
void CObject::AddToPair(const std::string& key, CObject* object)
{
	if (!object || key.empty())
		return;

	// �d���o�^��h��
	auto& objects = m_pair[key];
	if (std::find(objects.begin(), objects.end(), object) == objects.end())
	{
		objects.push_back(object);
	}
}

void CObject::RemoveFromPair(const std::string& key, CObject* object)
{
	if (m_pair.count(key) == 0)
		return;

	auto& objects = m_pair[key];
	objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());

	// ���X�g����ɂȂ�����G���g�����̂��폜
	if (objects.empty())
	{
		m_pair.erase(key);
	}
}

std::vector<CObject*>& CObject::GetPairObjects(const std::string& key)
{
	return m_pair[key];
}

std::vector<CObject*> CObject::GetAllObjects()
{
	std::vector<CObject*> objects;

	for (int nCnt = 0; nCnt < m_MAXPRIORITY; ++nCnt)
	{
		CObject* pObj = m_pTop[nCnt];

		while (pObj != nullptr)
		{
			objects.push_back(pObj); // ���݂̃I�u�W�F�N�g�����X�g�ɒǉ�
			pObj = pObj->GetNext();
		}
	}

	return objects;
}

CObject* CObject::FindFirstOfType(TYPE type)
{
	auto objects = GetAllObjects();

	for (auto* obj : objects)
	{
		if (obj->GetType() == type)
		{
			return obj; // �ŏ��Ɉ�v����I�u�W�F�N�g��Ԃ�
		}
	}

	return nullptr; // ������Ȃ������ꍇ
}