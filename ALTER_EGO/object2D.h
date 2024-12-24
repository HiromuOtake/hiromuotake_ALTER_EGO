//======================================================
//
// ALTER_EGO [object2D.h]
// Auther : ��|�
//
//======================================================

#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"
#include <cassert>

class CObject2D : public CObject
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;	//���_���W
		float rhw;			//���W�ϊ��p�W��(1.0�ŌŒ�)
		D3DCOLOR col;		//���_�J���[
		D3DXVECTOR2 tex;	//�e�N�X�`�����W
	}VERTEX_2D;
	CObject2D(int nPriority = 1);
	~CObject2D()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetPos(D3DXVECTOR3 pos);
	void SetWidthHeight(float fWidth, float fHeight);
	void SetColor(float fColor);
	void SetTexture(float fTexture);
	D3DXVECTOR3& GetPos();
	D3DXVECTOR3* GetPosOld();
	D3DXVECTOR3* GetRot();
	LPDIRECT3DVERTEXBUFFER9 GetBuffer() { return m_pVtxBuff; }
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;						//���_���W
	D3DXVECTOR3 m_posold;					//���_���W
	D3DXVECTOR3 m_rot;						//����
	D3DXVECTOR3 m_move;						//�ړ�
	float m_fLengthPlayer;				//�Ίp���̒���
	float m_fAnglePlayer;				//�Ίp���̊p�x
	float m_fWidth;
	float m_fHeight;
	float m_colorFade;					// �F
	float m_fTexture;
};

#endif // !_OBJECT2D_H_
#pragma once
