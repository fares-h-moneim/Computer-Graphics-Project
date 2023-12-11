#include "light-source.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    void LightComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        lightColor = data.value("lightColor", lightColor); //Q: what is this default value
        lightType = data.value("lightType", lightType);
        //for directional and spot only
        direction = data.value("direction", direction);
        //for spot only
        innerAngle = data.value("innerAngle", innerAngle);
        outerAngle = data.value("outerAngle", outerAngle);
        //for point &spot lights attunuations 
        constant = data.value("constant", constant);
        linear = data.value("linear", linear);
        quadratic = data.value("quadratic", quadratic);
        //light given different ways of lighting


    
    }
}