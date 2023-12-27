#pragma once

#include "door-system.hpp"
#include "free-camera-controller.hpp"
#include "../ecs/entity.hpp"
#include "../components/movement.hpp"

#include <iostream>

namespace our
{
    // This should be called every frame to apply the game logic.
    void DoorSystem::update(World *world, double deltaTime)
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
                door1 = entity;
            }
            if (entity->name == "door2")
            {
                door2 = entity;
            }
        }

        if (player && key)
        {
            if (key->parent == player)
            {
                if (glm::distance(player->localTransform.position, door1->localTransform.position) < 2.0f)
                {
                    if (app->getKeyboard().isPressed(GLFW_KEY_X))
                    {
                        open = true;
                    }
                }
            }
        }
        if (open)
        {
            openDoor(deltaTime, door1, 2.5);
            openDoor(deltaTime, door2, -1.5);
        }
    }

    void DoorSystem::openDoor(double deltaTime, Entity *door, float targetX)
    {
        float doorSpeed = 1.0f; // Adjust the speed as needed
        float x = targetX;
        float currentX = door->localTransform.position.x;

        if (currentX < x && door->name == "door1")
        {
            float newX = currentX + doorSpeed * deltaTime;
            door->localTransform.position.x = std::min(newX, x);
        }
        else if (currentX > x && door->name == "door2")
        {
            float newX = currentX - doorSpeed * deltaTime;
            door->localTransform.position.x = std::max(newX, x);
        }
    }
}
