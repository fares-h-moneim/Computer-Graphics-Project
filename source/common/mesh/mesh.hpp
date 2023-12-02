#pragma once

#include <glad/gl.h>
#include "vertex.hpp"

namespace our
{

// Attribute locations for vertex attributes
#define ATTRIB_LOC_POSITION 0
#define ATTRIB_LOC_COLOR 1
#define ATTRIB_LOC_TEXCOORD 2
#define ATTRIB_LOC_NORMAL 3

    class Mesh
    {
        // Object names for vertex array, vertex buffer, and element buffer
        unsigned int VBO, EBO;
        unsigned int VAO;
        // Number of elements to be drawn by glDrawElements
        GLsizei elementCount;

    public:
        // Constructor takes vectors of vertices and elements to initialize the mesh
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &elements)
        {
            // TODO: (Req 2) Write this function
            //  Remember to store the number of elements in "elementCount" since you will need it for drawing
            elementCount = elements.size();

            // Generate buffers
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
            glGenVertexArrays(1, &VAO);

            // Bind vertex array object
            glBindVertexArray(VAO);

            // Bind and store data in the vertex buffer
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            // Bind and store data in the element buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), &elements[0], GL_STATIC_DRAW);

            // Set vertex attribute pointers
            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
            glEnableVertexAttribArray(ATTRIB_LOC_POSITION);

            glVertexAttribPointer(ATTRIB_LOC_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
            glEnableVertexAttribArray(ATTRIB_LOC_COLOR);

            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tex_coord));
            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);

            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);
        }

        // Render the mesh using glDrawElements
        void draw()
        {
            // TODO: (Req 2) Write this function
            // Bind the vertex array object and draw the elements
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        // Destructor deletes vertex and element buffers, and vertex array object
        ~Mesh()
        {
            // TODO: (Req 2) Write this function
            // Delete OpenGL buffers and vertex array object
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            glDeleteVertexArrays(1, &VAO);
        }

        // Deleted copy constructor and assignment operator to prevent unintended copies
        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}
