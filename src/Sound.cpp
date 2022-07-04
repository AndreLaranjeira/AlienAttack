// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Sound class - Source code.

// Class header include.
#include "Sound.hpp"

// Class method implementations.
Sound::Sound(
  GameObject& associated
) : Component(associated, ComponentType::SoundComponent) {
  this->attachToAssociatedGameObject();
};

Sound::Sound(
  GameObject& associated,
  std::string file
) : Component(associated, ComponentType::SoundComponent) {
  this->open(file);
  this->attachToAssociatedGameObject();
};

Sound::~Sound() noexcept {
  this->stopSoundCurrentlyPlaying();
  this->cleanUpCurrentSound();
}

// Public method implementations.
std::string OpenSoundErrorDescription::describeErrorCause(
  OpenSoundErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");

  switch (error_code) {
    case FailureToLoadSound:
      error_cause += "attempting to load the sound asset from the file system";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string OpenSoundErrorDescription::describeErrorSummary() const noexcept {
  std::string error_summary = std::string(
    "OpenSoundError: An error occurred when opening a sound asset!"
  );

  return error_summary;
};

std::string PlaySoundErrorDescription::describeErrorCause(
  PlaySoundErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");

  switch (error_code) {
    case PlaySoundErrorCode::PlayedUnopenedSound:
      error_cause += "playing a sound asset that was not opened";
      break;

    case PlaySoundErrorCode::SoundAlreadyPlaying:
      error_cause += "attempting to play a sound asset that is already "
        "playing";
      break;

    case PlaySoundErrorCode::FailureToPlaySound:
      error_cause += "a failure to play a sound asset with the mixer channels";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string PlaySoundErrorDescription::describeErrorDetails(
  PlaySoundErrorCode error_code
) const noexcept {
    std::string error_details;

  switch (error_code) {
    case PlaySoundErrorCode::PlayedUnopenedSound:
      error_details += "The sound asset to be played must have an open file "
        "pointer that is not NULL";
      break;

    case PlaySoundErrorCode::SoundAlreadyPlaying:
      error_details += "The sound asset to be played must not be playing or "
        "must have finished playing";
      break;

    case PlaySoundErrorCode::FailureToPlaySound:
      error_details += SDL_GetError();
      break;
  }

  error_details += ".";

  return error_details;
};

std::string PlaySoundErrorDescription::describeErrorSummary() const noexcept {
  std::string error_summary = std::string(
    "PlaySoundError: An error occurred when playing a sound asset!"
  );

  return error_summary;
};

bool Sound::finishedPlaying() const noexcept {
  return (
    this->soundStartedPlaying() &&
    !this->soundIsPlaying()
  );
};

bool Sound::hasReservedChannel() const noexcept {
  return this->channel != -1;
};

bool Sound::isOpen() const noexcept {
  return this->sound != nullptr;
};

void Sound::open(std::string file) {
  this->cleanUpCurrentSound();

  if(this->loadSoundFile(file) != 0)
    throw OpenSoundException(OpenSoundErrorCode::FailureToLoadSound);
};

void Sound::play(int loops_after_first_time_played) {
  if(!this->isOpen())
    throw PlaySoundException(PlaySoundErrorCode::PlayedUnopenedSound);

  if(this->soundIsPlaying())
    throw PlaySoundException(PlaySoundErrorCode::SoundAlreadyPlaying);

  if(this->playCurrentSoundWithMixer(loops_after_first_time_played) != 0)
    throw PlaySoundException(PlaySoundErrorCode::FailureToPlaySound);
};

void Sound::render(SDL_Renderer* renderer) const noexcept {};

void Sound::stop() {
  if(!this->isOpen())
    throw StopSoundException(StopSoundErrorCode::StoppedUnopenedSound);

  if(!this->hasReservedChannel())
    throw StopSoundException(StopSoundErrorCode::NoReservedChannel);

  this->stopSoundCurrentlyPlaying();
};

void Sound::update(double dt) noexcept {};

std::string StopSoundErrorDescription::describeErrorCause(
  StopSoundErrorCode error_code
) const noexcept {
  std::string error_cause = std::string("This error was caused by ");

  switch (error_code) {
    case StopSoundErrorCode::StoppedUnopenedSound:
      error_cause += "stopping a sound asset that was not opened";
      break;

    case StopSoundErrorCode::NoReservedChannel:
      error_cause += "attempting to stop a sound asset without a reserved "
        "sound channel";
      break;
  }

  error_cause += ".";

  return error_cause;
};

std::string StopSoundErrorDescription::describeErrorDetails(
  StopSoundErrorCode error_code
) const noexcept {
    std::string error_details;

  switch (error_code) {
    case StopSoundErrorCode::StoppedUnopenedSound:
      error_details += "The sound asset to be stopped must have an open file "
        "pointer that is not NULL";
      break;

    case StopSoundErrorCode::NoReservedChannel:
      error_details += "The sound asset to be stopped must have been assigned "
        "a reserved channel (occurs when played) to be properly stopped";
      break;
  }

  error_details += ".";

  return error_details;
};

std::string StopSoundErrorDescription::describeErrorSummary() const noexcept {
  std::string error_summary = std::string(
    "StopSoundError: An error occurred when stopping a sound asset!"
  );

  return error_summary;
};

// Private method implementations.
void Sound::cleanUpCurrentSound() noexcept {
  if(this->isOpen()) {
    Mix_FreeChunk(this->sound);
    this->sound = nullptr;
  }
};

int Sound::loadSoundFile(std::string file) noexcept {
  this->sound = Mix_LoadWAV(file.c_str());

  if(this->sound != nullptr)
    return 0;

  else
    return -1;
};

int Sound::playCurrentSoundWithMixer(
  int loops_after_first_time_played
) noexcept {
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

bool Sound::reservedChannelHasNotBeenReassigned() const noexcept {
  return (
    this->hasReservedChannel() &&
    Mix_GetChunk(this->channel) == this->sound
  );
};

bool Sound::reservedChannelIsInUse() const noexcept {
  return (this->hasReservedChannel() && Mix_Playing(this->channel));
};

bool Sound::soundIsPlaying() const noexcept {
  return (
    this->soundStartedPlaying() &&
    this->reservedChannelIsInUse() &&
    this->reservedChannelHasNotBeenReassigned()
  );
};

bool Sound::soundStartedPlaying() const noexcept {
  return (
    this->isOpen() &&
    this->hasReservedChannel()
  );
};

void Sound::stopSoundCurrentlyPlaying() noexcept {
  if(this->soundIsPlaying())
    this->stopSoundOnReservedChannel();

  this->channel = -1;
};

void Sound::stopSoundOnReservedChannel() const noexcept {
  Mix_HaltChannel(this->channel);
};
