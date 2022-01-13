// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Music class - Header file.

// Define guard.
#ifndef MUSIC_H_
#define MUSIC_H_

// Includes.
#include <stdexcept>
#include <string>

// SDL2 includes.
#include <SDL2/SDL_mixer.h>

// User includes.
#include "ErrorDescriptionTemplate.hpp"

// Namespace.
using namespace std;

// Enumeration definitions.
enum OpenMusicErrorCode {
  LoadMusicError = 1
};

enum PlayMusicErrorCode {
  PlayUnopenedMusicError = 1,
  MusicAlreadyPlayingError,
  MixerInUseError,
  FailureToPlayMusicError
};

enum StopMusicErrorCode {
  StopUnopenedMusicError = 1,
  MusicNotPlayedError,
  MixerNotInUseError,
  FailureToStopMusicError
};

// Auxiliary class definitions.
class OpenMusicErrorDescription :
  public ErrorDescriptionTemplate<OpenMusicErrorCode>
{
  // Public components.
  public:

    // Class method prototypes.
    OpenMusicErrorDescription(OpenMusicErrorCode error_code);
    ~OpenMusicErrorDescription();

    // Method prototypes.
    string describeErrorCause(OpenMusicErrorCode error_code) override;
    string describeErrorDetails(OpenMusicErrorCode error_code) override;
    string describeErrorSummary() override;
};

class PlayMusicErrorDescription :
  public ErrorDescriptionTemplate<PlayMusicErrorCode>
{
  // Public components.
  public:

    // Class method prototypes.
    PlayMusicErrorDescription(PlayMusicErrorCode error_code);
    ~PlayMusicErrorDescription();

    // Method prototypes.
    string describeErrorCause(PlayMusicErrorCode error_code) override;
    string describeErrorDetails(PlayMusicErrorCode error_code) override;
    string describeErrorSummary() override;
};

class StopMusicErrorDescription :
  public ErrorDescriptionTemplate<StopMusicErrorCode>
{
  // Public components.
  public:

    // Class method prototypes.
    StopMusicErrorDescription(StopMusicErrorCode error_code);
    ~StopMusicErrorDescription();

    // Method prototypes.
    string describeErrorCause(StopMusicErrorCode error_code) override;
    string describeErrorDetails(StopMusicErrorCode error_code) override;
    string describeErrorSummary() override;
};

// Exception definitions.
class OpenMusicException :
  public OpenMusicErrorDescription,
  public runtime_error
{
    // Public components.
  public:

    // Class method prototypes.
    OpenMusicException(OpenMusicErrorCode error_code);
    ~OpenMusicException();
};

class PlayMusicException :
  public PlayMusicErrorDescription,
  public runtime_error
{
    // Public components.
  public:

    // Class method prototypes.
    PlayMusicException(PlayMusicErrorCode error_code);
    ~PlayMusicException();
};

class StopMusicException :
  public StopMusicErrorDescription,
  public runtime_error
{
    // Public components.
  public:

    // Class method prototypes.
    StopMusicException(StopMusicErrorCode error_code);
    ~StopMusicException();
};

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
    bool mixerInUse();
    void openNewMusic(string file);
    int playCurrentMusic(int repetitions);
    int stopCurrentMusic(unsigned int fade_out_duration_milliseconds);
};

#endif // MUSIC_H_