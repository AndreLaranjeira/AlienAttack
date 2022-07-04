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

// Declarations.
class Music;
enum OpenMusicErrorCode : unsigned short;
class OpenMusicErrorDescription;
class OpenMusicException;
enum PlayMusicErrorCode : unsigned short;
class PlayMusicErrorDescription;
class PlayMusicException;
enum StopMusicErrorCode : unsigned short;
class StopMusicErrorDescription;
class StopMusicException;

// Enumeration definitions.
enum OpenMusicErrorCode : unsigned short {
  FailureToLoadMusic = 1
};

enum PlayMusicErrorCode : unsigned short {
  PlayedUnopenedMusic = 1,
  InvalidPlayCommand,
  MixerInUse,
  FailureToPlayMusic
};

enum StopMusicErrorCode : unsigned short {
  StoppedUnopenedMusic = 1,
  StoppedUnplayedMusic,
  FailureToStopMusic
};

// Type definitions.
using MixMusicUniquePTR = std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)>;

// Auxiliary class definitions.
class OpenMusicErrorDescription : public ErrorDescription<OpenMusicErrorCode> {
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      OpenMusicErrorCode error_code
    ) const noexcept override;
    std::string describeErrorSummary() const noexcept override;
};

class PlayMusicErrorDescription : public ErrorDescription<PlayMusicErrorCode> {
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      PlayMusicErrorCode error_code
    ) const noexcept override;
    std::string describeErrorDetails(
      PlayMusicErrorCode error_code
    ) const noexcept override;
    std::string describeErrorSummary() const noexcept override;
};

class StopMusicErrorDescription : public ErrorDescription<StopMusicErrorCode> {
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      StopMusicErrorCode error_code
    ) const noexcept override;
    std::string describeErrorDetails(
      StopMusicErrorCode error_code
    ) const noexcept override;
    std::string describeErrorSummary() const noexcept override;
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
    Music() noexcept = default;
    Music(std::string file);

    // Method prototypes.
    bool isOpen() const noexcept;
    bool isUsingMixer() const noexcept;
    void open(std::string file);
    void play(int times = -1);
    void stop(unsigned int fade_out_duration_milliseconds = 1500);

  // Private components.
  private:

    // Members.
    MixMusicUniquePTR music = MixMusicUniquePTR(nullptr, &Mix_FreeMusic);
    bool usingMixer = false;

    // Method prototypes.
    bool mixerInUse() const noexcept;
    int useMixerToPlayCurrentMusic(int times) const noexcept;
    int useMixerToStopCurrentMusic(
      unsigned int fade_out_duration_milliseconds
    ) const noexcept;
};

#endif // MUSIC_H_
