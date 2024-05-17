#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <img/img.hpp>
#include <sstream>

#include "App.hpp"
#include "Map.hpp"
#include "Graph.hpp"
#include "simpletext.h"
#include "utils.hpp"
#include "GLHelpers.hpp"

GLuint sprite_test{};

App::App() : _previousTime(0.0), _viewSize(2.0)
{
    // Attention à l'ordre d'appel des méthodes => lire leurs noms et voir si l'enchainement est cohérent.
    map.NUMBER_OF_PIXELS_IN_LINE = 10;
    map.schema_file = "map_schema_10x10_V2";
    map.get_NODES_from_ITD();
    map.create_GRAPH_from_NODES();
    map.get_SHORTER_PATH_from_dijkstra();
    map.generate_SCHEMA();
    map.get_PIXELS_from_SCHEMA();
    map.set_PIXELS_type();
    map.set_PIXELS_connected();
    // map.get_NODES_from_PIXELS_AUTO();
    map.get_TILES_from_PIXELS();
    map.render_TILES_texture();

    // srand((unsigned int)time(0));
    // std::cout << map.GRAPH << std::endl;

    // // This program will create some sequence of random
    // // numbers on every program run within range 0 to N-1
    // int factor{2};
    // for (size_t x = 0; x < map.NUMBER_OF_PIXELS_IN_LINE * factor; x++)
    //     std::cout << rand() % map.NUMBER_OF_PIXELS_IN_LINE << " ";

    // Debug
    // map.display_PIXELS_informations();

    sprite_test = loadTexture(img::load(make_absolute_path("images/Tiles/tile_0023.png", true), 4, true));
}

void App::setup()
{
    // Set the clear color to a nice blue
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    // Setup the text renderer with blending enabled and white text color
    TextRenderer.ResetFont();
    TextRenderer.SetColor(SimpleText::TEXT_COLOR, SimpleText::Color::WHITE);
    TextRenderer.SetColorf(SimpleText::BACKGROUND_COLOR, 0.f, 0.f, 0.f, 0.f);
    TextRenderer.EnableBlending(true);
}

void App::update()
{

    const double currentTime{glfwGetTime()};
    const double elapsedTime{currentTime - _previousTime};
    _previousTime = currentTime;

    if (i <= 0.5f)
        i += 0.1f * elapsedTime;
    else if (j <= 0.5f)
        j += 0.1f * elapsedTime;
    _angle += 10.0f * elapsedTime;
    _angle = std::fmod(_angle, 360.0f);
    std::cout << i << std::endl;

    render();
}

void App::render()
{
    // Clear the color and depth buffers of the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLoadIdentity();
    // glRotatef(_angle,0,0,1);
    // glPushMatrix();
    map.load_MAP();

    glTranslatef(i, j, 0);
    map.draw_quad_with_texture(sprite_test, {(int)(i), (int)(j), {}});
    // for (Node node : map.SHORTER_PATH)
    // {
    //     int X = node.pixel.x;
    //     int Y = (map.SCHEMA.width() - 1 - node.pixel.y);
    //     map.draw_quad_with_texture(sprite_test, {X, Y, {}});
    // }

    // glPopMatrix();

    // Text zone
    // TextRenderer.Label("- IMAC TOWER DEFENSE - ", _width / 2, 20, SimpleText::CENTER);

    // // Without set precision
    // const std::string angle_label_text { "Angle: " + std::to_string(_angle) };

    // // Using stringstream to format the string with fixed precision
    // std::string angle_label_text{};
    // std::stringstream stream{};
    // stream << std::fixed << "Angle: " << std::setprecision(2) << _angle;
    // stream << std::fixed << "MAP : " << map.NUMBER_OF_PIXELS_IN_LINE << " X " << map.NUMBER_OF_PIXELS_IN_LINE << " PIXELS";
    // // angle_label_text = stream.str();

    // TextRenderer.Label(angle_label_text.c_str(), _width / 2, _height - 4, SimpleText::CENTER);

    TextRenderer.Render();
}

void App::key_callback(int /*key*/, int /*scancode*/, int /*action*/, int /*mods*/)
{
}

void App::mouse_button_callback(int /*button*/, int /*action*/, int /*mods*/)
{
}

void App::scroll_callback(double /*xoffset*/, double /*yoffset*/)
{
}

void App::cursor_position_callback(double /*xpos*/, double /*ypos*/)
{
}

void App::size_callback(int width, int height)
{
    _width = width;
    _height = height;

    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, _width, _height);

    const float aspectRatio{_width / (float)_height};

    // Change the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspectRatio > 1.0f)
    {
        glOrtho(-_viewSize / 2.0f * aspectRatio, _viewSize / 2.0f * aspectRatio, -_viewSize / 2.0f, _viewSize / 2.0f, -1.0f, 1.0f);
    }
    else
    {
        glOrtho(-_viewSize / 2.0f, _viewSize / 2.0f, -_viewSize / 2.0f / aspectRatio, _viewSize / 2.0f / aspectRatio, -1.0f, 1.0f);
    }
}
