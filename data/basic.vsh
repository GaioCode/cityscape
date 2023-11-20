uniform mat4 projectionView;
uniform mat4 world;
in vec4 position;

void main()
{
    gl_Position = projectionView * world * position;
}