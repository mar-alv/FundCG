#pragma once
#include <string>
#include <glad/glad.h>

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

const float GRIDS_WIDTH = 64;
const float GRIDS_HEIGHT = 32;

const std::string SHADER_SPRITE_VS_PATH = "../shaders/sprite.vs";
const std::string SHADER_SPRITE_FS_PATH = "../shaders/sprite.fs";

const std::string LEVELS_PATH = "../levels/level";
const std::string LINK_SPRITE_PATH = "../textures/spritesheet2.png";

const std::string SHADER_TRANSFORMATIONS_VS_PATH = "../shaders/transformations.vs";
const std::string SHADER_TRANSFORMATIONS_FS_PATH = "../shaders/transformations.fs";
