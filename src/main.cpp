// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Main function.

// Includes.
#include <exception>
#include <iostream>
#include <memory>

// User includes.
#include "Game.hpp"

// Namespace.
using namespace std;

// Enumeration definitions.
enum MainFunctionStatusCode {
  MainFunctionSuccess,
  GameInitError
};

// Main function.
int main(int argc, char** argv) {
  unique_ptr<Game> game;

  try {
    game = unique_ptr<Game>(&Game::getInstance());
    game->run();
  }
  catch (GameInitException& e) {
      cerr << "[Main] " << e.what();
      return MainFunctionStatusCode::GameInitError;
  }

  return MainFunctionStatusCode::MainFunctionSuccess;
};
