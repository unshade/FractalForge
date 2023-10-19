uniform vec2 resolution; // Résolution de la fenêtre
uniform float zoom; // Facteur de zoom
uniform vec2 offset; // Décalage pour centrer la fractale
uniform vec2 c; // Constante complexe pour l'ensemble de Julia

// STANDARD HSV <--> RGB CONVERSION (from https://gist.github.com/983/e170a24ae8eba2cd174f)
vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}
vec3 hsv2rgb(vec3 c)
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
        vec3 rgb = hsv2rgb(vec3((i / 100.0), 0.5, 1.0));
        gl_FragColor = vec4(rgb, 1.0);
    } else {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Noir
    }


}
