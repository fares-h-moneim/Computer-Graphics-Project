#pragma once

#include "../ecs/world.hpp"
#include "../application.hpp"
#include <vector>
#include <unordered_map>

namespace our
{
    class PickSystem
    {
        Application *app;
        Entity *player;
        std::vector<Entity *> keys;
        Entity *hand;
        Entity *heldKey = nullptr;
        struct OriginalTransform
        {
            glm::vec3 position;
            glm::vec3 rotation;
            glm::vec3 scale;
        };
        std::unordered_map<Entity *, OriginalTransform> originalTransforms;

    public:
        void setApp(Application *app)
        {
            this->app = app;
        }

        void update(World *world);
        void pickUp(Entity *key);
        void putDown(Entity *key);
    };
}
