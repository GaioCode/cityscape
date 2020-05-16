#include "sampleClampMode.h"
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

static GLubyte textureData[] = {
     0, 0, 0,		255, 0, 0,	255, 0, 0,		255, 255, 0,  
     0, 0, 0,		255, 0, 0,	255, 0, 0,		255, 255, 0,  
     0, 0, 0,		255, 0, 0,	255, 0, 0,		255, 255, 0,  
     0, 0, 0,		255, 0, 0,	255, 0, 0,		255, 255, 0,  
};

SampleClampMode::~SampleClampMode()
{
	printf("Destroying Texture Clamp to Edge Sample\n");
	delete m_pDecl;
	wolf::ProgramManager::DestroyProgram(m_pProgram);
	wolf::BufferManager::DestroyBuffer(m_pVB);
	glDeleteTextures(1, &m_tex);
}

void SampleClampMode::init()
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

		glGenTextures(1, &m_tex);
		glBindTexture(GL_TEXTURE_2D, m_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		// These two lines are explained soon!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//#define SHOW_BORDER_ISSUE
#ifdef SHOW_BORDER_ISSUE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
#else
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#endif
	}

    printf("Successfully initialized Texture Clamp to Edge Sample\n");
}

void SampleClampMode::update(float dt) 
{
}

void SampleClampMode::render(int width, int height)
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



