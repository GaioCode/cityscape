#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class Sample4444: public Sample
{
public:
    Sample4444(wolf::App* pApp) : Sample(pApp,"Texture Format 4444") {}
    ~Sample4444();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = nullptr;
    wolf::VertexDeclaration* m_pDecl = nullptr;
    wolf::Program* m_pProgram = nullptr;
    GLuint m_tex = 0;
};
