#pragma once

#include "door-system.hpp"
#include "free-camera-controller.hpp"
#include "../ecs/entity.hpp"
#include "../components/movement.hpp"
#include "../components/key.hpp"

#include <iostream>

namespace our
{
    // This should be called every frame to apply the game logic.
    void DoorSystem::update(World *world, double deltaTime)
    {
        for (Entity *entity : world->getEntities())
        {
            if (entity->name == "key" && entity->getComponent<KeyComponent>()->isPickedUp == true)
            {
                key = entity;
                if (entity->getComponent<KeyComponent>()->keyCanOpenDoor == true)
                {
                    keyCanOpenDoor = true;
                }
                else
                {
                    keyCanOpenDoor = false;
                }
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
            if (entity->name == "door_collider")
            {
                doorCollider = entity;
            }
        }

        if (player && key && keyCanOpenDoor)
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
            removeCollider();
            if (player->localTransform.position.z > 20.4)
            {
                app->changeState("win");
            }
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

    void DoorSystem::removeCollider()
    {
        if (doorCollider->getComponent<CollisionComponent>() != nullptr)
            doorCollider->deleteComponent<CollisionComponent>();
    }

    void DoorSystem::reset()
    {
        keyCanOpenDoor = false;
        open = false;
        openValue = 2;

        door1->localTransform.position.x = 0.75;
        door2->localTransform.position.x = 0.4;
    }
}
