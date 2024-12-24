//==============================================
//
// ALTER_EGO[block.h]
// Author: hiromu otake
//
//==============================================

#include "manager.h"
#include "objectX.h"
#include "player.h"
#include "clone.h"
#include <iostream>

// �}�N����`
#define BLOCK_WIDTH			(100.0f)
#define BLOCK_HEIGHT		(100.0f)

class CBlock : public CObjectX
{
public:
	// �{�^���̏��
	enum class ButtonState
	{
		RED_ENABLED,
		BLUE_ENABLED
	};
	typedef enum
	{
		BLOCK_NONE = 0,
		BLOCK_NORMAL,
		BLOCK_NEEDLE,
		BLOCK_DOOR,
		BLOCK_BUTTON,
		BLOCK_GOAL,
		BLOCK_MAX
	}BLOCK;
	CBlock(int nPriority = 3);
	~CBlock();
	HRESULT Init() override;
	void Uninit() override;
	virtual void Update() override;
	void SetBlockType(BLOCK BlockType);
	void SetPairKey(const char* pairKey) { m_pairKey = pairKey; }
	BLOCK GetBlockType();
	const std::string& GetPairKey() const { return m_pairKey; }
	static CBlock* Create(D3DXVECTOR3 pos, BLOCK nType);
	void Draw()override;
	void PressRedButton();
	void PressBlueButton();
	ButtonState GetCurrentState() const { return currentButtonState; }
	void SetDeath()override;
	BLOCK m_BlockType;
private:
	ButtonState currentButtonState = ButtonState::RED_ENABLED;
	int m_nModelIdx;
	int m_nTexIdx;
	int m_nTimer;
	bool m_bOpen;
	D3DXVECTOR3 m_move;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;   //���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_matWorld;
	CInputKeyboard* m_Keyboard;
	std::string m_pairKey;	// �y�A�̃L�[
};

class CBlockNeedle : public CBlock
{
public:
	CBlockNeedle(int nPriority = 3);
	~CBlockNeedle();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlockNeedle* Create(D3DXVECTOR3 pos, BLOCK nType);
	void SetDeath()override;
private:
	int m_nModelIdx;
	int m_nTexIdx;
};

class CBlockButton : public CBlock
{
public:
	enum BUTTON_COLOR
	{
		BUTTON_NORMAL,
		BUTTON_RED,
		BUTTON_BLUE,
	};
	CBlockButton(int nPriority = 3);
	~CBlockButton();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlockButton* Create(D3DXVECTOR3 pos, BLOCK nType, BUTTON_COLOR color = BUTTON_NORMAL);
	void SetColor(BUTTON_COLOR color) { m_Color = color; }
	BUTTON_COLOR GetColor() const { return m_Color; }	// �{�^���̐F���擾
	void SetDeath()override;
	void OnPressed();
	bool& GetOpenDoor(); // �����J����Ԃ��擾
	static BUTTON_COLOR m_LastPressedButton;
private:
	int m_nModelIdx;
	int m_nTexIdx;
	bool m_bOpen;
	bool m_bColliderActive;		// �����蔻�肪�L�����ǂ���
	bool m_bResetPending;  // �{�^�������Z�b�g��҂��Ă����Ԃ��ǂ���
	bool m_bPressedOnce;
	BUTTON_COLOR m_Color;  // �X�C�b�`�̐F
	bool IsCollisionPlayer(CPlayer* player);
	bool IsCollisionClone(CClone* clone);
	void SetMatColor(D3DMATERIAL9* pMat, int nMatIdx) override;
};

// �Ԃ��{�^��
class CBlockRedButton : public CBlockButton
{
public:
	CBlockRedButton(int nPriority = 3);
	~CBlockRedButton();
	HRESULT Init()override;
	static CBlockRedButton* Create(D3DXVECTOR3 pos, BUTTON_COLOR color);
private:
	int m_nModelIdx;
	int m_nTexIdx;
	bool m_bOpen;
	bool m_bColliderActive;		// �����蔻�肪�L�����ǂ���
	BUTTON_COLOR m_Color;			// �X�C�b�`�̐F
};

// ���{�^��
class CBlockBlueButton : public CBlockButton
{
public:
	CBlockBlueButton(int nPriority = 3);
	~CBlockBlueButton();
	HRESULT Init()override;
	static CBlockBlueButton* Create(D3DXVECTOR3 pos, BUTTON_COLOR color);
private:
	int m_nModelIdx;
	int m_nTexIdx;
	bool m_bOpen;
	bool m_bColliderActive;		// �����蔻�肪�L�����ǂ���
	BUTTON_COLOR m_Color;			// �X�C�b�`�̐F
};

class CBlockDoor :public CBlock
{
public:
	enum DOOR_COLOR
	{
		DOOR_NORMAL,
		DOOR_RED,
		DOOR_BLUE,
	};
	CBlockDoor(int nPriority = 3, DOOR_COLOR color = DOOR_NORMAL);
	~CBlockDoor();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlockDoor* Create(D3DXVECTOR3 pos, BLOCK nType, DOOR_COLOR color);
	void SetColor(DOOR_COLOR color) { m_Color = color; }
	DOOR_COLOR GetColor() const { return m_Color; }
	bool IsOpen() const { return m_bOpen; }
	void OpenAndClose(bool open);			// �����J���鏈��
	void Open();
	void SetDeath()override;
private:
	int m_nModelIdx;
	int m_nTexIdx;
	int m_Timer;
	float m_deleteDoor;
	bool m_isOpen = false; // �h�A�̏�Ԃ�ێ�
	bool m_bOpen;				// �����J���Ă��邩�̏��
	bool m_bColliderActive;		// �����蔻�肪�L�����ǂ���
	bool m_bVisible;  // ���̕\���E��\���𐧌䂷��t���O
	DOOR_COLOR m_Color;			// �h�A�̐F
	CInputKeyboard* m_Keyboard;
	CPlayer* m_pPlayer;
};

// �Ԃ��h�A
class CBlockRedDoor : public CBlockDoor
{
public:
	CBlockRedDoor(int nPriority = 3);
	~CBlockRedDoor();
	HRESULT Init()override;
	static CBlockRedDoor* Create(D3DXVECTOR3 pos, DOOR_COLOR color);
private:
	int m_nModelIdx;
	int m_nTexIdx;
	bool m_bOpen;
	bool m_bColliderActive;
	DOOR_COLOR m_color;			// �h�A�̐F
};

// ���h�A
class CBlockBlueDoor : public CBlockDoor
{
public:
	CBlockBlueDoor(int nPriority = 3);
	~CBlockBlueDoor();
	HRESULT Init()override;
	static CBlockBlueDoor* Create(D3DXVECTOR3 pos, DOOR_COLOR color);
private:
	int m_nModelIdx;
	int m_nTexIdx;
	bool m_bOpen;		
	bool m_bColliderActive;

	DOOR_COLOR m_color;			// �h�A�̐F
};

class CBlockGoal : public CBlock
{
public:
	CBlockGoal(int nPriority = 0);
	~CBlockGoal();
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static CBlockGoal* Create(D3DXVECTOR3 pos, BLOCK nType);
	void SetDeath()override;
private:
	float m_fGoalRot;
	int m_nModelIdx;
	int m_nTexIdx;
};

#pragma once
