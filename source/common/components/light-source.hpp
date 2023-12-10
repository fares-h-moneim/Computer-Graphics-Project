#pragma once

#include "../ecs/component.hpp"
#include "../asset-loader.hpp"
#include <glm/glm.hpp>

namespace our {
    class LightComponent : public Component {
    public:
        glm::vec3 lightColor;
        std::string lightType; // directional (sun) point(bulb) spot (flashlight)
        glm::vec3 direction; //for directional light and spot (the direction it focus on)
        float innerAngle; //for spot light
        float outerAngle;  //for spot light
        float constant, linear, quadratic; //for point light and spot light how they decrease

        // The ID of this component type is "Light"
        static std::string getID() { return "Light"; }

        // Reads light details from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}