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
    throw OpenMusicException(OpenMusicErrorCode::LoadMusicError);
};

void Music::play(int times) {
  if(!this->isOpen())
    throw PlayMusicException(PlayMusicErrorCode::PlayUnopenedMusicError);

  else if(this->isUsingMixer())
    throw PlayMusicException(PlayMusicErrorCode::MusicAlreadyPlayingError);

  else if(this->mixerInUse())
    throw PlayMusicException(PlayMusicErrorCode::MixerInUseError);

  else if(this->useMixerToPlayCurrentMusic(times) != 0)
    throw PlayMusicException(PlayMusicErrorCode::FailureToPlayMusicError);
};

void Music::stop(unsigned int fade_out_duration_milliseconds) {
  if(!this->isOpen())
    throw StopMusicException(StopMusicErrorCode::StopUnopenedMusicError);

  else if(!this->isUsingMixer())
    throw StopMusicException(StopMusicErrorCode::MusicNotPlayedError);

  else if(!this->mixerInUse())
    throw StopMusicException(StopMusicErrorCode::MixerNotInUseError);

  else if(this->useMixerToStopCurrentMusic(fade_out_duration_milliseconds) != 0)
    throw StopMusicException(StopMusicErrorCode::FailureToStopMusicError);
};

std::string OpenMusicErrorDescription::describeErrorCause(
  OpenMusicErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");

  switch (error_code) {
    case LoadMusicError:
      error_cause += "attempting to load the music from the file system";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string OpenMusicErrorDescription::describeErrorDetails(
  OpenMusicErrorCode error_code
) const noexcept {
  std::string error_details;

  switch (error_code) {
    default:
      error_details += Mix_GetError();
  }

  error_details += ".";

  return error_details;
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
    case PlayMusicErrorCode::PlayUnopenedMusicError:
      error_cause += "attempting to play a music track that was not opened";
      break;
    case PlayMusicErrorCode::MusicAlreadyPlayingError:
      error_cause += "attempting to play a music track that is already "
        "playing";
      break;
    case PlayMusicErrorCode::MixerInUseError:
      error_cause += "attempting to use the mixer to play a music track when "
        "another track is already playing";
      break;
    case PlayMusicErrorCode::FailureToPlayMusicError:
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
    default:
      error_details += Mix_GetError();
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
    case StopMusicErrorCode::StopUnopenedMusicError:
      error_cause += "attempting to stop a music track that was not opened";
      break;
    case StopMusicErrorCode::MusicNotPlayedError:
      error_cause += "attempting to stop a music track that was not played";
      break;
    case StopMusicErrorCode::MixerNotInUseError:
      error_cause += "attempting to use the mixer to stop a music track when "
        "no track is playing";
      break;
    case StopMusicErrorCode::FailureToStopMusicError:
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
    default:
      error_details += Mix_GetError();
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
  return (Mix_PlayingMusic() && Mix_FadingMusic() != MIX_FADING_OUT);
};

int Music::useMixerToPlayCurrentMusic(int times) noexcept {
  if(Mix_PlayMusic(this->music.get(), times) != 0)
    return -1;

  this->usingMixer = true;
  return 0;
};

int Music::useMixerToStopCurrentMusic(
  unsigned int fade_out_duration_milliseconds
) noexcept {
  if(Mix_FadeOutMusic(fade_out_duration_milliseconds) != 0)
    return -1;

  this->usingMixer = false;
  return 0;
};
