//==============================================
//
// ALTER_EGO[result.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "scene.h"
#include "number.h"

class CResult : public CScene
{
public:
	CResult();							// �R���X�g���N�^
	~CResult()override;					// �f�X�g���N�^
	HRESULT Init()override;				// �����ݒ�
	void Uninit()override;				// �I������
	void Update()override;				// �X�V����
	void Draw()override;				// �`�揈��
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	CNumber* m_pNumber;
};

#pragma once
