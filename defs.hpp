
#ifndef DEFS_HPP
#define DEFS_HPP

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>

#define PULSE_TIME 1.0
#define TURN_TIME 0.18
#define MAX_SPD 0.2
#define ACCEL_TIME 0.3
#define GRAVITY 0.0008
#define JUMP_GRAVITY 0.0019
#define JUMP_SPD 0.42
#define JUMP_TIME 0.15

#define SHADOW_ALPHA 0.62

#define MIN_SCALE 7.0/9.0
#define MAX_ANGLE 7.0
#define VIEW_BORDER 300
#define BASE_OUTLINE 5.0

#define RANGE 400.0

#define LIGHT_TO_TEXT 200.0
#define TEXT_TO_WALL 10.0

#define RES_X 960
#define RES_Y 640

#define TITLE "Game"

#if defined(__APPLE__) || defined(MACOSX)
#define RES(file_with_double_quotes) (resourcePath() + file_with_double_quotes)
#else
#define RES(file_with_double_quotes) (std::string("./res/") + file_with_double_quotes)
#endif

enum STATE{
    GAME,
    MENU,
};

enum PLAYER_STATE{
    STAND,
    WALK,
    CLIMB,
};

using namespace std;

#endif

