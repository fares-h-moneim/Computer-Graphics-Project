#pragma once

#include "pickUpKey.hpp"
#include "free-camera-controller.hpp"
#include "../ecs/entity.hpp"
#include "../components/movement.hpp"

#include <iostream>

namespace our
{
    // This should be called every frame to apply the game logic.
    void PickSystem::update(World *world)
    {
        for (Entity *entity : world->getEntities())
        {
            if (entity->name == "key")
            {
                key = entity;
            }
            if (entity->name == "player")
            {
                player = entity;
            }
        }

        if (player && key)
        {
            printf("player position: %f, %f, %f\n", player->localTransform.position.x, player->localTransform.position.y, player->localTransform.position.z);
            // printf("key position: %f, %f, %f\n", key->localTransform.position.x, key->localTransform.position.y, key->localTransform.position.z);
            // printf("distance: %f\n", glm::distance(player->localTransform.position, key->localTransform.position));
            if (glm::distance(player->localTransform.position, key->localTransform.position) < 1.45f)
            {
                if (app->getKeyboard().isPressed(GLFW_KEY_X))
                    pickUp();
            }
        }
    }

    void PickSystem::pickUp() // TODO: we can find a better way for searching an entity here
    {
        // TODO: fix key position
        key->parent = player;
        key->localTransform.position = glm::vec3(-0.5f, -0.2f, -0.3f);
        key->localTransform.rotation = glm::vec3(-90.0f, 45.0f, 0.0f);
        key->localTransform.scale = glm::vec3(50.0f, 50.0f, 50.0f);
    }
}
