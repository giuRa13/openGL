#version 450 core                                                                  
                                                                              
in vec4 vCol;	
in vec2 TexCoord;

out vec4 colour;     

struct DirectionalLight
{
    vec3 colour;
    float ambientIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
                                                                              
void main()                                                                   
{                                     
    vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;

    //colour = vec4(0.9, 0.65, 0.0, 1.0);                                       
	//colour = vCol;   
    colour = texture(theTexture, TexCoord) * ambientColour;                 						                   
}