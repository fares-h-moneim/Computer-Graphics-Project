#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"

namespace our
{

    // Function: Sets up the pipeline state and activates the shader for rendering
    void Material::setup() const
    {
        // TODO: (Req 7) Set up the pipeline state and activate the shader for rendering
        pipelineState.setup(); // Set up pipeline state
        shader->use();         // Activate the shader
    }

    // Function: Reads material data from a JSON object
    void Material::deserialize(const nlohmann::json &data)
    {
        // Check if the data is an object
        if (!data.is_object())
            return;

        // Check if "pipelineState" is present and deserialize it
        if (data.contains("pipelineState"))
        {
            pipelineState.deserialize(data["pipelineState"]);
        }

        // Get the shader from the AssetLoader based on the provided string
        shader = AssetLoader<ShaderProgram>::get(data["shader"].get<std::string>());

        // Set the "transparent" flag to the value in the JSON object, defaulting to false
        transparent = data.value("transparent", false);
    }

    // Function: Calls the setup of its parent and sets the "tint" uniform
    void TintedMaterial::setup() const
    {
        // TODO: (Req 7) Call the setup of the parent and set the "tint" uniform
        Material::setup();         // Call the parent setup
        shader->set("tint", tint); // Set the "tint" uniform
    }

    // Function: Reads material data from a JSON object
    void TintedMaterial::deserialize(const nlohmann::json &data)
    {
        // Call the deserialize of the parent
        Material::deserialize(data);

        // Check if the data is an object
        if (!data.is_object())
            return;

        // Set the "tint" member variable to the value in the JSON object, defaulting to white
        tint = data.value("tint", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // Function: Calls the setup of its parent, sets additional uniforms, and binds textures and samplers
    void TexturedMaterial::setup() const
    {
        // TODO: (Req 7) Call the setup of the parent, set additional uniforms, and bind textures and samplers
        TintedMaterial::setup();                       // Call the parent setup
        shader->set("alphaThreshold", alphaThreshold); // Set additional uniform "alphaThreshold"
        glActiveTexture(GL_TEXTURE0);                  // Activate texture unit 0

        // Bind texture and sampler to texture unit 0, and send the unit number to the uniform variable "tex"
        if (texture)
            texture->bind();
        if (sampler)
            sampler->bind(0);
        shader->set("tex", 0);
    }

    // Function: Reads material data from a JSON object
    void TexturedMaterial::deserialize(const nlohmann::json &data)
    {
        // Call the deserialize of the parent
        TintedMaterial::deserialize(data);

        // Check if the data is an object
        if (!data.is_object())
            return;

        // Set the "alphaThreshold" member variable to the value in the JSON object, defaulting to 0.0f
        alphaThreshold = data.value("alphaThreshold", 0.0f);

        // Get the texture and sampler from the AssetLoader based on the provided strings
        texture = AssetLoader<Texture2D>::get(data.value("texture", ""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }


    void LitMaterial::setup() const
    {
        TexturedMaterial::setup();
        shader->set("material.shininess",shineness);
        glActiveTexture(GL_TEXTURE1);
        if(diffuse)
        diffuse->bind();
        glActiveTexture(GL_TEXTURE2);
        if(specular)
        specular->bind();
        glActiveTexture(GL_TEXTURE3);
        if(ambient)
        ambient->bind();
        if (sampler){
            sampler->bind(1);
            sampler->bind(2);
            sampler->bind(3);
        }
        
        shader->set("material.diffuse",1);
        shader->set("material.specular",2);
        shader->set("material.ambient",3);
        //Q: is this correct?
        
    }
    void LitMaterial::deserialize(const nlohmann::json &data)
    {
        TexturedMaterial::deserialize(data);
        if (!data.is_object())
            return;
        diffuse = AssetLoader<Texture2D>::get(data.value("diffuse", ""));
        specular = AssetLoader<Texture2D>::get(data.value("specular", "")); 
        ambient = AssetLoader<Texture2D>::get(data.value("ambient", ""));
        shineness = data.value("shineness", 32.0f); 
    }


}