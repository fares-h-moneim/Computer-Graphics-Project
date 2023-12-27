#pragma once

#include "../ecs/world.hpp"
#include "../application.hpp"

namespace our
{
    class PickSystem
    {
        Application *app;
        Entity *player;
        Entity *key;
        Entity *hand;

    public:
        void setApp(Application *app)
        {
            this->app = app;
        }

        void update(World *world);
        void pickUp();
    };
}
