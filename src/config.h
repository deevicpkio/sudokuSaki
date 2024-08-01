#ifndef SUDOKU_CONFIG
#define SUDOKU_CONFIG
#pragma once

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1200;

// NOTE: Handy macros
#define SHOW_VAR(value) spdlog::debug("{}: {}", #value, value);

#endif
