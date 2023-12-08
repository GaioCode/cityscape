#include "cube.h"

static const sheep::VertexPosition3D cubeVertices[]
{
    // Front
	{ 0.0f, 0.0f, 1.0f },
	{ 0.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 0.0f, 1.0f },
	{ 0.0f, 0.0f, 1.0f },

	// Back
	{ 1.0f, 1.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f },

	// Left
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 1.0f, 1.0f },
	{ 0.0f, 0.0f, 1.0f },
	{ 0.0f, 0.0f, 1.0f },
	{ 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },

	// Right
	{ 1.0f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f },

	// Top
	{ 0.0f, 1.0f, 1.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 1.0f },
	{ 0.0f, 1.0f, 1.0f },

	// Bottom
	{ 0.0f, 0.0f, 1.0f },
	{ 1.0f, 0.0f, 1.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f },
};

static GLboolean isProgramGenerated = GL_FALSE;
static wolf::Program* program = 0;
static wolf::VertexDeclaration* vao = 0;     // VAO
static wolf::VertexBuffer* positionVBO = 0;       // VBO

static std::string colorUniform;


Cube::Cube(wolf::Program* programParam, const std::string& positionUniformParam, const std::string& colorUniformParam)
{
    if (!isProgramGenerated)
    {
        printf("Cube class not initialized. Initializing...\n");
        program = programParam;
        colorUniform = colorUniformParam;

        // Create VBOs
		
        positionVBO = wolf::BufferManager::CreateVertexBuffer(cubeVertices, sizeof(sheep::VertexPosition3D) * 36);

        // Create VAO and assign VBOs to it

        vao = new wolf::VertexDeclaration();
        vao->Begin();
        vao->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        vao->SetVertexBuffer(positionVBO);
        vao->End();

        isProgramGenerated = GL_TRUE;
    }
    printf("Successfully initialzed Cube class.\n");
    
}

Cube::~Cube()
{
    if (isProgramGenerated)
    {
        printf("Destructing Cube class...\n");
        delete vao;
        wolf::BufferManager::DestroyBuffer(positionVBO);
        isProgramGenerated = GL_FALSE;
        printf("Cube Class destructed.");
    }
    
}

void Cube::update(float dt)
{
    this->time += dt;
}

void Cube::render(const std::string& worldUniform, const std::string& projectionViewUniform, 
const glm::mat4& projectionViewMatrix)
{
	// Convert object space to world space

    glm::mat4 worldMatrix = 
        glm::translate(glm::mat4(1.0f), translateVector) *
        glm::rotate(glm::mat4(1.0f), rotateZ, glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::rotate(glm::mat4(1.0f), rotateY, glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), rotateX, glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0f), scaleVector);

	program->SetUniform(projectionViewUniform, projectionViewMatrix);
	program->SetUniform(worldUniform, worldMatrix);
    program->Bind();        // Bind here to fix shifting


	program->SetUniform(colorUniform, colorVector);

	program->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void Cube::render(const std::string& worldUniform, const std::string& viewUniform, const std::string& projectionUniform, 
const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	// Convert object space to world space

    glm::mat4 worldMatrix =
		glm::mat4(1.0f) *
        glm::translate(glm::mat4(1.0f), translateVector) *
		glm::scale(glm::mat4(1.0f), scaleVector) *
		glm::rotate(glm::mat4(1.0f), rotateX, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), rotateY, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), rotateZ, glm::vec3(0.0f, 0.0f, 1.0f));

	program->Bind();
	program->SetUniform(projectionUniform, projectionMatrix);
	program->SetUniform(viewUniform, viewMatrix);
	program->SetUniform(worldUniform, worldMatrix);

	program->SetUniform(colorUniform, colorVector);

	vao->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void Cube::translate(GLfloat x, GLfloat y, GLfloat z)
{
	this->translateVector = glm::vec3(x, y, z);
};


void Cube::scale(GLfloat x, GLfloat y, GLfloat z)
{
	this->scaleVector = glm::vec3(x, y, z);
};


void Cube::rotate(GLfloat x, GLfloat y, GLfloat z)
{
	this->rotateX = x;
	this->rotateY = y;
	this->rotateZ = z;
};

void Cube::setColor(const glm::vec4& color)
{
	this->colorVector = color;
};