#include "sample4444.h"
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

static GLushort gs_texture1Data[] =
{
     0x00ff,  // blue
     0xff0f, // yellow
     0xf00f,  // red
     0x0f0f,  // green
};

static GLushort gs_texture2Data[16*16];

Sample4444::~Sample4444()
{
	printf("Destroying Texture Format 4444 Sample\n");
	delete m_pDecl;
	wolf::MaterialManager::DestroyMaterial(m_pMat);
	wolf::TextureManager::DestroyTexture(m_pTex1);
	wolf::TextureManager::DestroyTexture(m_pTex2);
	wolf::BufferManager::DestroyBuffer(m_pVB);
}

void Sample4444::init()
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

		m_pTex1 = wolf::TextureManager::CreateTexture(gs_texture1Data, 2, 2, wolf::Texture::FMT_4444);
		m_pTex1->SetFilterMode(wolf::Texture::FM_Nearest);

        for (int v = 0; v < 16; v++)
        {
            for (int u = 0; u < 16; u++)
            {
                gs_texture2Data[v * 16 + u] = 0x000f | (v << 4);
            }
        }
		m_pTex2 = wolf::TextureManager::CreateTexture(gs_texture2Data, 16, 16, wolf::Texture::FMT_4444);
		m_pTex2->SetFilterMode(wolf::Texture::FM_Nearest);

		m_pCurrTex = m_pTex1;

		m_pMat = wolf::MaterialManager::CreateMaterial("_sample_4444");
		m_pMat->SetProgram("data/one_texture.vsh", "data/one_texture.fsh");
		m_pMat->SetTexture("tex", m_pCurrTex);
    }

    printf("Successfully initialized Texture Clamp to Edge Sample\n");
}

void Sample4444::update(float dt) 
{
	if(m_pApp->isKeyDown('f'))
	{
		m_keyDown = true;
	}
	else 
	{
		if(m_keyDown)
		{
			if(m_pCurrTex == m_pTex1)
				m_pCurrTex = m_pTex2;
			else
				m_pCurrTex = m_pTex1;

			m_pMat->SetTexture("tex", m_pCurrTex);
			m_keyDown = false;
		}
	}
}

void Sample4444::render(int width, int height)
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

