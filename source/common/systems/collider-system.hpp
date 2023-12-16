#pragma once

#include "../ecs/world.hpp"
#include "../components/movement.hpp"
#include "../components/collision.hpp"
#include "../components/free-camera-controller.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    // The movement system is responsible for moving every entity which contains a MovementComponent.
    // This system is added as a simple example for how use the ECS framework to implement logic. 
    // For more information, see "common/components/movement.hpp"
    class ColliderSystem {
    private:
    void revertMovement(Entity* moving,Entity* other){
        MovementComponent* movement = moving->getComponent<MovementComponent>();
        CollisionComponent* collider = moving->getComponent<CollisionComponent>();
        CollisionComponent* other_collider = other->getComponent<CollisionComponent>();
        float change = 0.0f;
        //try reverting x
        change=moving->localTransform.position.x;
        moving->localTransform.position.x = moving->last_location.x;
        collider->update_collider(moving->getLocalToWorldMatrix(), moving->localTransform.scale);
        if(collider->checkCollision(*other_collider)){
            //revert
            moving->localTransform.position.x = change;
        }
        else
        {
            if(movement){
                movement->linearVelocity.x = 0.0f;
            }
            return;
        }
        //try reverting y
        change=moving->localTransform.position.y;
        moving->localTransform.position.y = moving->last_location.y;
        collider->update_collider(moving->getLocalToWorldMatrix(),moving->localTransform.scale);
        if(collider->checkCollision(*other_collider)){
            //revert
            moving->localTransform.position.y = change;
        }
        else
        {
            if(movement){
                movement->linearVelocity.y = 0.0f;
            }
            return;
        }
        //try reverting z
        change=moving->localTransform.position.z;
        moving->localTransform.position.z = moving->last_location.z;
        collider->update_collider(moving->getLocalToWorldMatrix(),moving->localTransform.scale);
        if(collider->checkCollision(*other_collider)){
            //revert
            moving->localTransform.position.z = change;
        }
        else
        {
            if(movement){
                movement->linearVelocity.z = 0.0f;
            }
            return;
        }
        //revert all
        moving->localTransform.position = moving->last_location;
        if(movement){
            movement->linearVelocity = glm::vec3(0.0f);
        }
        collider->update_collider(moving->getLocalToWorldMatrix(),moving->localTransform.scale);
        if(collider->checkCollision(*other_collider))
        {
            printf("collision detected after reverting all\n");
        }
    }
    public:

        // This should be called every frame to update all entities containing a MovementComponent. 
        void checkCollision(World* world, float deltaTime) {
            //check for colliders and set the current location in world space
            std::vector<our::Entity*> colliding;
            for(auto entity : world->getEntities()){
                CollisionComponent* collider = entity->getComponent<CollisionComponent>();
                if(collider){
                    //update the collider
                    //if the collider is the player, remove the rotation from the getLocalToWorldMatrix
                    //given Localtoworldmatrix how to remove rotation
                    collider->update_collider(entity->getLocalToWorldMatrix(),entity->localTransform.scale);
                    colliding.push_back(entity);
                }
            }
            //check for collisions
            for(int i = 0; i < colliding.size(); i++){
                for(int j = i+1; j < colliding.size(); j++){
                    if( colliding[i]->getComponent<CollisionComponent>()->checkCollision(*colliding[j]->getComponent<CollisionComponent>())){
                        //if a collision has occured, move the object back to its previous position
                        printf("collision detected %d\n",i);
                        MovementComponent* movement = colliding[i]->getComponent<MovementComponent>();
                        FreeCameraControllerComponent* controller = colliding[i]->getComponent<FreeCameraControllerComponent>();
                        if(movement||controller){
                            revertMovement(colliding[i],colliding[j]);
                        }
                        movement = colliding[j]->getComponent<MovementComponent>();
                        controller = colliding[j]->getComponent<FreeCameraControllerComponent>();
                        if(movement||controller){
                            revertMovement(colliding[j],colliding[i]);
                        }
                    }  
                }
            }
        }

    };

}
