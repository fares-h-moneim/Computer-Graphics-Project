#include "light-source.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    void LightComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        lightColor = data.value("lightColor", lightColor); //Q: what is this default value
    }
}