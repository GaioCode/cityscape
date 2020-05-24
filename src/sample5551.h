#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class Sample5551: public Sample
{
public:
    Sample5551(wolf::App* pApp) : Sample(pApp,"Texture Format 5551") {}
    ~Sample5551();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = nullptr;
    wolf::VertexDeclaration* m_pDecl = nullptr;
    wolf::Program* m_pProgram = nullptr;
    GLuint m_tex = 0;
};

