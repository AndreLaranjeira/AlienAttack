// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Main function.

// Includes.
#include <exception>
#include <iostream>

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
  try {
    Game game = Game::getInstance();
    game.run();
  }
  catch (GameInitException& e) {
      cerr << "[Main] " << e.what();
      return MainFunctionStatusCode::GameInitError;
  }

  return MainFunctionStatusCode::MainFunctionSuccess;
}
