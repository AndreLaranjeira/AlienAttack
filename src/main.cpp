// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Main function.

// Includes.
#include <exception>
#include <iostream>
#include <string>

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
  Game *game;

  try {
    game = &Game::GetInstance();
  }
  catch (exception &e) {
      cout << "Caught exception: " << e.what();
      return MainFunctionStatusCode::GameInitError;
  }
  
  // Run game.
  game->Run();

  // Clean up resources used.
  delete game;

  return MainFunctionStatusCode::MainFunctionSuccess;
}
