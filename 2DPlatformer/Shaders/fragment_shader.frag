#define S (iResolution.x / 6e1) // The cell size.

void mainImage(out vec4 c, vec2 p)
{
    c = texture2D(texture, floor((p + .5) / S) * S / iResolution.xy);
}