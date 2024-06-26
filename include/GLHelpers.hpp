#pragma once

#include <img/img.hpp>
#include "glad/glad.h"
#include "utils.hpp"

GLuint loadTexture(uint8_t const *data, int width, int height);
inline GLuint loadTexture(img::Image const &image) { return loadTexture(image.data(), image.width(), image.height()); }
