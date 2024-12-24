//======================================================
//
// ALTER_EGO [object.h]
// Auther : ��|�
//
//======================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include <assert.h>
#include <iostream>

// �S�I�u�W�F�N�g���N���X
class CObject
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_CLONE,
		TYPE_FIELD,
		TYPE_BULLET,
		TYPE_BLOCK,
		TYPE_ITEM,
		TYPE_BG,
		TYPE_TEXTURE,
		TYPE_MAX,
	}TYPE;
	CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static void ReleaseAll();									// �S�I�u�W�F�N�g���
	static void UpdateAll();									// �S�I�u�W�F�N�g�X�V
	static void DrawAll();										// �S�I�u�W�F�N�g�`��
	void SetType(TYPE type);									// �^�C�v�ݒ�
	TYPE GetType();												// �^�C�v�擾
	//CObject* GETObject(int nPrio, int nObj);
	CObject* GetTop(int nPrio);
	void SetNext(CObject* pObject);
	CObject* GetNext();
	virtual void SetDeath();
	void SetUseDeath(bool bUseDeath);
	static void DeleateProcess();
	static const int m_MAXPRIORITY = 10;

	using BlockPair = std::unordered_map<std::string, std::vector<CObject*>>;
	static BlockPair& GetPair() { return m_pair; }	// �y�A�̎擾
	void AddToPair(const std::string& key, CObject* object);
	void RemoveFromPair(const std::string& key, CObject* object);
	std::vector<CObject*>& GetPairObjects(const std::string& key);
	std::vector<CObject*> GetAllObjects();
	CObject* FindFirstOfType(TYPE type);

protected:
	void Release();												// �������g�̉��
private:
	//static CObject* m_apObject[m_MAXPRIORITY][m_MAXOBJECT];		// �I�u�W�F�N�g�Ǘ�
	static CObject* m_pTop[m_MAXPRIORITY];					// �擪�̃I�u�W�F�N�g�̃|�C���^
	static CObject* m_pCur[m_MAXPRIORITY];					// ����(�Ō��)�̃|�C���^
	CObject* m_pPrev;											// �O�̃I�u�W�F�N�g�̃|�C���^
	CObject* m_pNext;											// ���̃I�u�W�F�N�g�̃|�C���^
	static int m_nNumAll;										// �I�u�W�F�N�g����
	int m_nPriority;											// �`��D��x
	bool m_Death;												// ���S�t���O
	bool m_bUseDeath;
	TYPE m_Type;												// �^�C�v�ݒ�p

	static BlockPair m_pair;	// �n�b�V���}�b�v
};

#endif // !_OBJECT_H_