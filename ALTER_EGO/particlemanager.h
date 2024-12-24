//======================================================
//
// ALTER_EGO [particlemanager.h]
// Auther : ��|�
//
//======================================================

#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

#include "particle.h"
#include <d3dx9.h>
#include <vector>

class CParticleManager
{
public:
    CParticleManager();
    ~CParticleManager();
    void Init();
    void Uninit();
    void Update();
    void Draw();
    void EmitParticles(D3DXVECTOR3 pos, int numParticles, float size, float speed, D3DXCOLOR color);
private:
    std::vector<CParticle*> m_particles;  // �p�[�e�B�N�����X�g
};

#endif  // _PARTICLE_MANAGER_H_