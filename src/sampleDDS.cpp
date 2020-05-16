#include "sampleDDS.h"
#include "../samplefw/Grid2D.h"

struct Vertex
{
	GLfloat x,y;
	GLfloat u,v;
};

static const Vertex squareVertices[] = {
	{ 100.0f, 100.0f,	0, 1 }, 
	{ 100.0f, 300.0f,	0, 0 }, 
	{ 300.0f, 300.0f,	1, 0 }, 

	{ 300.0f, 300.0f,	1, 0 }, 
	{ 300.0f, 100.0f,	1, 1 }, 
	{ 100.0f, 100.0,	0, 1 }, 
};

SampleDDS::~SampleDDS()
{
	printf("Destroying Texture Format DDS Sample\n");
	delete m_pDecl;
	wolf::ProgramManager::DestroyProgram(m_pProgram);
	wolf::BufferManager::DestroyBuffer(m_pVB);
	glDeleteTextures(1, &m_tex);
}

void SampleDDS::init()
{
	// Only init if not already done
    if(!m_pProgram)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        m_pProgram = wolf::ProgramManager::CreateProgram("data/one_texture.vsh", "data/one_texture.fsh");
        m_pVB = wolf::BufferManager::CreateVertexBuffer(squareVertices, sizeof(Vertex) * 6);

        m_pDecl = new wolf::VertexDeclaration();
        m_pDecl->Begin();
        m_pDecl->AppendAttribute(wolf::AT_Position, 2, wolf::CT_Float);
        m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        m_pDecl->SetVertexBuffer(m_pVB);
        m_pDecl->End();

        m_tex = wolf::CreateTextureFromDDS("data/metal.dds");

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    printf("Successfully initialized Texture Format DDS Sample\n");
}

void SampleDDS::update(float dt) 
{
}

void SampleDDS::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 mProj = glm::ortho(0.0f,(float)width,(float)height,0.0f,0.0f,1000.0f);

    // Use shader program.
	m_pProgram->Bind();
    
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex);

	// Bind Uniforms
	m_pProgram->SetUniform("projection", mProj);
    m_pProgram->SetUniform("texture", 0);
    
	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

