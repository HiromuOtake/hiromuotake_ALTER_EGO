//==============================================
//
// ALTER_EGO[bg.cpp]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "scene.h"
#include "object2D.h"
#include <d3dx9.h>

// 頂点フォーマット
struct VTX_2D
{
	D3DXVECTOR3 pos;    // 座標
	D3DXCOLOR col;		// 色
	D3DXVECTOR2 tex;    // テクスチャ座標
};

#define FVF_VTX_2D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

class CBg : public CObject2D
{
public:
	CBg(int nPriority = 0);
	~CBg();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBg* Create(CScene::MODE mode);
	void SetDeath()override;
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャ
	D3DXMATRIX m_mtxWorld;
	int m_nTexIdx;
	float m_texScrollSpeed01;
	float m_texScrollSpeed02;
};

#pragma once
