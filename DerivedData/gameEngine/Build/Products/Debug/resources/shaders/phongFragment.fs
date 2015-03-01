#version 120

const int MAX_POINT_LIGHTS = 4;
const int MAX_SPOT_LIGHTS = 4;

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 worldPos0;
varying vec4 color0;

struct BaseLight
{
    vec3 color;
    float intensity;
};

struct DirectionalLight
{
    BaseLight base;
    vec3 direction;
};

struct Attenuation
{
    float constant;
    float linear;
    float exponent;
};

struct PointLight
{
    BaseLight base;
    Attenuation atten;
    vec3 position;
    float range;
};

struct SpotLight
{
    PointLight pointLight;
    vec3 direction;
    float cutoff;
};

uniform vec3 baseColor;
uniform vec3 eyePos; //the camera position
uniform vec3 ambientLight;
uniform DirectionalLight directionalLight;
uniform sampler2D diffuse;

uniform float specularIntensity;
uniform float specularPower;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
    float diffuseFactor = dot(normal, -direction);
    
    vec4 diffuseColor = vec4(0,0,0,0);
    vec4 specularColor = vec4(0,0,0,0);
    
    if (diffuseFactor > 0) //if it's affecting the surface
    {
        diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;
        
        vec3 directionToEye = normalize(eyePos - worldPos0);
        vec3 reflectDirection = normalize(reflect(direction, normal));
        
        float specularFactor = dot(directionToEye, reflectDirection);
        specularFactor = pow(specularFactor, specularPower);
        
        if (specularFactor > 0)
        {
            specularColor = vec4(base.color, 1.0) * specularIntensity * specularFactor;
        }
    }
    
    return diffuseColor + specularColor;
}

vec4  calcDirectionalLight(DirectionalLight directionaLight, vec3 normal)
{
    return calcLight(directionaLight.base, -directionaLight.direction, normal);
}

vec4 calcPointLight(PointLight pointLight, vec3 normal)
{
    vec3 lightDirection = worldPos0 - pointLight.position;
    float distanceToPoint = length(lightDirection);
    
    if (distanceToPoint > pointLight.range)
        return vec4(0,0,0,0);
    
    lightDirection = normalize(lightDirection);
    
    vec4 color = calcLight(pointLight.base, lightDirection, normal);
    
    float attenuation = pointLight.atten.constant +
                        pointLight.atten.linear * distanceToPoint +
                        pointLight.atten.exponent * distanceToPoint * distanceToPoint +
                        0.0001; //so we don't divide by zero
    
    //light gets weaker when distance gets larger
    return color / attenuation;
}

vec4 calcSpotLight(SpotLight spotLight, vec3 normal)
{
    vec3 lightDirection = normalize(worldPos0 - spotLight.pointLight.position);
    float spotFactor = dot(lightDirection, spotLight.direction);
    
    vec4 color = vec4(0,0,0,0);
    
    if (spotFactor > spotLight.cutoff)
    {
        color = calcPointLight(spotLight.pointLight, normal) *
            (1.0 - (1.0 - spotFactor)/(1.0 - spotLight.cutoff));
    }
    
    return color;
}

void main()
{
    vec4 totalLight = vec4(ambientLight,1);
    vec4 TexColor = texture2D(diffuse, texCoord0.xy);
    vec4 color = vec4(baseColor, 1.0);
    
    if (TexColor != vec4(0,0,0,0))
    {
        color = TexColor * color;
    }
    
    vec3 normal = normalize(normal0);
    
    totalLight += calcDirectionalLight(directionalLight, normal);
    
    //glsl likes const variables for "for" loops
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        if (pointLights[i].base.intensity > 0)
        {
            totalLight += calcPointLight(pointLights[i], normal);
        }
    }
    
    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
    {
        if (spotLights[i].pointLight.base.intensity > 0)
        {
            totalLight += calcSpotLight(spotLights[i], normal);
        }
    }
    
    gl_FragColor = color * totalLight;
}