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
        Entity *door1;
        Entity *door2;
        bool keyCanOpenDoor = false;
        bool open = false;
        double openValue = 2;

    public:
        void setApp(Application *app)
        {
            this->app = app;
        }

        void update(World *world, double deltaTime);
        void openDoor(double deltaTime, Entity *door, float targetX);
        void reset();
    };
}
