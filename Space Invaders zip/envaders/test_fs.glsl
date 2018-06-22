//#version 330 core
//out vec4 FragColor;

//in vec3 ourColor;
//in vec2 TexCoord;

// texture sampler
//uniform sampler2D texture1;

//void main()
//{
	//FragColor = texture(texture1, TexCoord);
	//FragColor = vec4(ourColor, 1.0);
//}


#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{    
    color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
}  