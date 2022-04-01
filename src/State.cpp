// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - State class - Source code.

// Class header include.
#include "State.hpp"

// Class method implementations.
State::State(SDL_Renderer* renderer) :
  music(STATE_MUSIC_FILE),
  renderer(renderer)
{
  this->addBackgroundGameObject({
    .sprite_file = BACKGROUND_SPRITE_FILE
  });
  this->playMusic();
};

// Public method implementations.
void State::loadAssets() {};

void State::processInput() {
  SDL_Event event;
  VectorR2 mouse_coordinates = this->mouseCoordinates();

  while(SDL_PollEvent(&event))
    this->handleEvent(event, mouse_coordinates);
};

bool State::quitRequested() const noexcept {
  return this->quit_requested;
};

void State::renderAndPresent() {
  SDL_RenderClear(this->renderer);
  this->renderGameObjects();
  SDL_RenderPresent(this->renderer);
};

void State::update(double dt) {
  this->processInput();
  this->updateGameObjects(dt);
  this->requestDeletionOfGameObjectsAptForDeletion();
  this->removeGameObjectsWhoseDeletionWasRequested();
};

// Private method implementations.
void State::addBackgroundGameObject(
  const BackgroundParams& background_params
) {
  GameObject *background_object = new GameObject();

  this->addGameObject(background_object);

  new Sprite(
    *background_object,
    this->renderer,
    background_params.sprite_file
  );
};

void State::addEnemyGameObject(const EnemyParams& enemy_params) {
  GameObject *enemy_object = new GameObject();
  
  this->addGameObject(enemy_object);

  new Face(*enemy_object);
  new Sound(*enemy_object, enemy_params.sound_file);
  new Sprite(*enemy_object, this->renderer, enemy_params.sprite_file);

  enemy_object->setCenterCoordinates(enemy_params.coordinates);
};

void State::addGameObject(GameObject* new_game_object) {
  this->objectArray.emplace_back(std::unique_ptr<GameObject>(new_game_object));
};

int State::applyDamageToGameObject(
  std::unique_ptr<GameObject>& damage_target,
  unsigned int damage
) {
  Face* target_face_component;

  if(!damage_target->hasComponentType(ComponentType::FaceComponent))
    return -1;

  target_face_component = static_cast<Face*>(
    damage_target->getComponent(ComponentType::FaceComponent)
  );
  target_face_component->registerDamage(damage);
  
  return 0;
};

game_object_iter State::convertReverseIterToIter(
  game_object_reverse_iter reverse_iterator
) const {
  return (reverse_iterator + 1).base();
};

bool State::gameObjectFinishedPlayingDeathSound(
  std::unique_ptr<GameObject>& game_object
) const noexcept {
  Sound* game_object_sound_component;

  if(game_object->hasComponentType(ComponentType::SoundComponent)) {
    game_object_sound_component = static_cast<Sound*>(
      game_object->getComponent(ComponentType::SoundComponent)
    );

    return game_object_sound_component->finishedPlaying();
  }

  else
    return true;
};

bool State::gameObjectIsAptForDeletion(
  std::unique_ptr<GameObject>& game_object
) const noexcept {
  return(
    game_object->getState() == GameObjectState::DeadState &&
    this->gameObjectFinishedPlayingDeathSound(game_object)
  );
};

void State::handleClickOnGameObject(game_object_iter target_iter) {
  if((*target_iter)->hasComponentType(ComponentType::FaceComponent))
    this->applyDamageToGameObject(
      *target_iter,
      100
    );
};

void State::handleEvent(
  const SDL_Event& event,
  const VectorR2& mouse_coordinates
) {
  switch (event.type) {
    case SDL_KEYDOWN:
      this->handleKeyDown(event.key.keysym, mouse_coordinates);
      break;

    case SDL_MOUSEBUTTONDOWN:
      this->handleMouseButtonDown(mouse_coordinates);
      break;

    case SDL_QUIT:
      this->quit_requested = true;
      break;
  }
};

void State::handleKeyDown(
  const SDL_Keysym& keysym,
  const VectorR2& mouse_coordinates
) {
  switch (keysym.sym) {
    case SDLK_e:
      this->addEnemyGameObject({
        .sprite_file = ENEMY_SPRITE_FILE,
        .sound_file = ENEMY_SOUND_FILE,
        .coordinates = mouse_coordinates
      });
      break;

    case SDLK_ESCAPE:
      this->quit_requested = true;
      break;
  }
};

void State::handleMouseButtonDown(const VectorR2& mouse_coordinates) {
  game_object_iter game_object_clicked_on;

  game_object_clicked_on = this->livingGameObjectWithLeastDepthLocatedAt(
    mouse_coordinates
  );
  
  this->handleClickOnGameObject(game_object_clicked_on);
};

game_object_iter State::livingGameObjectWithLeastDepthLocatedAt(
  const VectorR2& search_coordinates
) {
  game_object_reverse_iter search_result_reverse_iter;

  auto coordinates_are_inside_of_living_game_object = [&search_coordinates](
    const std::unique_ptr<GameObject>& game_object
  ) {
    return (
      game_object->isAlive() &&
      game_object->box.isReferenceInsideOfSelf(search_coordinates)
    );
  };

  search_result_reverse_iter = find_if(
    this->objectArray.rbegin(),
    this->objectArray.rend(),
    coordinates_are_inside_of_living_game_object
  );

  return this->convertReverseIterToIter(search_result_reverse_iter);
};

VectorR2 State::mouseCoordinates() const noexcept {
  int mouseX, mouseY;

  SDL_GetMouseState(&mouseX, &mouseY);

  return VectorR2((double) mouseX, (double) mouseY);
};

void State::playMusic() noexcept {
  try {
    this->music.play();
  }
  catch(PlayMusicException& play_music_exception) {
    std::cerr << "[State] " << play_music_exception.what();
    std::cerr << "[State] Ignoring last exception and resuming execution!\n";
  }
};

VectorR2 State::randomCoordinatesWithMagnitude(
  unsigned int coordinates_magnitude
) const noexcept {
  double random_angle = M_PI * (rand() % 2000)/1000.0;

  return VectorR2((int) coordinates_magnitude, 0)\
    .clockwiseRotatedVector(random_angle);
};

void State::removeGameObjectAt(size_t index) {
  if(index < this->objectArray.size())
    this->objectArray.erase(std::next(this->objectArray.begin(), index));
};

void State::removeGameObjectsWhoseDeletionWasRequested() {
  unsigned int index = 0;

  // Use numerical indexes because vector might change with removals.
  while(index < this->objectArray.size()) {
    if(this->objectArray[index]->deletionWasRequested())
      this->removeGameObjectAt(index);
    else
      index++;
  }
};

void State::renderGameObjects() {
  for(auto& game_object : this->objectArray)
    game_object->render(this->renderer);
};

void State::requestDeletionOfGameObjectsAptForDeletion() noexcept {
  for(auto& game_object : this->objectArray)
    if(this->gameObjectIsAptForDeletion(game_object))
      game_object->requestDeletion();
};

void State::stopMusic() noexcept {
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
