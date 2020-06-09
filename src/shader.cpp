#include "util.cpp"
#include "gl_binding.cpp"

GLuint CreateShaderObject(GLenum shaderType, const char *filePath) {
    auto[succeed, fileContent] = GetTextFileContent(filePath);

    if (succeed) {
        auto shaderSource = fileContent.c_str();

        auto shader = glCreateShader(shaderType);

        if (shader) {
            glShaderSource(shader, 1, &shaderSource, nullptr);
            glCompileShader(shader);

            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

            if (status != GL_FALSE) {
                return shader;
            } else {
                GLint infoLogLength;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

                auto infoLog = new GLchar[infoLogLength + 1];
                glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);

                std::stringstream stringBuffer;
                stringBuffer << "Compile failure in ";

                switch (shaderType) {
                    case GL_VERTEX_SHADER  :
                        stringBuffer << "vertex";
                        break;
                    case GL_GEOMETRY_SHADER:
                        stringBuffer << "geometry";
                        break;
                    case GL_FRAGMENT_SHADER:
                        stringBuffer << "fragment";
                        break;
                    default:
                        stringBuffer << "unknown";
                        break;
                }

                stringBuffer << " shader:" << std::endl << std::string(infoLog) << std::endl;
                std::cerr << stringBuffer.str() << std::endl;

                delete[] infoLog;
                glDeleteShader(shader);
                return FALSE;
            }
        }
    }

    return FALSE;
}

GLuint CreateShader(const char *vertexShaderFilePath, const char *fragmentShaderFilePath) {
    auto vertexShader = CreateShaderObject(GL_VERTEX_SHADER, vertexShaderFilePath);
    auto fragmentShader = CreateShaderObject(GL_FRAGMENT_SHADER, fragmentShaderFilePath);

    if (vertexShader && fragmentShader) {
        auto shaderProgram = glCreateProgram();

        if (shaderProgram) {
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);

            glLinkProgram(shaderProgram);

            GLint status;
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

            glDetachShader(shaderProgram, vertexShader);
            glDetachShader(shaderProgram, fragmentShader);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            if (status != GL_FALSE) {
                return shaderProgram;
            } else {
                GLint infoLogLength;
                glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

                auto infoLog = new GLchar[infoLogLength + 1];
                glGetProgramInfoLog(shaderProgram, infoLogLength, nullptr, infoLog);

                std::stringstream stringBuffer;
                stringBuffer << "Linker failure: " << std::string(infoLog) << std::endl;
                std::cerr << stringBuffer.str() << std::endl;

                delete[] infoLog;

                glDeleteProgram(shaderProgram);
            }
        }
    }

    return FALSE;
}