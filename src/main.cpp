// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Main function.

// Includes.
#include <exception>
#include <iostream>
#include <memory>

// User includes.
#include "Game.hpp"

// Enumeration definitions.
enum MainFunctionStatusCode {
  MainFunctionSuccess,
  GameInitError,
  GameRunError
};

// Main function.
int main(int argc, char** argv) {
  std::unique_ptr<Game> game;

  try {
    game = std::unique_ptr<Game>(&Game::getInstance());
  }
  catch (GameInitException& game_init_exception) {
    std::cerr << "[Main] " << game_init_exception.what();
    return MainFunctionStatusCode::GameInitError;
  }

  try {
    game->run();
  }
  catch (GameRunException& game_run_exception) {
    std::cerr << "[Main] " << game_run_exception.what();
    return MainFunctionStatusCode::GameRunError;
  }

  return MainFunctionStatusCode::MainFunctionSuccess;
};
