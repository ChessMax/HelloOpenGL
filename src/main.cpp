#include "main.hpp"
#include "window.cpp"

int APIENTRY wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow) {
    // инициализируем контекст отрисовки
    auto[succeed, hwnd, dc] = InitRenderingContext(instance, cmdShow);

    if (!succeed)
        return appFail("InitRenderingContext failed.");

    auto shader = CreateShader(
        "data\\simple_vertex_shader.vert",
        "data\\simple_fragment_shader.frag");

    const float vertexPositions[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 1.0f,
    };

    GLuint posBufferObject;
    glGenBuffers(1, &posBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, posBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
    glBindVertexArray(0); // unbind VAO

    bool isRunning = true;

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DOUBLEBUFFER);
    glClearColor(0.129f, 0.586f, 0.949f, 1.0f); // rgb(33, 150, 243)

    // основной цикл приложения
    while (isRunning) {
        // обработка оконных сообщений
        isRunning = ProcessEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
        glUseProgram(0);

        SwapBuffers(dc);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &posBufferObject);
    glDeleteProgram(shader);

    // завершаем работу приложения
    DestroyWindow(hwnd);
    UnregisterClassW(windowClassName, instance);

    return 0;
}