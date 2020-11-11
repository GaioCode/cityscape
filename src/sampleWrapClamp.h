#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleWrapClamp: public Sample
{
public:
    SampleWrapClamp(wolf::App* pApp) : Sample(pApp,"Texture Wrap Clamp") {}
    ~SampleWrapClamp();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = nullptr;
    wolf::VertexDeclaration* m_pDecl = nullptr;
    wolf::Material* m_pMat = nullptr;
    wolf::Texture* m_pTex = nullptr;
    bool m_showBorderIssue = false;
    bool m_keyDown = false;
};


