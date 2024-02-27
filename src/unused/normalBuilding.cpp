#include "normalBuilding.h"

static GLboolean isProgramGenerated = GL_FALSE;
static wolf::Program* program = 0;
static wolf::VertexDeclaration* vao = 0;     // VAO
static wolf::VertexBuffer* positionVBO = 0;       // VBO
static wolf::Texture* textureManager;

const int BUILDING_SIDES = 6;
const int VERTICES_PER_SIDE = 4;

// TODO: Give NormalBuilding static ID int tracker

NormalBuilding::NormalBuilding(wolf::Program* programParam, const std::string& positionUniformParam, 
std::vector<sheep::VertexPosTex5D> vertices)
{
    if (!isProgramGenerated)
    {
        printf("NormalBuilding class not initialized. Initializing...\n");
        program = programParam;

        // Create VBOs

        sheep::VertexPosTex5D* array = vertices.data();
		
        positionVBO = wolf::BufferManager::CreateVertexBuffer(array, sizeof(sheep::VertexPosTex5D) * VERTICES_PER_SIDE
         * BUILDING_SIDES);

        // Create VAO and assign VBOs and Texture Unit to it

        vao = new wolf::VertexDeclaration();
        vao->Begin();
		vao->SetVertexBuffer(positionVBO);
        vao->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
		vao->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        vao->End();

		// Create Texture

		textureManager = wolf::TextureManager::CreateTexture("data/textures/brick.png");

        isProgramGenerated = GL_TRUE;
    }
    printf("Successfully initialzed NormalBuilding class.\n");
}

NormalBuilding::~NormalBuilding()
{
    if (isProgramGenerated)
    {
        printf("Destructing NormalBuilding class...\n");
		wolf::TextureManager::DestroyTexture(textureManager);
        wolf::BufferManager::DestroyBuffer(positionVBO);
        delete vao;
        program = 0;
		positionVBO = 0;
        textureManager = nullptr;
        isProgramGenerated = GL_FALSE;
        printf("NormalBuilding Class destructed.");
    }
}

void NormalBuilding::update(float dt)
{
    this->time += dt;
}

void NormalBuilding::render(const std::string& worldUniform, const std::string& projectionViewUniform,
const std::string& textureUniform, const glm::mat4& projectionViewMatrix)
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
	program->SetUniform("tex", 0);		// TODO: Put "Claw" number as param
    program->Bind();        // Bind here to fix shifting

	vao->Bind();
	textureManager->Bind(0);
	glDrawArrays(GL_TRIANGLES, 0, VERTICES_PER_SIDE * BUILDING_SIDES);

}

void NormalBuilding::translate(GLfloat x, GLfloat y, GLfloat z)
{
	this->translateVector = glm::vec3(x, y, z);
};


void NormalBuilding::scale(GLfloat x, GLfloat y, GLfloat z)
{
	this->scaleVector = glm::vec3(x, y, z);
};


void NormalBuilding::rotate(GLfloat x, GLfloat y, GLfloat z)
{
	this->rotateX = x;
	this->rotateY = y;
	this->rotateZ = z;
};