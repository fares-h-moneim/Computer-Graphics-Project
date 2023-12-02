#include "entity.hpp"
#include "../deserialize-utils.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our
{

    // This function computes and returns a matrix that represents this transform
    // Remember that the order of transformations is: Scaling, Rotation then Translation
    // HINT: to convert euler angles to a rotation matrix, you can use glm::yawPitchRoll
    glm::mat4 Transform::toMat4() const
    {
        // TODO: (Req 3) Write this function

        // Initialize a 4x4 identity matrix
        glm::mat4 trans = glm::mat4(1.0f);

        // Apply translation to the matrix
        trans = glm::translate(trans, position);

        // Apply rotation to the matrix using euler angles (yaw, pitch, roll)
        trans = trans * glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);

        // Apply scaling to the matrix
        trans = glm::scale(trans, scale);

        // Return the final transformation matrix
        return trans;
    }

    // Deserializes the entity data and components from a json object
    void Transform::deserialize(const nlohmann::json &data)
    {
        // Extract and set the position from the JSON data, using the default value if not present
        position = data.value("position", position);

        // Extract and set the rotation from the JSON data, converting degrees to radians, with a default value if not present
        rotation = glm::radians(data.value("rotation", glm::degrees(rotation)));

        // Extract and set the scale from the JSON data, using the default value if not present
        scale = data.value("scale", scale);
    }

}
