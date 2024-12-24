//==============================================
//
//ALTER_EGO[modelparts.h]
//Author: hiromu otake
//
//==============================================

#include "objectX.h"

class CModelParts
{
public:
//==============================================
//���f���̍\����
//==============================================
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		int nIdx;
		int nIdxModelParent;    // �e�̃C���f�b�N�X
	}Parts;

	static const int m_MAXTEXTURE = 126;

	typedef struct
	{
		LPD3DXBUFFER m_pBuffMat;		// �}�e���A���ւ̃|�C���^
		DWORD m_dwNumMat;				// �}�e���A���̐�
		LPD3DXMESH m_pMesh;				// ���b�V���ւ̃|�C���^
		bool m_bUse;
	}ModelInfo;

	CModelParts();
	~CModelParts();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	static CModelParts* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char* aModel);
	void SetParent(CModelParts* pModelParts);
	void BindModel(LPD3DXBUFFER BuffMat, DWORD dwNumMat, LPD3DXMESH Mesh);
	int Regist(const char* pTextureName);		// ���f���o�^
	D3DXMATRIX GetWoarldMatrix();
	D3DXVECTOR3& GetPos();
	D3DXVECTOR3& GetSize();
	D3DXVECTOR3& GetMin();
	D3DXVECTOR3& GetMax();
	D3DXMATRIX& GetMatrix();
	int& GetIdx();
	static const int m_MAXMODEL = 126;
	static const int m_MAXSENTENCE = 126;
	static const int m_MAX_LETTER = 496;
	static const int m_NUM_MODEL_PARTS = 15;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nIdx;
	int m_nIdxParents;
private:
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_size;
	int m_nNumVtx;			// ���_��
	DWORD m_sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH m_pMesh;					// ���b�V���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;
	CModelParts* m_pParent;
	ModelInfo m_pModelList[m_MAXMODEL];
	char m_pModelName[m_MAXMODEL][m_MAXSENTENCE];
	int m_nModelIdx;
	int m_nNumAll;
};

#pragma once