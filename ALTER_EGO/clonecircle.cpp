//==============================================
//
//ALTER_EGO[clonecircle.h]
//Author: hiromu otake
//
//==============================================

#include "CloneCircle.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include <d3dx9.h>

//==============================================
// �R���X�g���N�^
//==============================================
CCloneCircle::CCloneCircle(int nPriority): CObject3D(nPriority), m_pos{ 0.0f, 0.0f, 0.0f }, m_nSelectedIndex(0),m_nCircleTexture(0), m_nNormalTexture(0), m_nSelectTexture(0)
, m_pVtxBuff(nullptr), m_Keyboard(nullptr), m_bUseDeath(false)
{

}

//==============================================
// �f�X�g���N�^
//==============================================
CCloneCircle::~CCloneCircle() 
{

}

//==============================================
// ����������
//==============================================
HRESULT CCloneCircle::Init()
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();

    // ���_�o�b�t�@�̐���
    pDevice->CreateVertexBuffer(sizeof(CUSTOMVERTEX) * 4,
        D3DUSAGE_WRITEONLY,
        D3DFVF_CUSTOMVERTEX,
        D3DPOOL_MANAGED, 
        &m_pVtxBuff,
        NULL);

    // �e�N�X�`���̓ǂݍ���
    m_nCircleTexture = CManager::GetTexture()->Regist("data\\Texture\\clonecircle.png");
    m_nNormalTexture = CManager::GetTexture()->Regist("data\\Texture\\silhouette000.png");
    m_nSelectTexture = CManager::GetTexture()->Regist("data\\Texture\\silhouette001.png");

    if (m_nCircleTexture == -1 || m_nNormalTexture == -1 || m_nSelectTexture == -1)
    {
        return E_FAIL;
    }

    CUSTOMVERTEX* vertices;

    m_pVtxBuff->Lock(0, 0, (void**)&vertices, 0);

    vertices[0] = { D3DXVECTOR3(-75.0f,  75.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f) };
    vertices[1] = { D3DXVECTOR3(75.0f,  75.0f, 0.0f), D3DXVECTOR2(1.0f, 0.0f) };
    vertices[2] = { D3DXVECTOR3(-75.0f, -75.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f) };
    vertices[3] = { D3DXVECTOR3(75.0f, -75.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f) };

    m_pVtxBuff->Unlock();

    return S_OK;
}

//==============================================
// �I������
//==============================================
void CCloneCircle::Uninit()
{
    if (m_pVtxBuff)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = nullptr;
    }

    CObject3D::Uninit();
}

//==============================================
// �X�V����
//==============================================
void CCloneCircle::Update()
{
    CPlayer* pPlayer = dynamic_cast<CPlayer*>(CGame::GetPlayer());
    if (pPlayer)
    {
        m_pos = pPlayer->GetPos();
    }
}

//==============================================
// �`�揈��
//==============================================
void CCloneCircle::Draw()
{
    if (m_bUseDeath)
    {
        return; // ����������Ă���Ε`�悵�Ȃ�
    }

    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();

    // Z�o�b�t�@���ꎞ�I�ɖ�����
    pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
    pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

    if (CManager::IsPaused())
    {
        // �~�`��
        LPDIRECT3DTEXTURE9 pCircleTex = CManager::GetTexture()->GetAddress(m_nCircleTexture);
        if (pCircleTex)
        {
            DrawTexture(pCircleTex, m_pos, D3DXVECTOR2(3.5f, 3.5f));
        }

        // �N���[�����`��
        const float radius = 250.0f;
        D3DXVECTOR3 positions[4] =
        {
            { m_pos.x, m_pos.y + radius, m_pos.z },  // ��
            { m_pos.x, m_pos.y - radius, m_pos.z },  // ��
            { m_pos.x + radius, m_pos.y, m_pos.z },  // �E
            { m_pos.x - radius, m_pos.y, m_pos.z }   // ��
        };

        // �N���[���`��
        for (int i = 0; i < 4; i++)
        {
            int textureID = (i == m_nSelectedIndex) ? m_nSelectTexture : m_nNormalTexture;
            LPDIRECT3DTEXTURE9 pTexture = CManager::GetTexture()->GetAddress(textureID);
            if (pTexture)
            {
                DrawTexture(pTexture, positions[i], D3DXVECTOR2(0.3f, 0.5f));
            }
        }
    }
    // Z�o�b�t�@�����ɖ߂�
    pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
    pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

//==============================================
// �N���[���T�[�N���̐���
//==============================================
CCloneCircle* CCloneCircle::Create(D3DXVECTOR3 pos)
{
    CCloneCircle* pCircle = new CCloneCircle();
    if (pCircle != nullptr)
    {
        pCircle->Init();
        pCircle->SetPlayerPos(pos);
        pCircle->SetUseDeath(true);
    }
    return pCircle;
}

//==============================================
// �e�N�X�`���`��
//==============================================
void CCloneCircle::DrawTexture(LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR3 position, D3DXVECTOR2 scale)
{
    LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderere()->GetDevice();

    //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CUSTOMVERTEX));
    // ���_�t�H�[�}�b�g��ݒ�
    pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

    // ���݂̃��C�e�B���O��Ԃ�ۑ�
    DWORD  lightingEnabled;
    pDevice->GetRenderState(D3DRS_LIGHTING, &lightingEnabled);

    // ���C�e�B���O�𖳌��ɂ���
    pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

    // ���[���h�s���ݒ�
    D3DXMATRIX matWorld, matScale, matTrans;
    D3DXMatrixScaling(&matScale, scale.x, scale.y, 1.0f);
    D3DXMatrixTranslation(&matTrans, position.x, position.y, position.z);
    matWorld = matScale * matTrans;
    pDevice->SetTransform(D3DTS_WORLD, &matWorld);

    // �e�N�X�`���̐ݒ�ƕ`��
    pDevice->SetTexture(0, pTexture);

    //�|���S���̕`��
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    // ���C�e�B���O�̏�Ԃ����ɖ߂�
    pDevice->SetRenderState(D3DRS_LIGHTING, lightingEnabled);
}

//==============================================
// �N���[���o���ʒu�I��
//==============================================
D3DXVECTOR3 CCloneCircle::GetSelectedPosition()
{
    const float radius = 250.0f;
    switch (m_nSelectedIndex)
    {
    case 0: return { m_pos.x, m_pos.y + radius, m_pos.z };  // ��
    case 1: return { m_pos.x, m_pos.y - radius, m_pos.z };  // ��
    case 2: return { m_pos.x + radius, m_pos.y, m_pos.z };  // �E
    case 3: return { m_pos.x - radius, m_pos.y, m_pos.z };  // ��
    default: return m_pos;
    }
}

//==============================================
// �v���C���[�ʒu�ݒ�
//==============================================
void CCloneCircle::SetPlayerPos(D3DXVECTOR3 pos) 
{
    m_pos = pos;
}

//==============================================
// �I���ʒu�ݒ�
//==============================================
void CCloneCircle::SetSelectedIndex(int index)
{
    m_nSelectedIndex = index;
}

//==============================================
// �`����ėL����
//==============================================
void CCloneCircle::Activate()
{
    m_bUseDeath = false; 
}

//=========================================
// ���S�t���O�ݒ菈��
//=========================================
void CCloneCircle::SetDeath()
{
    // �N���[���T�[�N���̕`��𖳌���
    m_bUseDeath = true; // �t���O�ŕ`����~

    CObject::SetDeath();
}