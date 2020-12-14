//
// Created by stagakis on 9/12/20.
//

#ifndef VVR_OGL_LABORATORY_FOUNTAINEMITTER_H
#define VVR_OGL_LABORATORY_FOUNTAINEMITTER_H
#include <ParticleEmitterInt.h>

class FountainEmitter : public ParticleEmitterInt {
    public:
        FountainEmitter(Drawable* _model, int number);

        int active_particles = 0; //number of particles that have been instantiated
        void createNewParticle(int index);
        void updateParticles(float time, float dt) override;
};


#endif //VVR_OGL_LABORATORY_FOUNTAINEMITTER_H
