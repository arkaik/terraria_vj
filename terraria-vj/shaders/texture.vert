#version 330

uniform mat4 projection, modelview, ftcMatrix;
uniform vec2 texCoordDispl;
uniform bool fixedToCamera;

in vec2 position;
in vec2 texCoord;
out vec2 texCoordFrag;

void main()
{
	// Pass texture coordinates to access a given texture atlas
	texCoordFrag = texCoord + texCoordDispl;
	// Transform position from pixel coordinates to clipping coordinates
	if (fixedToCamera) {
		gl_Position = projection * ftcMatrix * modelview * vec4(position, 0.0, 1.0);
	} else {
		gl_Position = projection * modelview * vec4(position, 0.0, 1.0); 
	}
}

