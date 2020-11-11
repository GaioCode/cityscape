#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleWrapRepeat: public Sample
{
public:
    SampleWrapRepeat(wolf::App* pApp) : Sample(pApp,"Texture Repeat Wrap") {}
    ~SampleWrapRepeat();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = nullptr;
    wolf::VertexDeclaration* m_pDecl = nullptr;
    wolf::Material* m_pMat = nullptr;
    wolf::Texture* m_pTex = nullptr;
    bool m_mirrored = false;
    bool m_keyDown = false;
};