#pragma once

#include "door-system.hpp"
#include "free-camera-controller.hpp"
#include "../ecs/entity.hpp"
#include "../components/movement.hpp"

#include <iostream>

namespace our
{
    // This should be called every frame to apply the game logic.
    void DoorSystem::update(World *world)
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
            if (entity->name == "door1")
            {
                door = entity;
            }
        }

        if (player && key)
        {
            if (key->parent == player)
            {
                if (glm::distance(player->localTransform.position, door->localTransform.position) < 2.0f)
                {
                    if (app->getKeyboard().isPressed(GLFW_KEY_X))
                    {
                        openDoor();
                    }
                }
            }
        }
    }

    void DoorSystem::openDoor() // TODO: we can find a better way for searching an entity here
    {
        // TODO: fix key position
        door->localTransform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    }
}
