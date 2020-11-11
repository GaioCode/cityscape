#include "sampleMipmaps.h"
#include "../samplefw/Grid2D.h"

struct Vertex
{
	GLfloat x,y,z;
	GLfloat u,v;
};

static const Vertex gs_planeVertices[] = {
	{ -400.0f, 0.0f, -400.0f,	0, 16 }, 
	{ -400.0f, 0.0f, 100.0f,	0, 0 }, 
	{ 400.0f, 0.0f, 100.0f,	16, 0 }, 

	{ 400.0f, 0.0f, 100.0f,	16, 0 }, 
	{ 400.0f, 0.0f, -400.0f,	16, 16 }, 
	{ -400.0f, 0.0f, -400.0,	0, 16 }, 
};

SampleMipmaps::~SampleMipmaps()
{
	printf("Destroying Mipmaps Sample\n");
	delete m_pDecl;
	wolf::TextureManager::DestroyTexture(m_pTex);
	wolf::MaterialManager::DestroyMaterial(m_pMat);
	wolf::BufferManager::DestroyBuffer(m_pVB);
}

void SampleMipmaps::init()
{
    // Only init if not already done
    if(!m_pMat)
    {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		m_pVB = wolf::BufferManager::CreateVertexBuffer(gs_planeVertices, sizeof(Vertex) * 6);

		m_pDecl = new wolf::VertexDeclaration();
		m_pDecl->Begin();
		m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
		m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
		m_pDecl->SetVertexBuffer(m_pVB);
		m_pDecl->End();

		m_pTex = wolf::TextureManager::CreateTexture("data/brick.dds");
		m_pTex->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
		m_pTex->SetWrapMode(wolf::Texture::WM_Repeat);

		m_pMat = wolf::MaterialManager::CreateMaterial("_sample_mipmaps");
		m_pMat->SetProgram("data/one_texture.vsh", "data/one_texture.fsh");
		m_pMat->SetTexture("tex", m_pTex);
	}

    printf("Successfully initialized Mipmaps Sample\n");
}

void SampleMipmaps::update(float dt) 
{
	if(m_pApp->isKeyDown('f'))
	{
		m_keyDown = true;
	}
	else 
	{
		if(m_keyDown)
		{
			// advance the mode
			switch(m_currMode)
			{
				case wolf::Texture::FM_Nearest:
					m_currMode = wolf::Texture::FM_Linear;
					break;
				case wolf::Texture::FM_Linear:
					m_currMode = wolf::Texture::FM_TrilinearMipmap;
					break;
				case wolf::Texture::FM_TrilinearMipmap:
					m_currMode = wolf::Texture::FM_Nearest;
					break;
			}

			// set current mode
			switch(m_currMode)
			{
				case wolf::Texture::FM_Nearest:
					m_pTex->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
					break;
				case wolf::Texture::FM_Linear:
					m_pTex->SetFilterMode(wolf::Texture::FM_Linear, wolf::Texture::FM_Linear);
					break;
				case wolf::Texture::FM_TrilinearMipmap:
					m_pTex->SetFilterMode(wolf::Texture::FM_TrilinearMipmap, wolf::Texture::FM_Linear);
					break;
			}
			m_keyDown = false;
		}
	}

	if(m_pApp->isKeyDown('w'))
		m_eyePos += glm::vec3(0.0f,0.0f,-1.0f);
	if(m_pApp->isKeyDown('s'))
		m_eyePos += glm::vec3(0.0f,0.0f,1.0f);
	if(m_pApp->isKeyDown('a'))
		m_eyePos += glm::vec3(-1.0f,0.0f,0.0f);
	if(m_pApp->isKeyDown('d'))
		m_eyePos += glm::vec3(1.0f,0.0f,0.0f);
}

void SampleMipmaps::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// I've chosen to specify the vertices in clip space for this sample, just to easily make it
	// take up most of the viewport, regardless of window size. I could've done it by adding a world
	// matrix and scaling, but I opted to reuse the shader from the earlier samples.
    glm::mat4 mProj = glm::perspective(glm::radians(60.0f), (float)width/(float)height, 0.1f, 1000.0f);
    glm::mat4 mView = glm::lookAt(m_eyePos, m_eyePos + glm::vec3(0.0f,-50.0f,-100.0f), glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 mWorld = glm::mat4(1.0f);

	m_pMat->SetUniform("projection", mProj);
	m_pMat->SetUniform("view", mView);
	m_pMat->SetUniform("world", mWorld);
    m_pMat->Apply();

	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
