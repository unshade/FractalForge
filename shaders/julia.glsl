uniform vec2 resolution; // Résolution de la fenêtre
uniform float zoom; // Facteur de zoom
uniform vec2 offset; // Décalage pour centrer la fractale
uniform vec2 c; // Constante complexe pour l'ensemble de Julia

vec3 hsvToRgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    // Convertir les coordonnées du pixel en coordonnées complexes
    vec2 uv = (gl_FragCoord.xy / resolution) * zoom + offset;
    vec2 z = uv;
    float i;

    // Itérer sur les coordonnées complexes pour déterminer si le point fait partie de l'ensemble de Julia
    for (i = 0.0; i < 2000.0; ++i)
    {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;

        if (dot(z, z) > 100.0)
        break;
    }

    if (i < 100.0) {
        vec3 rgb = hsvToRgb(vec3(0.5 + (i / 200.0), 0.5, 1.0));
        gl_FragColor = vec4(rgb, 1.0);
    } else {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Noir
    }


}
