uniform mat4 projectionView;
uniform mat4 world;

in vec4 position;
in vec2 a_uv1;

out vec2 v_uv1;

void main()
{
    gl_Position = projectionView * world * position;
    v_uv1 = a_uv1;
}