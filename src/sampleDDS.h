#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleDDS: public Sample
{
public:
    SampleDDS(App* pApp) : Sample(pApp,"Texture Format DDS") {}
    ~SampleDDS();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = nullptr;
    wolf::VertexDeclaration* m_pDecl = nullptr;
    wolf::Program* m_pProgram = nullptr;
    GLuint m_tex = 0;
};
