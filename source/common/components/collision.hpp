#pragma once

#include "../ecs/component.hpp"
#include "../asset-loader.hpp"
#include <glm/glm.hpp>

namespace our {
    class CollisionComponent : public Component {
    public:
        //collider by bounding boxes
        glm::vec3 center;
        glm::vec3 size;
        glm::vec3 world_center;
        glm::vec3 world_size;

        // The ID of this component type is "Light"
        static std::string getID() { return "Collision"; }

        // Reads light details from the given json object
        void deserialize(const nlohmann::json& data) override;
        void update_collider(glm::mat4 modelMatrix,glm::vec3 scale);
        bool checkCollision(CollisionComponent other);
    };

}