//==============================================
//
// ALTER_EGO[game.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "scene.h"
#include "player.h"
#include "camera.h"
#include "item.h"
//#include <unordered_map>
//#include "block.h"

class CGame : public CScene
{
public:
	// ��ʂ̎��
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	}MODE;
	CGame();							// �R���X�g���N�^
	~CGame()override;					// �f�X�g���N�^
	HRESULT Init()override;				// �����ݒ�
	void Uninit()override;				// �I������
	void Update()override;				// �X�V����
	void Draw()override;				// �`�揈��
	void CreateObject(int type, const std::string& key, D3DXVECTOR3 position, float rotation);
	static CPlayer* GetPlayer();
	static CCamera* GetCamera();
	static const int m_BLOCK_BESIDE = 30;
	static const int m_BLOCK_VERTICAL = 15;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	static CPlayer* m_pPlayer;
	//static CItem* m_pItem;
	static CCamera* m_pCamera;
	int m_nType[m_BLOCK_BESIDE][m_BLOCK_VERTICAL];
	//std::unordered_map<std::string, CBlock*> m_pairList;
};

#pragma once
