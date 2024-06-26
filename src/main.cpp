#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include "App.hpp"

namespace
{
    App &window_as_app(GLFWwindow *window)
    {
        return *static_cast<App *>(glfwGetWindowUserPointer(window));
    }
}

// Optional: limit the frame rate
constexpr double TARGET_TIME_FOR_FRAME{1.0 / 60.0};

int main()
{

    // Set an error callback to display glfw errors
    glfwSetErrorCallback([](int error, const char *description)
                         { std::cerr << "Error " << error << ": " << description << std::endl; });

    // Initialize glfw
    if (!glfwInit())
    {
        return -1;
    }

    // Create window
    GLFWwindow *window{glfwCreateWindow(1280, 720, "Window", nullptr, nullptr)};
    if (!window)
    {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Intialize glad (loads the OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    App app{};

    glfwSetWindowUserPointer(window, &app);

    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                       { window_as_app(window).key_callback(key, scancode, action, mods); });
    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods)
                               { window_as_app(window).mouse_button_callback(window, button, action, mods); });
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos)
                             { window_as_app(window).cursor_position_callback(window, xpos, ypos); });
    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
                              { window_as_app(window).size_callback(window, width, height); });

    // Force calling the size_callback of the game to set the right viewport and projection matrix
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        app.size_callback(window, width, height);
    }

    app.setup();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {

        // Get time (in second) at loop beginning
        double startTime{glfwGetTime()};

        app.update();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();

        // Optional: limit the frame rate
        double elapsedTime{glfwGetTime() - startTime};
        // wait the remaining time to match the target wanted frame rate
        if (elapsedTime < TARGET_TIME_FOR_FRAME)
        {
            glfwWaitEventsTimeout(TARGET_TIME_FOR_FRAME - elapsedTime);
        }
    }

    glfwTerminate();

    return 0;
}
