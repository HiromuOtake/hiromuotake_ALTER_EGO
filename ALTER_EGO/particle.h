//==============================================
//
// ALTER_EGO[particle.h]
// Author: hiromu otake
//
//==============================================

#ifndef _BULLET_H_
#define _BULLET_H_

#include <d3dx9.h>
#include "manager.h"
#include "billboard.h"

class CParticle : public CBillboard
{
public:
	CParticle();
	~CParticle();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float size, float speed, D3DXCOLOR color);
	static HRESULT Load();
	static void Unload();
	void SetSize(float size) { m_size = size; }
	void SetSpeed(float speed) { m_speed = speed; }
	void SetColor(D3DXCOLOR color) { m_color = color; }
	D3DXVECTOR3* GetMove() { return &m_move; }
	void SetDeath()override;
	static const int m_MAXLIFE = 30;
	int m_nLife;							// �e�̎�������
private:
	static LPDIRECT3DTEXTURE9 m_pTextureTemp;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// ���_���W
	D3DXVECTOR3 m_rot;						// ����
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXMATRIX m_mtxWorld;
	D3DXCOLOR m_color;						// �p�[�e�B�N���̐F
	float m_size;							// �p�[�e�B�N���̑傫��
	float m_speed;							// �p�[�e�B�N���̑���
	bool m_bUse;							// �e���g���Ă邩���Ȃ���
};

#endif 