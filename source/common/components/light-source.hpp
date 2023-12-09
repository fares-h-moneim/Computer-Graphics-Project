#pragma once

#include "../ecs/component.hpp"
#include "../asset-loader.hpp"
#include <glm/glm.hpp>

namespace our {
    class LightComponent : public Component {
    public:
        glm::vec3 lightColor;
       // float lightIntensity;
       // float lightRadius;
       // float angle
       // std::string lightType;

        // The ID of this component type is "Light"
        static std::string getID() { return "Light"; }

        // Reads light details from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}