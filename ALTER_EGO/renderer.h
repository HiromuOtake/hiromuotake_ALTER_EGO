//======================================================
//
// ALTER_EGO [renderer.h]
// Auther : ��|�
//
//======================================================

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <Windows.h>
#include "d3dx9.h"

class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();
	void DrawCircle(const D3DXVECTOR3& position, float radius, D3DCOLOR color);
	void DrawFPS(int nCntFPS);
	LPDIRECT3DDEVICE9 GetDevice();			// 3D�f�o�C�X�̎擾
	LPD3DXFONT GetFont();
private:
	LPDIRECT3D9 m_pD3D;						// Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;			// Direct3D�f�o�C�X
	LPD3DXFONT m_pFont;
	int m_nCntFont;
};

#endif // !_RENDERER_H_
#pragma once
