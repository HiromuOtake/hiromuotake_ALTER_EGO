//==============================================
//
// ALTER_EGO[model.h]
// Author: hiromu otake
//
//==============================================

#include "main.h"

class CModel
{
public:
	static const int m_MAXTEXTURE = 126;
	typedef struct
	{
		LPD3DXBUFFER m_pBuffMat;		// �}�e���A���ւ̃|�C���^
		DWORD m_dwNumMat;				// �}�e���A���̐�
		LPD3DXMESH m_pMesh;				// ���b�V���ւ̃|�C���^
	}ModelInfo;
	CModel();
	~CModel();
	void Unload();								// ���f���j��
	int Regist(const char* pTextureName);		// ���f���o�^
	LPD3DXBUFFER GetBuffMat(int nIdx);
	DWORD GetNumMat(int nIdx);
	LPD3DXMESH GetMesh(int nIdx);
	static const int m_MAXMODEL = 126;
	static const int m_MAXSENTENCE = 126;
private:
	ModelInfo m_pModelList[m_MAXMODEL];
	char m_pModelName[m_MAXMODEL][m_MAXSENTENCE];
	int m_nNumAll;
};

#pragma once

