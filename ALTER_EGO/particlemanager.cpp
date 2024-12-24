//==============================================
//
// ALTER_EGO[particlemanager.cpp]
// Author: hiromu otake
//
//==============================================

#include "particlemanager.h"

//=====================================
// �R���X�g���N�^
//=====================================
CParticleManager::CParticleManager()
{

}

//=====================================
// �f�X�g���N�^
//=====================================
CParticleManager::~CParticleManager() 
{
    Uninit();
}

//==============================================
// �����ݒ�
//==============================================
void CParticleManager::Init()
{
    // �p�[�e�B�N���p�̃e�N�X�`�������[�h
    CParticle::Load();
}

//==============================================
// �I������
//==============================================
void CParticleManager::Uninit()
{
    for (CParticle* particle : m_particles)
    {
        if (particle)
        {
            delete particle;
        }
    }

    m_particles.clear();

    // �p�[�e�B�N���p�̃e�N�X�`�������
    CParticle::Unload();
}

//==============================================
// �X�V����
//==============================================
void CParticleManager::Update()
{
    for (auto it = m_particles.begin(); it != m_particles.end();) 
    {
        (*it)->Update();
        if ((*it)->GetMove()->x == 0.0f && (*it)->GetMove()->y == 0.0f || (*it)->m_nLife <= 0)
        {  // �����`�F�b�N��
            delete* it;
            it = m_particles.erase(it);
        }
        else 
        {
            ++it;
        }
    }
}

//==============================================
// �`�揈��
//==============================================
void CParticleManager::Draw()
{
    for (CParticle* particle : m_particles) 
    {
        particle->Draw();
    }
}

//=====================================================
// �p�[�e�B�N���̐����i�傫���A�����A�F���w��\�j
//=====================================================
void CParticleManager::EmitParticles(D3DXVECTOR3 pos, int numParticles, float size, float speed, D3DXCOLOR color)
{
    for (int i = 0; i < numParticles; ++i)
    {
        // �����_���Ȉړ���ݒ�
        D3DXVECTOR3 move;
        move.x = (rand() % 10 - 5) * speed * 0.1f;
        move.y = (rand() % 10) * speed * 0.1f;
        move.z = (rand() % 10 - 5) * speed * 0.1f;

        // �p�[�e�B�N������
        CParticle* particle = CParticle::Create(pos, move, size, speed, color);

        //if (particle && SUCCEEDED(particle->Init()))
        //{
        //    m_particles.push_back(particle);
        //}
        //else if (particle)
        //{
        //    delete particle;
        //}
    }
}