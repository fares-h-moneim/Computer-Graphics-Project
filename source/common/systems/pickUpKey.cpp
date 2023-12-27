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
            if (entity->name == "hand")
            {
                hand = entity;
            }
            if (entity->name == "moon")
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
            printf("key position: %f, %f, %f\n", key->localTransform.position.x, key->localTransform.position.y, key->localTransform.position.z);
            printf("distance: %f\n", glm::distance(player->localTransform.position, key->localTransform.position));
            if (glm::distance(player->localTransform.position, key->localTransform.position) < 1.0f)
            {
                pickUp(world, "key");
                // printf("key found\n");
            }
        }
    }

    void PickSystem::pickUp(World *world, std::string object_name) // TODO: we can find a better way for searching an entity here
    {

        // Entity *hand = world->GetEntity("hand");
        // Entity *object = world->GetEntity(object_name);

        // // insert child to hand
        // world->InsertChild("hand", object_name);

        // glm::vec3 &position = object->localTransform.position;
        // glm::vec3 &scale = object->localTransform.scale;
        // glm::vec3 &rotation = object->localTransform.rotation;
        // printf("object position: %f, %f, %f\n", position.x, position.y, position.z);
        // printf("object scale: %f, %f, %f\n", scale.x, scale.y, scale.z);
        // printf("object rotation: %f, %f, %f\n", rotation.x, rotation.y, rotation.z);
        printf("INSIDE PICKUP");
        return;
    }
}
