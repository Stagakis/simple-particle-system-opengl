#version 330 core

// Interpolated values from the vertex shaders
in vec3 vertex_position_worldspace;
in vec3 vertex_position_cameraspace;
in vec3 vertex_normal_cameraspace;
in vec2 vertex_UV;

uniform int useTexture = 0;
uniform sampler2D diffuseColorSampler;
uniform sampler2D specularColorSampler;
uniform sampler2DShadow shadowMapSampler;
uniform mat4 V;

// Phong
// light properties
struct Light {
    vec4 La;
    vec4 Ld;
    vec4 Ls;
    vec3 lightPosition_worldspace;
    float power;
};
uniform Light light = Light(
    vec4(1, 1, 1, 1),
    vec4(1, 1, 1, 1),
    vec4(1, 1, 1, 1),
    vec3(0, 4, 4),
    20.0f
);

// materials
struct Material {
    vec4 Ka;
    vec4 Kd;
    vec4 Ks;
    float Ns;
};
uniform Material mtl = Material(
    vec4(0.24725, 0.1995, 0.0745, 1),
    vec4(0.75164, 0.60648, 0.22648, 1),
    vec4(0.628281, 0.555802, 0.366065, 1),
    51.2f
);

// Output data
out vec4 fragmentColor;

void phong();

void main() {
    phong();
}

void phong() {
    vec4 _Ks = mtl.Ks;
    vec4 _Kd = mtl.Kd;
    vec4 _Ka = mtl.Ka;
    float _Ns = mtl.Ns;
    // use texture for materials
    if (useTexture == 1) {
        _Ks = vec4(texture(specularColorSampler, vertex_UV).rgb, 1.0);
        _Kd = vec4(texture(diffuseColorSampler, vertex_UV).rgb, 1.0);
        _Ka = vec4(0.1, 0.1, 0.1, 1.0);
        _Ns = 10;
    }

    // model ambient intensity (Ia)
    vec4 Ia = light.La * _Ka;

    // model diffuse intensity (Id)
    vec3 N = normalize(vertex_normal_cameraspace);
    vec3 L = normalize((V * vec4(light.lightPosition_worldspace, 1)).xyz
        - vertex_position_cameraspace);
    float cosTheta = clamp(dot(L, N), 0, 1);
    vec4 Id = light.Ld * _Kd * cosTheta;

    // model specular intensity (Is)
    vec3 R = reflect(-L, N);
    vec3 E = normalize(- vertex_position_cameraspace);
    float cosAlpha = clamp(dot(E, R), 0, 1);
    float specular_factor = pow(cosAlpha, _Ns);
    vec4 Is = light.Ls * _Ks * specular_factor;

    //model the light distance effect
    float distance = length(light.lightPosition_worldspace
        - vertex_position_worldspace);
    float distance_sq = distance * distance;

    // final fragment color
    fragmentColor = vec4(
        Ia +
        Id * light.power / distance_sq +
        Is * light.power / distance_sq);
}
