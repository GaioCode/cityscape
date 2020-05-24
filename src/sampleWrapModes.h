#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleWrapModes: public Sample
{
public:
    SampleWrapModes(wolf::App* pApp) : Sample(pApp,"Texture Wrap Modes") {}
    ~SampleWrapModes();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = nullptr;
    wolf::VertexDeclaration* m_pDecl = nullptr;
    wolf::Program* m_pProgram = nullptr;
    GLuint m_tex = 0;
};