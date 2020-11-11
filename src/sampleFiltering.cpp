#include "sampleFiltering.h"
#include "../samplefw/Grid2D.h"

struct Vertex
{
	GLfloat x,y;
	GLfloat u,v;
};

static const Vertex gs_squareVertices[] = {
	{ -0.5f, -0.5f,	0, 1 }, 
	{ -0.5f, 0.5f,	0, 0 }, 
	{ 0.5f, 0.5f,	1, 0 }, 

	{ 0.5f, 0.5f,	1, 0 }, 
	{ 0.5f, -0.5f,	1, 1 }, 
	{ -0.5f, -0.5f, 0, 1 }, 
};

SampleFiltering::~SampleFiltering()
{
	printf("Destroying Texture Filtering Sample\n");
	delete m_pDecl;
	wolf::MaterialManager::DestroyMaterial(m_pMat);
	wolf::TextureManager::DestroyTexture(m_pTex);
	wolf::BufferManager::DestroyBuffer(m_pVB);
}

void SampleFiltering::init()
{
    // Only init if not already done
    if(!m_pMat)
    {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		m_pVB = wolf::BufferManager::CreateVertexBuffer(gs_squareVertices, sizeof(Vertex) * 6);

		m_pDecl = new wolf::VertexDeclaration();
		m_pDecl->Begin();
		m_pDecl->AppendAttribute(wolf::AT_Position, 2, wolf::CT_Float);
		m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
		m_pDecl->SetVertexBuffer(m_pVB);
		m_pDecl->End();

		m_pTex = wolf::TextureManager::CreateTexture("data/brick.dds");
		m_pTex->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);

		m_pMat = wolf::MaterialManager::CreateMaterial("_sample_filtering");
		m_pMat->SetProgram("data/one_texture.vsh", "data/one_texture.fsh");
		m_pMat->SetTexture("tex", m_pTex);
	}

    printf("Successfully initialized Texture Filtering Sample\n");
}

void SampleFiltering::update(float dt) 
{
	if(m_pApp->isKeyDown('f'))
	{
		m_keyDown = true;
	}
	else 
	{
		if(m_keyDown)
		{
			m_isLinear = !m_isLinear;
			if(m_isLinear)
				m_pTex->SetFilterMode(wolf::Texture::FM_Linear, wolf::Texture::FM_Linear);
			else
				m_pTex->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
			m_keyDown = false;
		}
	}
}

void SampleFiltering::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 mProj = glm::ortho(0.0f,(float)width,(float)height,0.0f,0.0f,1000.0f);
    glm::mat4 mView = glm::mat4(1.0f);
    glm::mat4 mWorld = glm::translate(glm::vec3((float)width / 2.0f, (float)height / 2.0f, 0.0f)) *
					   glm::scale(glm::vec3((float)width * 0.75f, (float)height * 0.75f, 1.0f));

	m_pMat->SetUniform("projection", mProj);
	m_pMat->SetUniform("view", mView);
	m_pMat->SetUniform("world", mWorld);
    m_pMat->Apply();

	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
