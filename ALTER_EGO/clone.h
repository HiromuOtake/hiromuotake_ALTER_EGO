//==============================================
//
//ALTER_EGO[player.h]
//Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "objectX.h"
#include "modelparts.h"
#include "character.h"

class CClone : public CCharacter
{
public:
	typedef enum
	{
		PLAYER_NONE = 0,
		PLAYER_NORMAL,
		PLAYER_DEATH,
		PLAYER_MAX,
	}TYPE;
	CClone(int nPriority = 3);
	~CClone()override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	bool CollisionUPDOWN(bool& bIsLanding, CObject* pObj);	// �����蔻��㉺
	void CollisionLEFTRIGHT(CObject* pObj);					// �����蔻�荶�E
	static bool& GetGoal();									// �S�[�����̎擾
	static CClone* Create(D3DXVECTOR3 pos);				// �v���C���[�̐���
	static const int m_PLAYER_LIFE = 1;						// �v���C���[�̗̑�
	static const int m_DEATH_COUNT = 30;					// �v���C���[����������܂ł̎���
	static const int m_RESET_PLAYER_POS_X = 200;			// �v���C���[�𕜊�������ꏊ(X���W)
	static const int m_RESET_PLAYER_POS_Y = -1200;			// �v���C���[�𕜊�������ꏊ(Y���W)
	static constexpr float m_PLAYER_SHOT_POS = 20.0f;		// �v���C���[���e���o���ʒu�̕␳
	static constexpr float m_PLAYER_SHOT_MOVE = 15.0f;		// �v���C���[�̒e�̑��x
	static constexpr float m_PLAYER_ROTATION_SPEED = 0.15f;	// �v���C���[�̉�]�̑���
	static constexpr float m_PLAYER_JUMP = 22.5f;			// �v���C���[�̃W�����v��
	static constexpr float m_PLAYER_SPEED = 1.0f;			// �v���C���[�̃X�s�[�h
	static constexpr float m_LEFTRIGHT = 0.5f;
	void SetDeath()override;
private:
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_size;
	int m_nTextureIdx;
	bool m_bIsLanding;
	bool m_bJumping;
	bool m_bIsRight;
	static bool m_bGravity;
	static bool m_bGravityRotation;
	static bool m_bUse;
	static bool m_bhalfwaypoint;
	int m_JumpCnt;
	int m_nModelIdx;
	int m_nLife;
	int m_nType;
	int m_nDeathTimer;
	CInputKeyboard* m_Keyboard;
	CInputJoyPad* m_JoyPad;
	CModelParts* m_pModelParts[15];
};

#pragma once