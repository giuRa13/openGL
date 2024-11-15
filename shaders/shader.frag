#version 450 core                                                                  
                                                                              
in vec4 vCol;	                                                              
out vec4 colour;                                                              
                                                                              
void main()                                                                   
{                                                                             
    //colour = vec4(0.9, 0.65, 0.0, 1.0);                                       
	colour = vCol;                    						                   
}