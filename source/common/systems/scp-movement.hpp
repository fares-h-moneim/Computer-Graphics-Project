#pragma once

#include "../ecs/world.hpp"
#include "../application.hpp"
#include "../components/collision.hpp"
#include "../components/camera.hpp"
#include "../components/movement.hpp"
#include "free-camera-controller.hpp"

namespace our{
    class ScpMovement{
        Application *app;
        Entity *player;
        Entity *scp;
        CameraComponent *camera;
        CollisionComponent *scpBoundingBox;
        glm::ivec2 windowSize;
        bool isInViewPort = false;

    public:
        void setApp(Application *app){
            this->app = app;
            windowSize = app->getWindowSize();
        }
        void update(World *world);
        void isScpInteresctingWithFrustum();
        void extractPlanes(const glm::mat4& MVP);
        struct Plane {
            glm::vec3 normal;
            float distance;
        };
        Plane planes[6];
        bool isBoxOutsidePlane(const glm::vec4& scpMinPoint, const glm::vec4& scpMaxPoint, const Plane& plane) const;
    };
}