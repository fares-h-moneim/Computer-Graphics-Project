#pragma once

#include "scp-movement.hpp"
#include "free-camera-controller.hpp"
#include "../ecs/entity.hpp"
#include "../components/movement.hpp"
#include "../components/collision.hpp"

#include <iostream>

namespace our
{
    void ScpMovement::update(World *world)
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
            }
            else
            {
                printf("scp not in viewport\n");
            }
        }
    }

    void ScpMovement::isSCPVisible()
    {
        glm::mat4 mvp = camera->getProjectionMatrix(windowSize) * camera->getViewMatrix() * scp->getLocalToWorldMatrix();
        glm::vec3 halfSize = scpBoundingBox->size * 0.5f;
        glm::vec4 scpMaxPoint = glm::vec4(halfSize + scpBoundingBox->center, 1.0f);
        glm::vec4 scpMinPoint = glm::vec4(scpBoundingBox->center - halfSize, 1.0f);

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