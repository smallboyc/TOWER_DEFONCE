#pragma once

#include <glad/glad.h>
#include <simpletext.h>
#include "Map.hpp"
#include "utils.hpp"
#include <vector>
#include "Enemy.hpp"

class App
{
public:
    App();

    void setup();
    void update();

    // GLFW callbacks binding
    void key_callback(int key, int scancode, int action, int mods);
    void mouse_button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);
    void cursor_position_callback(double xpos, double ypos);
    void size_callback(int width, int height);

private:
    void render();

    int _width{};
    int _height{};
    double _previousTime{};
    float _viewSize{};
    const double elapsedTime{};
    // Add your variables here
    Map map;
    Node node;
    GLuint _texture{};
    float i{0};
    float _angle{};

    SimpleText TextRenderer{};
};