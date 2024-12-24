//======================================================
//
// ALTER_EGO [object3D.h]
// Auther : ��|�
//
//======================================================

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "object.h"

class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetVertexBuffer(LPDIRECT3DVERTEXBUFFER9 pVtxBuff);
	void SetPos(float x, float y, float z);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//���_���W
	D3DXVECTOR3 m_rot;						//����
	D3DXMATRIX m_mtxWorld;
};

#endif // !_OBJECT3D_H_
#pragma once
