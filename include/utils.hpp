#pragma once
#include <filesystem>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Graph.hpp"
#include "Cell.hpp"

struct Enemy;
struct Map;

std::filesystem::path
make_absolute_path(std::filesystem::path const &path, bool check_path_exists = true);

template <glm::length_t N, typename T, glm::qualifier Q>
std::ostream &operator<<(std::ostream &os, glm::vec<N, T, Q> const &vec);

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &vec);

bool operator==(Color const &color_1, Color const &color_2);
bool operator==(Pixel const &pixel_1, Pixel const &pixel_2);
std::ostream &operator<<(std::ostream &os, const Graph::WeightedGraph graph);

bool is_NODE(Connections const &NEIGHBOUR);
void set_IN_OUT_orientation_texture(Connections const &NEIGHBOUR, std::vector<std::filesystem::path> &TILE_path_list);
void set_NODE_orientation_texture(Connections const &NEIGHBOUR, std::vector<std::filesystem::path> &TILE_path_list);
void set_PATH_orientation_texture(Connections const &NEIGHBOUR, std::vector<std::filesystem::path> &TILE_path_list);

bool is_ENEMY_travel_correctly(Enemy &enemy, Map &map);
bool is_inside_MAP(float &x, float &y, Map &map);
bool hover_ELEMENT_in_UI(glm::vec2 const &mouse_cursor, glm::vec2 const &element_pos, int const &UI_size);
