//
// Created by stagakis on 9/12/20.
//

#ifndef VVR_OGL_LABORATORY_FOUNTAINEMITTER_H
#define VVR_OGL_LABORATORY_FOUNTAINEMITTER_H
#include <ParticleEmitterInt.h>

class FountainEmitter : public ParticleEmitterInt {
    public:
        FountainEmitter(Drawable* _model, int number);

        void initializeParticles();
        void createNewParticle(int index);
        void updateParticles(float time) override;
};


#endif //VVR_OGL_LABORATORY_FOUNTAINEMITTER_H
