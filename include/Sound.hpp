// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sound class - Header file.

// Define guard.
#ifndef SOUND_H_
#define SOUND_H_

// Includes.
#include <string>

// SDL2 includes.
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>

// User includes.
#include "GameObject.hpp"

// Template includes.
#include "templates/ErrorDescription.hpp"
#include "templates/RuntimeException.hpp"

// Declarations.
enum OpenSoundErrorCode : unsigned short;
class OpenSoundErrorDescription;
class OpenSoundException;
enum PlaySoundErrorCode : unsigned short;
class PlaySoundErrorDescription;
class PlaySoundException;
class Sound;
enum StopSoundErrorCode : unsigned short;
class StopSoundErrorDescription;
class StopSoundException;

// Enumeration definitions.
enum OpenSoundErrorCode : unsigned short {
  LoadSoundError = 1
};

enum PlaySoundErrorCode : unsigned short {
  PlayUnopenedSoundError = 1,
  SoundAlreadyPlayingError,
  FailureToPlaySoundError
};

enum StopSoundErrorCode : unsigned short {
  StopUnopenedSoundError = 1,
  NoChannelReservedError
};

// Auxiliary class definitions.
class OpenSoundErrorDescription : public ErrorDescription<OpenSoundErrorCode> {
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      OpenSoundErrorCode error_code
    ) const override;
    std::string describeErrorDetails(
      OpenSoundErrorCode error_code
    ) const override;
    std::string describeErrorSummary() const override;
};

class PlaySoundErrorDescription : public ErrorDescription<PlaySoundErrorCode> {
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      PlaySoundErrorCode error_code
    ) const override;
    std::string describeErrorDetails(
      PlaySoundErrorCode error_code
    ) const override;
    std::string describeErrorSummary() const override;
};

class StopSoundErrorDescription : public ErrorDescription<StopSoundErrorCode> {
  // Public components.
  public:

    // Inherited methods.
    using ErrorDescription::ErrorDescription;

    // Method prototypes.
    std::string describeErrorCause(
      StopSoundErrorCode error_code
    ) const override;
    std::string describeErrorDetails(
      StopSoundErrorCode error_code
    ) const override;
    std::string describeErrorSummary() const override;
};

// Exception definitions.
class OpenSoundException :
  public RuntimeException<OpenSoundErrorCode, OpenSoundErrorDescription>
{
    // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};

class PlaySoundException :
  public RuntimeException<PlaySoundErrorCode, PlaySoundErrorDescription>
{
    // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};


class StopSoundException :
  public RuntimeException<StopSoundErrorCode, StopSoundErrorDescription>
{
    // Public components.
  public:

    // Inherited methods.
    using RuntimeException::RuntimeException;
};

// Class definition.
class Sound : public Component {
  // Public components.
  public:

    // Class method prototypes.
    Sound(GameObject& associated);
    Sound(GameObject& associated, std::string file);
    ~Sound();

    // Method prototypes.
    bool hasReservedChannel() const;
    bool isOpen() const;
    void open(std::string file);
    void play(int loops_after_first_time_played = 0);
    void render(SDL_Renderer* renderer) override;
    void stop();
    void update(double dt) override;

  // Private components.
  private:

    // Class method prototypes.
    Sound(const Sound&) = delete;

    // Default operator overloadings.
    Sound& operator = (const Sound&) = delete;

    // Members.
    int channel = -1;
    bool has_reserved_channel = false;
    Mix_Chunk* sound = nullptr;

    // Method prototypes.
    void cleanUpCurrentSound();
    int loadSoundFile(std::string file);
    int playCurrentSoundWithMixer(int loops_after_first_time_played);
    bool reservedChannelHasNotBeenReassigned() const;
    bool reservedChannelIsInUse() const;
    bool soundIsPlaying() const;
    void stopSoundCurrentlyPlaying();
    void stopSoundOnReservedChannel();
};

#endif // SOUND_H_
