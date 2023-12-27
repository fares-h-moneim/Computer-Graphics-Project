#pragma once

#include "../ecs/world.hpp"
#include "../application.hpp"

namespace our
{
    class DoorSystem
    {
        Application *app;
        Entity *player;
        Entity *key;
        Entity *door;

    public:
        void setApp(Application *app)
        {
            this->app = app;
        }

        void update(World *world);
        void openDoor();
    };
}
