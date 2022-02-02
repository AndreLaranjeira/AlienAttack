// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Music class - Header file.

// Define guard.
#ifndef MUSIC_H_
#define MUSIC_H_

// Includes.
#include <memory>
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
class OpenMusicErrorDescription : public ErrorDescription<OpenMusicErrorCode> {
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    string describeErrorCause(OpenMusicErrorCode error_code) override;
    string describeErrorDetails(OpenMusicErrorCode error_code) override;
    string describeErrorSummary() override;
};

class PlayMusicErrorDescription : public ErrorDescription<PlayMusicErrorCode> {
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    string describeErrorCause(PlayMusicErrorCode error_code) override;
    string describeErrorDetails(PlayMusicErrorCode error_code) override;
    string describeErrorSummary() override;
};

class StopMusicErrorDescription : public ErrorDescription<StopMusicErrorCode> {
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    string describeErrorCause(StopMusicErrorCode error_code) override;
    string describeErrorDetails(StopMusicErrorCode error_code) override;
    string describeErrorSummary() override;
};

// Exception definitions.
class OpenMusicException :
  public RuntimeException<OpenMusicErrorCode, OpenMusicErrorDescription>
{
    // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};

class PlayMusicException :
  public RuntimeException<PlayMusicErrorCode, PlayMusicErrorDescription>
{
    // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};

class StopMusicException :
  public RuntimeException<StopMusicErrorCode, StopMusicErrorDescription>
{
    // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
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
    int playCurrentMusicWithMixer(int repetitions);
    int stopCurrentMusicWithMixer(unsigned int fade_out_duration_milliseconds);
};

#endif // MUSIC_H_
