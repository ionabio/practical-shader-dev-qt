#pragma once
//Shaders are stored as const strings in this file

// the first two are for rainbow triangle
// the second two are for uniform color triangle

const char* vertexShaderRainbowSource = R"(
        #version 410

        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec4 col;

		out vec4 fragColor;

        void main()
        {
            gl_Position = vec4(pos, 1.0);
			fragColor = vec4(col);
        }
    )";

const char* fragmentShaderRainbowSource = R"(
        #version 410
        
        in vec4 fragColor;  
        out vec4 outColor;

        void main()
        {
            outColor = fragColor;
        }
    )";

const char* vertexShaderUniformSource = R"(
        #version 410

        layout (location = 0) in vec3 pos;

        void main()
        {
            gl_Position = vec4(pos, 1.0);
        }
    )";

const char* fragmentShaderUniformSource = R"(
        #version 410
        
        uniform vec4 col;  
        out vec4 outColor;

        void main()
        {
            outColor = col;
        }
    )";