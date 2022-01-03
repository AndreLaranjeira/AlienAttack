// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Music class - Header file.

// Define guard.
#ifndef MUSIC_H_
#define MUSIC_H_

// Includes.
#include <iostream>
#include <stdexcept>
#include <string>

// SDL2 includes.
#include <SDL2/SDL_mixer.h>

// Namespace.
using namespace std;

// Class definition.
class Music {
  // Public components.
  public:

    // Class method prototypes.
    Music();
    Music(string file);
    ~Music();

    // Method prototypes.
    bool isOpen();
    bool isUsingMixer();
    void open(string file);
    void play(int repetitions = -1);
    void stop(unsigned int fade_out_duration_milliseconds = 1500);

  // Private components.
  private:

    // Members.
    Mix_Music* music = nullptr;
    bool usingMixer = false;

    // Method prototypes.
    void cleanUpCurrentMusic();
    string formatMusicExceptionMessage(
      string exception_context,
      string exception_cause
    );
    bool mixerInUse();
    void openNewMusic(string file);
    int playCurrentMusic(int repetitions);
    int stopCurrentMusic(unsigned int fade_out_duration_milliseconds);
    void throwHandleMusicException(string error_description);
    void throwOpenMusicException(string error_description);
};

#endif // MUSIC_H_