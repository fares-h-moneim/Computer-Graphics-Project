#pragma once

#include "../ecs/world.hpp"
#include "../application.hpp"
#include "../components/collision.hpp"
#include "../components/camera.hpp"
#include "../components/movement.hpp"
#include "../systems/forward-renderer.hpp"
#include "free-camera-controller.hpp"
#include "irrKlang.h"

using namespace irrklang;

namespace our
{
    class ScpMovement
    {
        Application *app;
        Entity *player;
        Entity *scp;
        CameraComponent *camera;
        CollisionComponent *scpBoundingBox;
        glm::ivec2 windowSize;
        bool isInViewPort = false;
        ISoundEngine *SoundEngine;

        bool firstMove = true;

    public:
        void setApp(Application *app)
        {
            this->app = app;
            windowSize = app->getWindowSize();
            SoundEngine = app->getSoundEngine();
        }
        void update(World *world, ForwardRenderer *renderer);
        void isSCPVisible();
        float updateShakeIntensity(float distance);
        void reset();
    };
}