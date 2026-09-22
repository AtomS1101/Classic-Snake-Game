#pragma once

constexpr int LENGTH = 5;
constexpr int MARGIN = 5;
constexpr int FOOD   = 5; // default food count
constexpr int SPEED  = 2; // default speed (0 ~ 5)

constexpr int UP     = 1;
constexpr int DOWN   = 2;
constexpr int LEFT   = 3;
constexpr int RIGHT  = 4;

#define convIndex(x, y) ((y) * sizeX + (x))
