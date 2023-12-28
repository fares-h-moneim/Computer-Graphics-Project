#pragma once

#include "scp-movement.hpp"
#include "free-camera-controller.hpp"
#include "../ecs/entity.hpp"
#include "../components/movement.hpp"
#include "../components/collision.hpp"

#include <iostream>

namespace our{
    void ScpMovement::update(World* world){
        for (Entity* entity: world->getEntities()){
            if (entity->name == "scp"){
                scp = entity;
            }
            if (entity->name == "player"){
                player = entity;
                camera = entity->getComponent<CameraComponent>();
            }
        }
        if (player && scp){
            scpBoundingBox = scp->getComponent<CollisionComponent>();
            isScpInteresctingWithFrustum();
            if (isInViewPort){
                printf("scp in viewport\n");
            }
            else{
                printf("scp not in viewport\n");
            }
        }
    }

    void ScpMovement::extractPlanes(const glm::mat4& MVP){
        planes[0].normal = glm::vec3(MVP[0][3] - MVP[0][0], MVP[1][3] - MVP[1][0], MVP[2][3] - MVP[2][0]);
        planes[1].normal = glm::vec3(MVP[0][3] + MVP[0][0], MVP[1][3] + MVP[1][0], MVP[2][3] + MVP[2][0]);
        planes[2].normal = glm::vec3(MVP[0][3] + MVP[0][1], MVP[1][3] + MVP[1][1], MVP[2][3] + MVP[2][1]);
        planes[3].normal = glm::vec3(MVP[0][3] - MVP[0][1], MVP[1][3] - MVP[1][1], MVP[2][3] - MVP[2][1]);
        planes[4].normal = glm::vec3(MVP[0][2], MVP[1][2], MVP[2][2]);
        planes[5].normal = glm::vec3(MVP[0][3] - MVP[0][2], MVP[1][3] - MVP[1][2], MVP[2][3] - MVP[2][2]);
        // for (int i = 0; i < 6; ++i) {
        //     float length = glm::length(planes[i].normal);
        //     printf("length: %f\n", length);
        //     planes[i].normal /= length;
        //     planes[i].distance = MVP[3][3] + MVP[3][i] * length;
        //     printf("hello\n");
        // }
    }

    bool ScpMovement::isBoxOutsidePlane(const glm::vec4& scpMinPoint, const glm::vec4& scpMaxPoint, const ScpMovement::Plane& plane) const {

        glm::vec3 p[8];
        p[0] = glm::vec3(scpMinPoint.x, scpMinPoint.y, scpMinPoint.z);
        p[1] = glm::vec3(scpMaxPoint.x, scpMinPoint.y, scpMinPoint.z);
        p[2] = glm::vec3(scpMinPoint.x, scpMaxPoint.y, scpMinPoint.z);
        p[3] = glm::vec3(scpMaxPoint.x, scpMaxPoint.y, scpMinPoint.z);
        p[4] = glm::vec3(scpMinPoint.x, scpMinPoint.y, scpMaxPoint.z);
        p[5] = glm::vec3(scpMaxPoint.x, scpMinPoint.y, scpMaxPoint.z);
        p[6] = glm::vec3(scpMinPoint.x, scpMaxPoint.y, scpMaxPoint.z);
        p[7] = glm::vec3(scpMaxPoint.x, scpMaxPoint.y, scpMaxPoint.z);

        for (int i = 0; i < 8; ++i) {
            float distance = glm::dot(plane.normal, p[i]) + plane.distance;
            if (distance < 0.0f) {
                return true;
            }
        }

        return false;
    }

    void ScpMovement::isScpInteresctingWithFrustum(){
        glm::mat4 mvp = camera->getProjectionMatrix(windowSize) * camera->getViewMatrix() * camera->getOwner()->getLocalToWorldMatrix();
        glm::vec3 halfSize = scpBoundingBox->size * 0.5f;
        glm::vec4 scpMaxPoint = glm::vec4(halfSize + scpBoundingBox->center, 1.0f);
        glm::vec4 scpMinPoint = glm::vec4(scpBoundingBox->center - halfSize, 1.0f);
        extractPlanes(mvp);
        for (int i = 0; i < 6; ++i) {
            if (isBoxOutsidePlane(scpMaxPoint, scpMinPoint, planes[i])) {
                isInViewPort = false;
                return;
            }
        }
        isInViewPort = true;
    }
}