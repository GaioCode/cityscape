#include "sampleWrapRepeat.h"
#include "../samplefw/Grid2D.h"

struct Vertex
{
	GLfloat x,y;
	GLfloat u,v;
};

static const Vertex gs_squareVertices[] = {
	{ -0.5f, -0.5f,	0, 2 }, 
	{ -0.5f, 0.5f,	0, 0 }, 
	{ 0.5f, 0.5f,	2, 0 }, 

	{ 0.5f, 0.5f,	2, 0 }, 
	{ 0.5f, -0.5f,	2, 2 }, 
	{ -0.5f, -0.5f, 0, 2 }, 
};

static GLubyte gs_textureData[] = {
     0, 0, 255,  // blue
     255, 255, 0, // yellow
     255, 0, 0,  // red
     0, 255, 0,  // green
};

SampleWrapRepeat::~SampleWrapRepeat()
{
	printf("Destroying Texture Wrap Modes Sample\n");
	delete m_pDecl;
	wolf::MaterialManager::DestroyMaterial(m_pMat);
	wolf::TextureManager::DestroyTexture(m_pTex);
	wolf::BufferManager::DestroyBuffer(m_pVB);
}

void SampleWrapRepeat::init()
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

		m_pTex = wolf::TextureManager::CreateTexture(gs_textureData, 2, 2, wolf::Texture::FMT_888);
		m_pTex->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
		m_pTex->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);

		m_pMat = wolf::MaterialManager::CreateMaterial("_sample_wrap_repeat");
		m_pMat->SetProgram("data/one_texture.vsh", "data/one_texture.fsh");
		m_pMat->SetTexture("tex", m_pTex);
	}

    printf("Successfully initialized Texture Wrap Modes Sample\n");
}

void SampleWrapRepeat::update(float dt) 
{
	if(m_pApp->isKeyDown('w'))
		m_keyDown = true;
	else
	{
		if(m_keyDown)
		{
			m_mirrored = !m_mirrored;

			if(m_mirrored)
				m_pTex->SetWrapMode(wolf::Texture::WM_MirroredRepeat);
			else 
				m_pTex->SetWrapMode(wolf::Texture::WM_Repeat);
			m_keyDown = false;
		}
	}
}

void SampleWrapRepeat::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 mProj = glm::ortho(0.0f,(float)width,(float)height,0.0f,0.0f,1000.0f);
    glm::mat4 mView = glm::mat4(1.0f);
    glm::mat4 mWorld = glm::translate(glm::vec3((float)width / 2.0f, (float)height / 2.0f, 0.0f)) *
					   glm::scale(glm::vec3((float)width * 0.5f, (float)height * 0.5f, 1.0f));

	m_pMat->SetUniform("projection", mProj);
	m_pMat->SetUniform("view", mView);
	m_pMat->SetUniform("world", mWorld);
    m_pMat->Apply();
    
	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
