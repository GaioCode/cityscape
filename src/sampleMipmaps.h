#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleMipmaps: public Sample
{
public:
    SampleMipmaps(wolf::App* pApp) : Sample(pApp,"Texture Mipmaps") {}
    ~SampleMipmaps();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = nullptr;
    wolf::VertexDeclaration* m_pDecl = nullptr;
    wolf::Material* m_pMat = nullptr;
    wolf::Texture* m_pTex = nullptr;
    glm::vec3 m_eyePos = glm::vec3(0.0f, 50.0f, 100.0f);
    bool m_keyDown = false;
    wolf::Texture::FilterMode m_currMode = wolf::Texture::FM_Nearest;
};