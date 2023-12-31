#include "texturedCube.h"

static const sheep::VertexPosTex5D cubeVertices[]
{
    // Front face
    {-0.5, -0.5,  0.5,  0.0, 0.0}, { 0.5, -0.5,  0.5,  1.0, 0.0}, { 0.5,  0.5,  0.5,  1.0, 1.0},
    {-0.5, -0.5,  0.5,  0.0, 0.0}, { 0.5,  0.5,  0.5,  1.0, 1.0}, {-0.5,  0.5,  0.5,  0.0, 1.0},
    
    // Back face
    {-0.5, -0.5, -0.5,  1.0, 0.0}, {-0.5,  0.5, -0.5,  1.0, 1.0}, { 0.5,  0.5, -0.5,  0.0, 1.0},
    {-0.5, -0.5, -0.5,  1.0, 0.0}, { 0.5,  0.5, -0.5,  0.0, 1.0}, { 0.5, -0.5, -0.5,  0.0, 0.0},
    
    // Top face
    {-0.5,  0.5, -0.5,  0.0, 1.0}, {-0.5,  0.5,  0.5,  0.0, 0.0}, { 0.5,  0.5,  0.5,  1.0, 0.0},
    {-0.5,  0.5, -0.5,  0.0, 1.0}, { 0.5,  0.5,  0.5,  1.0, 0.0}, { 0.5,  0.5, -0.5,  1.0, 1.0},
    
    // Bottom face
    {-0.5, -0.5, -0.5,  0.0, 0.0}, { 0.5, -0.5, -0.5,  1.0, 0.0}, { 0.5, -0.5,  0.5,  1.0, 1.0},
    {-0.5, -0.5, -0.5,  0.0, 0.0}, { 0.5, -0.5,  0.5,  1.0, 1.0}, {-0.5, -0.5,  0.5,  0.0, 1.0},
    
    // Right face
    { 0.5, -0.5, -0.5,  0.0, 0.0}, { 0.5,  0.5, -0.5,  1.0, 0.0}, { 0.5,  0.5,  0.5,  1.0, 1.0},
    { 0.5, -0.5, -0.5,  0.0, 0.0}, { 0.5,  0.5,  0.5,  1.0, 1.0}, { 0.5, -0.5,  0.5,  0.0, 1.0},
    
    // Left face
    {-0.5, -0.5, -0.5,  1.0, 0.0}, {-0.5, -0.5,  0.5,  0.0, 0.0}, {-0.5,  0.5,  0.5,  0.0, 1.0},
    {-0.5, -0.5, -0.5,  1.0, 0.0}, {-0.5,  0.5,  0.5,  0.0, 1.0}, {-0.5,  0.5, -0.5,  1.0, 1.0},
};

static GLboolean isProgramGenerated = GL_FALSE;
static wolf::Program* program = 0;
static wolf::VertexDeclaration* vao = 0;     // VAO
static wolf::VertexBuffer* positionVBO = 0;       // VBO
static wolf::Texture* textureManager;


TexturedCube::TexturedCube(wolf::Program* programParam, const std::string& positionUniformParam)
{
    if (!isProgramGenerated)
    {
        printf("TexturedCube class not initialized. Initializing...\n");
        program = programParam;

        // Create VBOs
		
        positionVBO = wolf::BufferManager::CreateVertexBuffer(cubeVertices, sizeof(sheep::VertexPosTex5D) * 36);

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
    printf("Successfully initialzed TexturedCube class.\n");
    
}

TexturedCube::~TexturedCube()
{
    if (isProgramGenerated)
    {
        printf("Destructing TexturedCube class...\n");
		wolf::TextureManager::DestroyTexture(textureManager);
        wolf::BufferManager::DestroyBuffer(positionVBO);
		delete vao;
		program = 0;
		positionVBO = 0;
		textureManager = nullptr;
        isProgramGenerated = GL_FALSE;
        printf("TexturedCube Class destructed.\n");
    }
    
}

void TexturedCube::update(float dt)
{
    this->time += dt;
}

void TexturedCube::render(const std::string& worldUniform, const std::string& projectionViewUniform,
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
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void TexturedCube::translate(GLfloat x, GLfloat y, GLfloat z)
{
	this->translateVector = glm::vec3(x, y, z);
};


void TexturedCube::scale(GLfloat x, GLfloat y, GLfloat z)
{
	this->scaleVector = glm::vec3(x, y, z);
};


void TexturedCube::rotate(GLfloat x, GLfloat y, GLfloat z)
{
	this->rotateX = x;
	this->rotateY = y;
	this->rotateZ = z;
};