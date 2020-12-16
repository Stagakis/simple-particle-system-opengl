//
// Created by stagakis on 15/12/20.
//

#ifndef VVR_OGL_LABORATORY_ORBITEMITTER_H
#define VVR_OGL_LABORATORY_ORBITEMITTER_H

#include "IntParticleEmitter.h"

class OrbitEmitter : public IntParticleEmitter {
public:

    std::vector<float> particle_radius; //a specific radius value for each particle. It is generated in the constructor
    void updateParticles(float time, float dt, glm::vec3 camera_pos = glm::vec3(0, 0, 0)) override;
    void createNewParticle(int index) override;

    OrbitEmitter(Drawable* _model, int number, float _radius_min, float _radius_max);
    float radius_min, radius_max;
};


#endif //VVR_OGL_LABORATORY_ORBITEMITTER_H
