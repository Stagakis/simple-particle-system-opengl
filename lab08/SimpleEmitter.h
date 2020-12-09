//
// Created by stagakis on 9/12/20.
//

#ifndef VVR_OGL_LABORATORY_SIMPLEEMITTER_H
#define VVR_OGL_LABORATORY_SIMPLEEMITTER_H

#include "ParticleEmitterInt.h"
class SimpleEmitter : public ParticleEmitterInt {

public:
    SimpleEmitter(Drawable* _model, int number);
    void updateParticles(float time, float dt) override;

};


#endif //VVR_OGL_LABORATORY_SIMPLEEMITTER_H
