#include "sample4444.h"
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

#define TEX 1

#if TEX == 0

static GLushort g_aTexture[] =
{
     0x00ff,  // blue
     0xff0f, // yellow
     0xf00f,  // red
     0x0f0f,  // green
};

#else

static GLushort g_aTexture[16*16];

#endif

Sample4444::~Sample4444()
{
	printf("Destroying Texture Format 4444 Sample\n");
	delete m_pDecl;
	wolf::ProgramManager::DestroyProgram(m_pProgram);
	wolf::BufferManager::DestroyBuffer(m_pVB);
	glDeleteTextures(1, &m_tex);
}

void Sample4444::init()
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

#if TEX == 0
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, g_aTexture);
#else
        for (int v = 0; v < 16; v++)
        {
            for (int u = 0; u < 16; u++)
            {
                g_aTexture[v * 16 + u] = 0x000f | (v << 4);
            }
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 16, 16, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, g_aTexture);
#endif

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    printf("Successfully initialized Texture Clamp to Edge Sample\n");
}

void Sample4444::update(float dt) 
{
}

void Sample4444::render(int width, int height)
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

