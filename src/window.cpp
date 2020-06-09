#include "shader.cpp"

const wchar_t windowClassName[] = L"HelloOpenGL";

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_QUIT:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

HWND CreateWnd(HINSTANCE instance, LPCWSTR wndClassName, LPCWSTR wndTitle) {
    return CreateWindowW(wndClassName, wndTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                         CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, instance, nullptr);
}

std::tuple<bool, HWND, HDC> ircFail(const char *reason) {
    return {fail(reason), 0, 0};
}

std::tuple<bool, HWND, HDC, HGLRC> ctcFail(const char *reason) {
    return {fail(reason), 0, 0, 0};
}

std::tuple<bool, HWND, HDC, HGLRC> CreateTempRenderingContext(HINSTANCE instance) {
    // создаем временное окно
    HWND tempWnd = CreateWnd(instance, windowClassName, L"Temp window");

    if (!tempWnd) {
        return ctcFail("Create temp window failed.");
    }

    HDC tempDC = GetDC(tempWnd);

    if (!tempDC) {
        return ctcFail("Get temp window device context failed.");
    }

    // выбираем формат пикселей устройства
    PIXELFORMATDESCRIPTOR tempPfd = {};
    tempPfd.nSize = sizeof(tempPfd);
    tempPfd.nVersion = 1;
    tempPfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    tempPfd.iPixelType = PFD_TYPE_RGBA;
    tempPfd.cColorBits = 32;
    tempPfd.cAlphaBits = 8;
    tempPfd.cDepthBits = 24;

    int tempPFDID = ChoosePixelFormat(tempDC, &tempPfd);

    if (tempPFDID == 0) {
        return ctcFail("ChoosePixelFormat failed.");
    }

    if (SetPixelFormat(tempDC, tempPFDID, &tempPfd) == 0) {
        return ctcFail("SetPixelFormat failed.");
    }

    HGLRC tempRenderingContext = wglCreateContext(tempDC);

    if (tempRenderingContext == nullptr) {
        return ctcFail("wglCreateContext failed.");
    }

    if (wglMakeCurrent(tempDC, tempRenderingContext) == 0) {
        return ctcFail("wglMakeCurrent failed.");
    }

    return {true, tempWnd, tempDC, tempRenderingContext};
}

std::tuple<bool, HWND, HDC> InitRenderingContext(HINSTANCE instance, int cmdShow) {
    // регистрируем класс окна
    WNDCLASSEXW wc = {};

    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instance;
    wc.hIcon = nullptr;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = windowClassName;
    wc.hIconSm = nullptr;

    if (!RegisterClassExW(&wc)) {
        return ircFail("RegisterClass failed");
    }

    // создаем временный контекст отрисовки
    auto[succeed, tempWnd, tempDC, tempRenderingContext] = CreateTempRenderingContext(instance);

    if (!InitGLBindings()) {
        return ircFail("Bindings initialization failed");
    }

    // создаем основное окно
    HWND hWnd = CreateWnd(instance, windowClassName, L"Hello OpenGL");

    if (!hWnd) {
        return ircFail("CreateWindow failed");
    }

//    RECT rect;
//    if (GetWindowRect(hWnd, &rect)) {
//        SetWindowPos(hWnd, 0, rect.left, rect.top, 800, 600, 0);
//    }

    HDC dc = GetDC(hWnd);

    const int pixelAttribs[] =
        {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
            WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
            WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
            WGL_COLOR_BITS_ARB, 32,
            WGL_ALPHA_BITS_ARB, 8,
            WGL_DEPTH_BITS_ARB, 24,
            WGL_STENCIL_BITS_ARB, 8,
            WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
            WGL_SAMPLES_ARB, 4,
            0
        };

    UINT numFormats;
    int pixelFormatID;
    BOOL status = wglChoosePixelFormatARB(dc, pixelAttribs, nullptr, 1, &pixelFormatID, &numFormats);

    if (!status || numFormats == 0) {
        return ircFail("wglChoosePixelFormatARB() failed.");
    }

    PIXELFORMATDESCRIPTOR PFD;
    DescribePixelFormat(dc, pixelFormatID, sizeof(PFD), &PFD);
    SetPixelFormat(dc, pixelFormatID, &PFD);

    // версия OpenGL
    const int major_min = 4;
    const int minor_min = 5;
    int contextAttribs[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
            WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

    HGLRC renderingContext = wglCreateContextAttribsARB(dc, nullptr, contextAttribs);
    if (renderingContext == nullptr) {
        return ircFail("wglCreateContextAttribsARB failed.");
    }

    // подчищаем за временным окно и временным контекстом отрисовки
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(tempRenderingContext);
    ReleaseDC(tempWnd, tempDC);
    DestroyWindow(tempWnd);

    // назначаем новый текущий контекст отрисовки
    if (!wglMakeCurrent(dc, renderingContext)) {
        return ircFail("wglMakeCurrent failed.");
    }

    ShowWindow(hWnd, cmdShow);
    UpdateWindow(hWnd);

    return {true, hWnd, dc};
}

bool ProcessEvents() {
    MSG msg;

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        switch (msg.message) {
            case WM_QUIT:
                return false;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}