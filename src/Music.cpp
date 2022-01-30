// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Music class - Source code.

// Class header include.
#include "Music.hpp"

// Class method implementations.
Music::Music(string file) {
  this->open(file);
};

OpenMusicException::OpenMusicException(
  OpenMusicErrorCode error_code
) :
  OpenMusicErrorDescription(error_code),
  runtime_error(this->describeError(error_code)) {};

PlayMusicException::PlayMusicException(
  PlayMusicErrorCode error_code
) :
  PlayMusicErrorDescription(error_code),
  runtime_error(this->describeError(error_code)) {};

StopMusicException::StopMusicException(
  StopMusicErrorCode error_code
) :
  StopMusicErrorDescription(error_code),
  runtime_error(this->describeError(error_code)) {};

// Public method implementations.
bool Music::isOpen() {
  return (this->music.get() != nullptr);
};

bool Music::isUsingMixer() {
  return this->usingMixer;
}

void Music::open(string file) {
  this->music.reset(Mix_LoadMUS(file.c_str()));

  if(this->music.get() == nullptr)
    throw OpenMusicException(OpenMusicErrorCode::LoadMusicError);
};

void Music::play(int repetitions) {
  if(!this->isOpen())
    throw PlayMusicException(PlayMusicErrorCode::PlayUnopenedMusicError);

  else if(this->isUsingMixer())
    throw PlayMusicException(PlayMusicErrorCode::MusicAlreadyPlayingError);

  else if(this->mixerInUse())
    throw PlayMusicException(PlayMusicErrorCode::MixerInUseError);

  else if(this->playCurrentMusic(repetitions) != 0)
    throw PlayMusicException(PlayMusicErrorCode::FailureToPlayMusicError);
};

void Music::stop(unsigned int fade_out_duration_milliseconds) {
  if(!this->isOpen())
    throw StopMusicException(StopMusicErrorCode::StopUnopenedMusicError);

  else if(!this->isUsingMixer())
    throw StopMusicException(StopMusicErrorCode::MusicNotPlayedError);

  else if(!this->mixerInUse())
    throw StopMusicException(StopMusicErrorCode::MixerNotInUseError);

  else if(this->stopCurrentMusic(fade_out_duration_milliseconds) != 0)
    throw StopMusicException(StopMusicErrorCode::FailureToStopMusicError);
};

// Private method implementations.
bool Music::mixerInUse() {
  return (Mix_PlayingMusic() && Mix_FadingMusic() != MIX_FADING_OUT);
};

int Music::playCurrentMusic(int repetitions) {
  if(Mix_PlayMusic(this->music.get(), repetitions) != 0)
    return -1;

  this->usingMixer = true;
  return 0;
};

int Music::stopCurrentMusic(unsigned int fade_out_duration_milliseconds) {
  if(Mix_FadeOutMusic(fade_out_duration_milliseconds) != 0)
    return -1;

  this->usingMixer = false;
  return 0;
};

string OpenMusicErrorDescription::describeErrorCause(
  OpenMusicErrorCode error_code
) {
  string error_cause = string("This error was caused by ");

  switch (error_code) {
    case LoadMusicError:
      error_cause += "attempting to load the music from the file system";
      break;
  }

  error_cause += ".";

  return error_cause;
};

string OpenMusicErrorDescription::describeErrorDetails(
  OpenMusicErrorCode error_code
) {
  string error_details;

  switch (error_code) {
    default:
      error_details += Mix_GetError();
  }

  error_details += ".";

  return error_details;
};

string OpenMusicErrorDescription::describeErrorSummary() {
  string error_summary = string(
    "OpenMusicError: An error occurred when opening a music track!"
  );

  return error_summary;
};

string PlayMusicErrorDescription::describeErrorCause(
  PlayMusicErrorCode error_code
) {
  string error_cause = string("This error was caused by ");

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
      error_cause += "a failure to play a music track";
      break;
  }

  error_cause += ".";

  return error_cause;
};

string PlayMusicErrorDescription::describeErrorDetails(
  PlayMusicErrorCode error_code
) {
  string error_details;

  switch (error_code) {
    default:
      error_details += Mix_GetError();
  }

  error_details += ".";

  return error_details;
};

string PlayMusicErrorDescription::describeErrorSummary() {
  string error_summary = string(
    "PlayMusicError: An error occurred when playing a music track!"
  );

  return error_summary;
};

string StopMusicErrorDescription::describeErrorCause(
  StopMusicErrorCode error_code
) {
  string error_cause = string("This error was caused by ");

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
      error_cause += "a failure to stop a music track";
      break;
  }

  error_cause += ".";

  return error_cause;
};

string StopMusicErrorDescription::describeErrorDetails(
  StopMusicErrorCode error_code
) {
  string error_details;

  switch (error_code) {
    default:
      error_details += Mix_GetError();
  }

  error_details += ".";

  return error_details;
};

string StopMusicErrorDescription::describeErrorSummary() {
  string error_summary = string(
    "StopMusicError: An error occurred when stopping a music track!"
  );

  return error_summary;
};
