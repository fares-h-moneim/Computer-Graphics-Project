#pragma once

#include "scp-movement.hpp"
#include "free-camera-controller.hpp"
#include "../ecs/entity.hpp"
#include "../components/movement.hpp"
#include "../components/collision.hpp"

#include <iostream>
namespace our
{
    float calcdistance(float x1, float x2, float y1, float y2)
    {
        return sqrt(pow(abs(x2 - x1), 2) + pow(abs(y2 - y1), 2));
    }

    void ScpMovement::update(World *world, ForwardRenderer *renderer)
    {
        for (Entity *entity : world->getEntities())
        {
            if (entity->name == "scp")
            {
                scp = entity;
            }
            if (entity->name == "player")
            {
                player = entity;
                camera = entity->getComponent<CameraComponent>();
            }
        }
        if (player && scp)
        {
            float distance = calcdistance(scp->localTransform.position.x, player->localTransform.position.x, scp->localTransform.position.z, player->localTransform.position.z);
            scpBoundingBox = scp->getComponent<CollisionComponent>();
            isSCPVisible();

            glm::vec3 directionFromScpToPlayer = player->localTransform.position - scp->localTransform.position;
            // glm::vec3 linearVelocity = glm::normalize(directionFromScpToPlayer) * 0.5f;
            glm::vec3 linearVelocity = directionFromScpToPlayer;
            scp->localTransform.rotation.y = atan2(linearVelocity.x, linearVelocity.z) + 3.14f;
            if (isInViewPort)
            {
                scp->getComponent<MovementComponent>()->linearVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
                renderer->setShake(false);
            }
            else
            {
                linearVelocity.y = 0.0f;
                scp->getComponent<MovementComponent>()->linearVelocity = linearVelocity * 0.7f;
                // set rotation of scp to face player
                renderer->setShake(true);
            }
        }
    }

    void ScpMovement::isSCPVisible()
    {
        glm::mat4 mvp = camera->getProjectionMatrix(windowSize) * camera->getViewMatrix() * scp->getLocalToWorldMatrix();
        glm::vec4 homo = mvp * glm::vec4(scp->localTransform.position, 1.0f);
        glm::vec4 ndc = homo / homo.w;

        if (abs(ndc.x) > 1 || abs(ndc.y) > 1 || abs(ndc.z) > 1)
        {
            isInViewPort = false;
        }
        else
        {
            isInViewPort = true;
        }
    }

    float ScpMovement::updateShakeIntensity(float distance)
    {
        float maxShakeIntensity = 0.07f; // da akbar rakam 7aseto over lw akbar
        float minShakeIntensity = 0.005f;
        // say lw distance = 2 yb2a max shake
        // lw akbar mn 20 min shake
        float shake = 0.07 + (0.005 - 0.7) * ((distance - 2) / 18); // linear interpolation
        if (shake >= 0)
            return shake;
        else
            return minShakeIntensity;
    }
}