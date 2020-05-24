#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleClampMode: public Sample
{
public:
    SampleClampMode(wolf::App* pApp) : Sample(pApp,"Texture Clamp Modes") {}
    ~SampleClampMode();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = nullptr;
    wolf::VertexDeclaration* m_pDecl = nullptr;
    wolf::Program* m_pProgram = nullptr;
    GLuint m_tex = 0;
};


