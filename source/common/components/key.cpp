#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"
#include "key.hpp"

namespace our
{
    // Reads linearVelocity & angularVelocity from the given json object
    void KeyComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        keyCanOpenDoor = data.value("keyCanOpenDoor", keyCanOpenDoor);
        isPickedUp = data.value("isPickedUp", isPickedUp);
    }
}