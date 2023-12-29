#pragma once

#include "pickUpKey.hpp"
#include "free-camera-controller.hpp"
#include "../ecs/entity.hpp"
#include "../components/movement.hpp"
#include "../components/key.hpp"

#include <iostream>

namespace our
{
    // This should be called every frame to apply the game logic.
    void PickSystem::initialize(World *world)
    {
        for (Entity *entity : world->getEntities())
        {
            if (entity->name == "key")
            {
                keys.push_back(entity);
            }
            if (entity->name == "player")
            {
                player = entity;
            }
        }
    }

    void PickSystem::update(World *world)
    {

        for (auto key : keys) // Iterate through all keys
        {
            if (player && key)
            {
                printf("player position: %f, %f, %f\n", player->localTransform.position.x, player->localTransform.position.y, player->localTransform.position.z);
                if (glm::distance(player->localTransform.position, key->localTransform.position) < 1.15f)
                {
                    if (app->getKeyboard().isPressed(GLFW_KEY_X) && !heldKey)
                        pickUp(key); // picking up if no key is held
                }
            }
        }

        if (app->getKeyboard().isPressed(GLFW_KEY_Y) && heldKey)
        {
            putDown(heldKey);
        }
    }

    void PickSystem::pickUp(Entity *key) // TODO: we can find a better way for searching an entity here
    {
        if (!heldKey)
        {
            originalTransforms[key] = {key->localTransform.position, key->localTransform.rotation, key->localTransform.scale};
        }
        heldKey = key;
        key->getComponent<KeyComponent>()->isPickedUp = true;
        key->parent = player;
        key->localTransform.position = glm::vec3(-0.9f, -0.4f, -0.65f);
        key->localTransform.rotation = glm::vec3(-20.0f, 45.0f, 0.0f);
        key->localTransform.scale = glm::vec3(50.0f, 50.0f, 50.0f);
    }

    void PickSystem::putDown(Entity *key)
    {
        if (key)
        {
            if (heldKey == key)
            {
                OriginalTransform &orig = originalTransforms[key];
                key->localTransform.position = orig.position;
                key->localTransform.rotation = orig.rotation;
                key->localTransform.scale = orig.scale;
                key->getComponent<KeyComponent>()->isPickedUp = false;

                key->parent = nullptr; // Detach from the player
                heldKey = nullptr;     // No longer holding a key
            }
        }
    }

}
