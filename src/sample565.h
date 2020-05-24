#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class Sample565: public Sample
{
public:
    Sample565(wolf::App* pApp) : Sample(pApp,"Texture Format 565") {}
    ~Sample565();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = nullptr;
    wolf::VertexDeclaration* m_pDecl = nullptr;
    wolf::Program* m_pProgram = nullptr;
    GLuint m_tex = 0;
};
