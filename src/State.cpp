// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - State class - Source code.

// Class header include.
#include "State.hpp"

// Class method implementations.
State::State(SDL_Renderer* renderer) try :
  music("./assets/audio/stage_state.ogg")
{
	try {
		this->addBackgroundGameObject(renderer, "./assets/img/ocean.jpg");
	}
	catch(std::exception& e) {
		throw;
	}

  this->playMusic();
}
catch(std::exception& e) {
  throw;
};

// Public method implementations.
void State::loadAssets() {};

void State::processInput() {
  SDL_Event event;

	while (SDL_PollEvent(&event))
		this->handleEvent(event);
};

bool State::quitRequested() const {
  return this->quit_requested;
};

void State::render(SDL_Renderer* renderer) {
  for(auto& game_object : this->objectArray)
    game_object->render(renderer);
};

void State::update(double dt) {
	this->processInput();
	this->updateGameObjects(dt);
	this->removeDeadGameObjects();
};

// Private method implementations.
void State::addBackgroundGameObject(
	SDL_Renderer* renderer,
	std::string file
) {
	GameObject *background_object = new GameObject();
	Sprite *background_sprite = new Sprite(*background_object, renderer, file);

	background_object->addComponent(background_sprite);
	this->addGameObject(background_object);
};

void State::addGameObject(GameObject* new_game_object) {
	this->objectArray.emplace_back(std::unique_ptr<GameObject>(new_game_object));
};

void State::handleEvent(SDL_Event& event) {
	VectorR2 mouse_coordinates = this->mouseCoordinates();

	switch (event.type) {
		case SDL_KEYDOWN:
			this->handleKeyDown(event.key.keysym);
			break;

		case SDL_MOUSEBUTTONDOWN:
			this->handleMouseButtonDown(mouse_coordinates);
			break;

		case SDL_QUIT:
			this->quit_requested = true;
			break;
	}
};

void State::handleKeyDown(SDL_Keysym& keysym) {
	switch (keysym.sym) {
		case SDLK_ESCAPE:
			this->quit_requested = true;
			break;
	}
};

void State::handleMouseButtonDown(VectorR2& mouse_coordinates) {};

VectorR2 State::mouseCoordinates() const {
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);

	return VectorR2((double) mouseX, (double) mouseY);
};

bool State::musicIsUsingMixer() const {
  return this->music.isUsingMixer();
};

void State::playMusic() {
  try {
    this->music.play();
  }
  catch(PlayMusicException& play_music_exception) {
    std::cerr << "[State] " << play_music_exception.what();
    std::cerr << "[State] Ignoring last exception and resuming execution!\n";
  }
};

void State::removeDeadGameObjects() {
	unsigned int index = 0;

	// Use numerical indexes because vector might change with removals.
	while(index < this->objectArray.size()) {
		if(this->objectArray[index]->isDead())
			this->removeGameObjectAt(index);
		else
			index++;
	}
};

void State::removeGameObjectAt(size_t index) {
	if(index < this->objectArray.size())
		this->objectArray.erase(std::next(this->objectArray.begin(), index));
};

void State::stopMusic() {
  try {
    this->music.stop();
  }
  catch(StopMusicException& stop_music_exception) {
    std::cerr << "[State] " << stop_music_exception.what();
    std::cerr << "[State] Ignoring last exception and resuming execution!\n";
  }
};

void State::updateGameObjects(double dt) {
	// Use numerical indexes because vector might change with updates.
	for(unsigned int i = 0; i < this->objectArray.size(); i++)
		this->objectArray[i]->update(dt);
};
