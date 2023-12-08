#include "building.h"

namespace sheep
{

    int Building::buildingIDCount = 0;

    Building::Building(wolf::Program* programParam, const std::string& positionUniformParam)
        : rotateX(0.0f), rotateY(0.0f), rotateZ(0.0f), scaleVector(glm::vec3(1.0f)), translateVector(glm::vec3(0.0f))
    {
        buildingID = ++buildingIDCount;
    }

    // Pure virtual destructor
    Building::~Building()
    {
        
    }

    void Building::translate(GLfloat x, GLfloat y, GLfloat z)
    {
        translateVector = glm::vec3(x, y, z);
    };

    void Building::scale(GLfloat x, GLfloat y, GLfloat z)
    {
        scaleVector = glm::vec3(x, y, z);
    };

    void Building::rotate(GLfloat x, GLfloat y, GLfloat z)
    {
        rotateX = x;
        rotateY = y;
        rotateZ = z;
    };
}