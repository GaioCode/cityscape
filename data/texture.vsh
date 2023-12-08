uniform mat4 projectionView;
uniform mat4 world;

in vec3 a_position;
in vec2 a_uv1;

out vec2 v_uv1;

void main()
{
    gl_Position = projectionView * world * vec4(a_position, 1.0f);
    v_uv1 = a_uv1;
}