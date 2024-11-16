#version 450 core                                                                  
                                                                              
in vec4 vCol;	
in vec2 TexCoord;

out vec4 colour;     

uniform sampler2D theTexture;
                                                                              
void main()                                                                   
{                                                                             
    //colour = vec4(0.9, 0.65, 0.0, 1.0);                                       
	//colour = vCol;   
    colour = texture(theTexture, TexCoord);                 						                   
}