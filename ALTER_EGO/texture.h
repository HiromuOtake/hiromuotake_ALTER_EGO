//==============================================
//
// ALTER_EGO[texture.h]
// Author: hiromu otake
//
//==============================================

#include "main.h"

class CTexture
{
public:
	CTexture();
	~CTexture();
	void Unload();								// �e�N�X�`���j��
	int Regist(const char* pTextureName);		// �e�N�X�`���o�^
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);	// �e�N�X�`���擾
	static const int m_MAXTEXTURE = 126;
	static const int m_MAXSENTENCE = 126;
private:
	LPDIRECT3DTEXTURE9 m_pTextureList[m_MAXTEXTURE];
	char m_pTextureName[m_MAXTEXTURE][m_MAXSENTENCE];
	int m_nNumAll;
	static LPD3DXBUFFER m_pBuffMat;		// �}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;			// �}�e���A���̐�
};

#pragma once

