// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sound class - Source code.

// Class header include.
#include "Sound.hpp"

// Class method implementations.
Sound::Sound(
  GameObject& associated
) : Component(associated, ComponentType::SoundComponent) {};

Sound::Sound(
  GameObject& associated,
  std::string file
) : Sound(associated) {
  this->open(file);
};

Sound::~Sound() {
  this->stopSoundCurrentlyPlaying();
  this->cleanUpCurrentSound();
}

// Public method implementations.
std::string OpenSoundErrorDescription::describeErrorCause(
  OpenSoundErrorCode error_code
) const {
  std::string error_cause = std::string("This error was caused by ");

  switch (error_code) {
    case LoadSoundError:
      error_cause += "attempting to load the sound asset from the file system";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string OpenSoundErrorDescription::describeErrorDetails(
  OpenSoundErrorCode error_code
) const {
  std::string error_details;

  switch (error_code) {
    default:
      error_details += Mix_GetError();
  }

  error_details += ".";

  return error_details;
};

std::string OpenSoundErrorDescription::describeErrorSummary() const {
  std::string error_summary = std::string(
    "OpenSoundError: An error occurred when opening a sound asset!"
  );

  return error_summary;
};

std::string PlaySoundErrorDescription::describeErrorCause(
  PlaySoundErrorCode error_code
) const {
  std::string error_cause = std::string("This error was caused by ");

  switch (error_code) {
    case PlaySoundErrorCode::PlayUnopenedSoundError:
      error_cause += "attempting to play a sound asset that was not opened";
      break;
    case PlaySoundErrorCode::SoundAlreadyPlayingError:
      error_cause += "attempting to play a sound asset that is already "
        "playing";
      break;
    case PlaySoundErrorCode::FailureToPlaySoundError:
      error_cause += "a failure to play a sound asset with the mixer channels";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string PlaySoundErrorDescription::describeErrorDetails(
  PlaySoundErrorCode error_code
) const {
  std::string error_details;

  switch (error_code) {
    default:
      error_details += Mix_GetError();
  }

  error_details += ".";

  return error_details;
};

std::string PlaySoundErrorDescription::describeErrorSummary() const {
  std::string error_summary = std::string(
    "PlaySoundError: An error occurred when playing a sound asset!"
  );

  return error_summary;
};

bool Sound::hasReservedChannel() const {
  return this->has_reserved_channel;
};

bool Sound::isOpen() const {
  return this->sound != nullptr;
};

void Sound::open(std::string file) {
  this->cleanUpCurrentSound();

  if(this->loadSoundFile(file) != 0)
    throw OpenSoundException(OpenSoundErrorCode::LoadSoundError);
};

void Sound::play(int loops_after_first_time_played) {
  if(!this->isOpen())
    throw PlaySoundException(PlaySoundErrorCode::PlayUnopenedSoundError);

  else if(this->soundIsPlaying())
    throw PlaySoundException(PlaySoundErrorCode::SoundAlreadyPlayingError);

  else if(this->playCurrentSoundWithMixer(loops_after_first_time_played) != 0)
    throw PlaySoundException(PlaySoundErrorCode::FailureToPlaySoundError);
};

void Sound::render(SDL_Renderer* renderer) {};

void Sound::stop() {
  if(!this->isOpen())
    throw StopSoundException(StopSoundErrorCode::StopUnopenedSoundError);

  else if(!this->hasReservedChannel())
    throw StopSoundException(StopSoundErrorCode::NoChannelReservedError);

  else if(this->soundIsPlaying())
    this->stopSoundCurrentlyPlaying();
};

void Sound::update(double dt) {};

std::string StopSoundErrorDescription::describeErrorCause(
  StopSoundErrorCode error_code
) const {
  std::string error_cause = std::string("This error was caused by ");

  switch (error_code) {
    case StopSoundErrorCode::StopUnopenedSoundError:
      error_cause += "attempting to stop a sound asset that was not opened";
      break;
    case StopSoundErrorCode::NoChannelReservedError:
      error_cause += "attempting to stop a sound asset that did not reserve "
        "a sound channel to play on";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string StopSoundErrorDescription::describeErrorDetails(
  StopSoundErrorCode error_code
) const {
  std::string error_details;

  switch (error_code) {
    default:
      error_details += Mix_GetError();
  }

  error_details += ".";

  return error_details;
};

std::string StopSoundErrorDescription::describeErrorSummary() const {
  std::string error_summary = std::string(
    "StopSoundError: An error occurred when stopping a sound asset!"
  );

  return error_summary;
};

// Private method implementations.
void Sound::cleanUpCurrentSound() {
  if(this->isOpen()) {
    Mix_FreeChunk(this->sound);
    this->sound = nullptr;
  }
};

int Sound::loadSoundFile(std::string file) {
  this->sound = Mix_LoadWAV(file.c_str());

  if(this->sound != nullptr)
    return 0;

  else
    return -1;
};

int Sound::playCurrentSoundWithMixer(int loops_after_first_time_played) {
  int auto_assign_channel = -1, assigned_channel;
  
  assigned_channel = Mix_PlayChannel(
    auto_assign_channel,
    this->sound,
    loops_after_first_time_played
  );

  if(assigned_channel == -1)
    return -1;

  this->channel = assigned_channel;
  return 0;
};

bool Sound::reservedChannelHasNotBeenReassigned() const {
  return (
    this->isOpen() &&
    this->hasReservedChannel() &&
    Mix_GetChunk(this->channel) == this->sound
  );
};

bool Sound::reservedChannelIsInUse() const {
  return (this->hasReservedChannel() && Mix_Playing(this->channel));
};

bool Sound::soundIsPlaying() const {
  return (
    this->isOpen() &&
    this->hasReservedChannel() &&
    this->reservedChannelIsInUse() &&
    this->reservedChannelHasNotBeenReassigned()
  );
};

void Sound::stopSoundCurrentlyPlaying() {
  if(this->soundIsPlaying())
    this->stopSoundOnReservedChannel();
};

void Sound::stopSoundOnReservedChannel() {
  Mix_HaltChannel(this->channel);
  this->channel = -1;
  this->has_reserved_channel = false;
};
