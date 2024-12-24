//==============================================
//
// ALTER_EGO[billboard.h]
// Author: hiromu otake
//
//==============================================

#include "main.h"
#include "object.h"

#ifndef  _BILLBOARD_H_          //���̃}�N����`������Ă��Ȃ�������
#define  _BILLBOARD_H_          //�Q�d�C���N���[�h�h�~�̃}�N����`

class CBillboard : public CObject
{
public:
	CBillboard(int nPriority = 4);
	~CBillboard();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3& GetPos();
	D3DXVECTOR3& GetPosOld();
	D3DXVECTOR3& GetRot();
	D3DXVECTOR3& GetSize();
	D3DXVECTOR3& GetMin();
	D3DXVECTOR3& GetMax();
	void SetDeath()override;
	static constexpr float m_BILLBOARD_SIZE = 20.0f;
private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   //���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posold;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_size;
	D3DXMATRIX m_mtxWorld;
	int m_nNumVtx;						// ���_��
	DWORD m_sizeFVF;					// ���_�t�H�[�}�b�g�̃T�C�Y
	LPD3DXMESH m_pMesh;					// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;			// �}�e���A���ւ̃|�C���^
};

#endif 