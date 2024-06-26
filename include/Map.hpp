#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <img/img.hpp>
#include <glad/glad.h>
#include <simpletext.h>
#include "utils.hpp"
#include "Base.hpp"
#include "Graph.hpp"

struct Map
{
    size_t NUMBER_OF_PIXELS_IN_LINE{15};
    std::string schema_ITD_file;
    img::Image SCHEMA{img::load(make_absolute_path("images/map_schema_15x15_02.png", true), 3, true)};
    std::vector<Tile> TILES;
    std::vector<Pixel> PIXELS;
    std::vector<Node> NODES;
    Graph::WeightedGraph GRAPH;
    std::vector<std::vector<Node>> SHORTER_PATH_LIST;

    void check_order_elements_ITD();
    void get_SCHEMA_from_ITD();
    Color get_colors_from_ITD(std::string const &type);
    void get_NODES_from_ITD();
    void get_PIXELS_from_SCHEMA();
    void set_PIXELS_type();
    void set_PIXELS_connected();
    void check_if_PIXEL_is_NODE();
    void create_GRAPH_from_NODES();
    void get_SHORTER_PATH_LIST();
    void get_TILES_path_from_PIXELS();
    void get_TILES_MAP(std::unordered_map<std::filesystem::path, GLuint> &LoadedTextures);
    void draw_MAP();

    // Debug
    void display_PIXELS_informations();
    void display_SHORTER_PATH();

    // MAP PARAMETERS (SQUARE)
    float MAP_SIZE{1.f}; // 1.0F
    float SEMI_MAP_SIZE{MAP_SIZE / 2.0f};
    float PIXEL_SIZE{MAP_SIZE / NUMBER_OF_PIXELS_IN_LINE};
};
