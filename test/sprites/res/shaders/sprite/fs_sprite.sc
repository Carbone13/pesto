$input v_uv, v_textureCoordinate

#include <bgfx_shader.sh>

SAMPLER2D(u_texture, 0);

void main()
{
    vec2 uv = vec2(v_uv.x * v_textureCoordinate.z + v_textureCoordinate.x, v_uv.y * v_textureCoordinate.w + v_textureCoordinate.y);
	gl_FragColor = texture2D(u_texture, uv);
}