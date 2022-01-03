// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Music class - Source code.

// Class header include.
#include "Music.hpp"

// Class method implementations.
Music::Music() {};

Music::Music(string file) {
  this->open(file);
};

Music::~Music() {
  this->cleanUpCurrentMusic();
};

// Public method implementations.
bool Music::isOpen() {
  return (this->music != nullptr);
};

bool Music::isUsingMixer() {
  return this->usingMixer;
}

void Music::open(string file) {
  this->cleanUpCurrentMusic();
  this->openNewMusic(file);
};

void Music::play(int repetitions) {
  if(!this->isOpen())
    this->throwHandleMusicException(
      "This error was caused by attempting to play a music track that was not "
      "opened."
    );

  else if(this->isUsingMixer())
    this->throwHandleMusicException(
      "This error was caused by attempting to play a music track that is "
      "already playing."
    );

  else if(this->mixerInUse())
    this->throwHandleMusicException(
      "This error was caused by attempting to use the mixer to play a music "
      "track when another track is already playing."
    );

  else if(this->playCurrentMusic(repetitions) != 0)
    this->throwHandleMusicException(
      "This error was caused by a failure to play a music track."
    );
};

void Music::stop(unsigned int fade_out_duration_milliseconds) {
  if(!this->isOpen())
    this->throwHandleMusicException(
      "This error was caused by attempting to stop a music track that was not "
      "opened."
    );

  else if(!this->isUsingMixer())
    this->throwHandleMusicException(
      "This error was caused by attempting to stop a music track that was not "
      "played."
    );

  else if(!this->mixerInUse())
    this->throwHandleMusicException(
      "This error was caused by attempting to use the mixer to stop a music "
      "track when no track is playing."
    );

  else if(this->stopCurrentMusic(fade_out_duration_milliseconds) != 0)
    this->throwHandleMusicException(
      "This error was caused by a failure to stop a music track."
    );
};

// Private method implementations.
void Music::cleanUpCurrentMusic() {
  if(this->isOpen()) {
    Mix_FreeMusic(this->music);
    this->music = nullptr;
  }
};

string Music::formatMusicExceptionMessage(
  string exception_context,
  string exception_cause
) {
  string exception_msg;

  exception_msg = string("There was an error ");
  exception_msg += exception_context;
  exception_msg += "!";
  exception_msg += " ";
  exception_msg += exception_cause;
  exception_msg += " ";
  exception_msg += "More details: ";
  exception_msg += Mix_GetError();
  exception_msg += ".";
  exception_msg += "\n";

  return exception_msg;
};

bool Music::mixerInUse() {
  return (Mix_PlayingMusic() && Mix_FadingMusic() != MIX_FADING_OUT);
};

void Music::openNewMusic(string file) {
  this->music = Mix_LoadMUS(file.c_str());

  if(this->music == nullptr)
    this->throwOpenMusicException(
      "This error was caused by attempting to load the music from the file "
      "system!"
    );
};

int Music::playCurrentMusic(int repetitions) {
  if(Mix_PlayMusic(this->music, repetitions) != 0)
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

void Music::throwHandleMusicException(string error_description) {
  string exception_context = string("handling a music track");
  string exception_msg = formatMusicExceptionMessage(
    exception_context,
    error_description
  );
  
  throw runtime_error(exception_msg);
};

void Music::throwOpenMusicException(string error_description) {
  string exception_context = string("opening a music track");
  string exception_msg = formatMusicExceptionMessage(
    exception_context,
    error_description
  );
  
  throw runtime_error(exception_msg);
};