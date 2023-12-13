#include "collision.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    void CollisionComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        center = data.value("center", center); //Q: what is this default value
        size = data.value("size", size);
       
    
    }
    //function given another collider checks if a collision has occured
    //do i not need to make the comparison in world space?
    //ans:
    bool CollisionComponent::checkCollision(CollisionComponent other){
        //check if the two bounding boxes intersect
        if (world_center.x + world_size.x / 2 < other.world_center.x - other.world_size.x / 2 || world_center.x - world_size.x / 2 > other.world_center.x + other.world_size.x / 2)
            return false;
     

        if (world_center.y + world_size.y / 2 < other.world_center.y - other.world_size.y / 2 || world_center.y - world_size.y / 2 > other.world_center.y + other.world_size.y / 2)
            return false;
      
        if (world_center.z + world_size.z / 2 < other.world_center.z - other.world_size.z / 2 || world_center.z - world_size.z / 2 > other.world_center.z + other.world_size.z / 2)
            return false;
     
        return true;
    }
    void CollisionComponent::update_collider(glm::mat4 modelMatrix,glm::vec3 scale){
        //update the center and size of the collider to make it in world coordinates
        world_center = glm::vec3(modelMatrix * glm::vec4(center, 1.0f));
        world_size = scale * size;
    }
}