// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Music class - Source code.

// Class header include.
#include "Music.hpp"

// Class method implementations.
Music::Music(std::string file) {
  this->open(file);
};

// Public method implementations.
bool Music::isOpen() const noexcept {
  return (this->music.get() != nullptr);
};

bool Music::isUsingMixer() const noexcept {
  return this->usingMixer;
};

void Music::open(std::string file) {
  this->music.reset(Mix_LoadMUS(file.c_str()));

  if(!this->music)
    throw OpenMusicException(OpenMusicErrorCode::FailureToLoadMusic);
};

void Music::play(int times) {
  if(!this->isOpen())
    throw PlayMusicException(PlayMusicErrorCode::PlayedUnopenedMusic);

  if(this->isUsingMixer())
    throw PlayMusicException(PlayMusicErrorCode::InvalidPlayCommand);

  if(this->mixerInUse())
    throw PlayMusicException(PlayMusicErrorCode::MixerInUse);

  if(this->useMixerToPlayCurrentMusic(times) != 0)
    throw PlayMusicException(PlayMusicErrorCode::FailureToPlayMusic);

  this->usingMixer = true;
};

void Music::stop(unsigned int fade_out_duration_milliseconds) {
  if(!this->isOpen())
    throw StopMusicException(StopMusicErrorCode::StoppedUnopenedMusic);

  if(!this->isUsingMixer())
    throw StopMusicException(StopMusicErrorCode::StoppedUnplayedMusic);

  if(
    this->mixerInUse() &&
    this->useMixerToStopCurrentMusic(fade_out_duration_milliseconds) != 0
  )
    throw StopMusicException(StopMusicErrorCode::FailureToStopMusic);

  this->usingMixer = false;
};

std::string OpenMusicErrorDescription::describeErrorCause(
  OpenMusicErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");

  switch (error_code) {
    case FailureToLoadMusic:
      error_cause += "attempting to load the music from the file system";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string OpenMusicErrorDescription::describeErrorSummary() const noexcept {
  std::string error_summary = std::string(
    "OpenMusicError: An error occurred when opening a music track!"
  );

  return error_summary;
};

std::string PlayMusicErrorDescription::describeErrorCause(
  PlayMusicErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");

  switch (error_code) {
    case PlayMusicErrorCode::PlayedUnopenedMusic:
      error_cause += "playing a music track that was not opened";
      break;

    case PlayMusicErrorCode::InvalidPlayCommand:
      error_cause += "issuing a play command for a music track that was "
        "already played but not stopped afterwards";
      break;

    case PlayMusicErrorCode::MixerInUse:
      error_cause += "attempting to use the mixer to play a music track when "
        "another track is already playing in the mixer";
      break;

    case PlayMusicErrorCode::FailureToPlayMusic:
      error_cause += "a failure to play a music track with the mixer";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string PlayMusicErrorDescription::describeErrorDetails(
  PlayMusicErrorCode error_code
) const noexcept {
    std::string error_details;

  switch (error_code) {
    case PlayMusicErrorCode::PlayedUnopenedMusic:
      error_details += "The music track to be played must have an open file "
        "pointer that is not NULL";
      break;

    case PlayMusicErrorCode::InvalidPlayCommand:
      error_details += "The music track to be played must be properly stopped "
        "before it can be played again";
      break;

    case PlayMusicErrorCode::MixerInUse:
      error_details += "There can be no music track playing in the mixer for "
        "another music track to start playing";
      break;

    case PlayMusicErrorCode::FailureToPlayMusic:
      error_details += SDL_GetError();
      break;
  }

  error_details += ".";

  return error_details;
};

std::string PlayMusicErrorDescription::describeErrorSummary() const noexcept {
  std::string error_summary = std::string(
    "PlayMusicError: An error occurred when playing a music track!"
  );

  return error_summary;
};

std::string StopMusicErrorDescription::describeErrorCause(
  StopMusicErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");

  switch (error_code) {
    case StopMusicErrorCode::StoppedUnopenedMusic:
      error_cause += "stopping a music track that was not opened";
      break;

    case StopMusicErrorCode::StoppedUnplayedMusic:
      error_cause += "stopping a music track that was not played";
      break;

    case StopMusicErrorCode::FailureToStopMusic:
      error_cause += "a failure to stop a music track with the mixer";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string StopMusicErrorDescription::describeErrorDetails(
  StopMusicErrorCode error_code
) const noexcept {
    std::string error_details;

  switch (error_code) {
    case StopMusicErrorCode::StoppedUnopenedMusic:
      error_details += "The music track to be stopped must have an open file "
        "pointer that is not NULL";
      break;

    case StopMusicErrorCode::StoppedUnplayedMusic:
      error_details += "The music track to be stopped must be have been "
        "played before it can be stopped";
      break;

    case StopMusicErrorCode::FailureToStopMusic:
      error_details += SDL_GetError();
      break;
  }

  error_details += ".";

  return error_details;
};

std::string StopMusicErrorDescription::describeErrorSummary() const noexcept {
  std::string error_summary = std::string(
    "StopMusicError: An error occurred when stopping a music track!"
  );

  return error_summary;
};

// Private method implementations.
bool Music::mixerInUse() const noexcept {
  return (Mix_PlayingMusic() == 1 && Mix_FadingMusic() != MIX_FADING_OUT);
};

int Music::useMixerToPlayCurrentMusic(int times) const noexcept {
  if(Mix_PlayMusic(this->music.get(), times) != 0)
    return -1;

  return 0;
};

int Music::useMixerToStopCurrentMusic(
  unsigned int fade_out_duration_milliseconds
) const noexcept {
  if(Mix_FadeOutMusic(fade_out_duration_milliseconds) != 0)
    return -1;

  return 0;
};
