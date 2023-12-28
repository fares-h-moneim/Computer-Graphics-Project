#pragma once

#include "scp-movement.hpp"
#include "free-camera-controller.hpp"
#include "../ecs/entity.hpp"
#include "../components/movement.hpp"
#include "../components/collision.hpp"

#include <iostream>

namespace our
{
    void ScpMovement::update(World *world, double deltaTime)
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
            scpBoundingBox = scp->getComponent<CollisionComponent>();
            isSCPVisible();
            if (isInViewPort)
            {
                printf("scp in viewport\n");
                scp->getComponent<MovementComponent>()->linearVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
            }
            else
            {
                printf("scp not in viewport\n");
                glm::vec3 directionFromScpToPlayer = player->localTransform.position - scp->localTransform.position;
                scp->getComponent<MovementComponent>()->linearVelocity = glm::normalize(directionFromScpToPlayer) * 1.5f;
                glm::vec3 linearVelocity = scp->getComponent<MovementComponent>()->linearVelocity;
                linearVelocity.y = 0.0f;
                scp->localTransform.position += linearVelocity * static_cast<float>(deltaTime);
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
}