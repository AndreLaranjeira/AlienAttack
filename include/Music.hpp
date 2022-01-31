// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Music class - Header file.

// Define guard.
#ifndef MUSIC_H_
#define MUSIC_H_

// Includes.
#include <memory>
#include <stdexcept>
#include <string>

// SDL2 includes.
#include <SDL2/SDL_mixer.h>

// Template includes.
#include "templates/ErrorDescription.hpp"
#include "templates/RuntimeException.hpp"

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

// Type definitions.
using MixMusicUniquePTR = unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)>;

// Auxiliary class definitions.
class OpenMusicErrorDescription :
  public ErrorDescriptionTemplate<OpenMusicErrorCode>
{
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescriptionTemplate::ErrorDescriptionTemplate;

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

    // Inherited methods.
    using ErrorDescriptionTemplate::ErrorDescriptionTemplate;

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

    // Inherited methods.
    using ErrorDescriptionTemplate::ErrorDescriptionTemplate;

    // Method prototypes.
    string describeErrorCause(StopMusicErrorCode error_code) override;
    string describeErrorDetails(StopMusicErrorCode error_code) override;
    string describeErrorSummary() override;
};

// Exception definitions.
class OpenMusicException :
  public RuntimeExceptionTemplate<
    OpenMusicErrorCode,
    OpenMusicErrorDescription
  > {
    // Public components.
  public:

    // Inherited methods.
    using RuntimeExceptionTemplate::RuntimeExceptionTemplate;
};

class PlayMusicException :
  public RuntimeExceptionTemplate<
    PlayMusicErrorCode,
    PlayMusicErrorDescription
  > {
    // Public components.
  public:

    // Inherited methods.
    using RuntimeExceptionTemplate::RuntimeExceptionTemplate;
};

class StopMusicException :
  public RuntimeExceptionTemplate<
    StopMusicErrorCode,
    StopMusicErrorDescription
  > {
    // Public components.
  public:

    // Inherited methods.
    using RuntimeExceptionTemplate::RuntimeExceptionTemplate;
};

// Class definition.
class Music {
  // Public components.
  public:

    // Class method prototypes.
    Music() = default;
    Music(string file);

    // Method prototypes.
    bool isOpen();
    bool isUsingMixer();
    void open(string file);
    void play(int repetitions = -1);
    void stop(unsigned int fade_out_duration_milliseconds = 1500);

  // Private components.
  private:

    // Members.
    MixMusicUniquePTR music = MixMusicUniquePTR(nullptr, &Mix_FreeMusic);
    bool usingMixer = false;

    // Method prototypes.
    bool mixerInUse();
    int playCurrentMusic(int repetitions);
    int stopCurrentMusic(unsigned int fade_out_duration_milliseconds);
};

#endif // MUSIC_H_