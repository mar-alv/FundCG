#pragma once
#include <glad/glad.h>
#include "ConstantsPlayer.h"

const GLuint WIDTH = 1280;
const GLuint HEIGHT = 720;

const float TILE_WIDTH = 128;
const float TILE_HEIGHT = 64;

const float XI = WIDTH / 2 - TILE_WIDTH / 2;
const float YI = 70;

const std::string LEVELS_PATH = "../levels/level";

const std::string TEXTURE_FILE_FORMAT = ".png";

const std::string SHADER_SPRITE_VS_PATH = "../shaders/sprite.vs";
const std::string SHADER_SPRITE_FS_PATH = "../shaders/sprite.fs";

const std::string GRIDS_SPRITES_PATH = "../textures/tiles/tile";
const std::string PLANT_SPRITES_PATH = "../textures/plants/plant";

const std::string SHADER_TRANSFORMATIONS_VS_PATH = "../shaders/transformations.vs";
const std::string SHADER_TRANSFORMATIONS_FS_PATH = "../shaders/transformations.fs";
