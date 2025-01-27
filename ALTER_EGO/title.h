//==============================================
//
// ALTER_EGO[title.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "scene.h"
#include "object3D.h"
#include "bg.h"
#include "player.h"
#include "camera.h"

class CTitle : public CScene
{
public:
	CTitle();							// �R���X�g���N�^
	~CTitle()override;					// �f�X�g���N�^
	HRESULT Init()override;				// �����ݒ�
	void Uninit()override;				// �I������
	void Update()override;				// �X�V����
	void Draw()override;				// �`�揈��
	static CCamera* GetCamera();
	static const int m_BLOCK_BESIDE = 30;
	static const int m_BLOCK_VERTICAL = 15;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	int m_nType[m_BLOCK_BESIDE][m_BLOCK_VERTICAL];
	CBg* m_pBg;
	static CPlayer* m_pPlayer;
	static CCamera* m_pCamera;
};

#pragma once
