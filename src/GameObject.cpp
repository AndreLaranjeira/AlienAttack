// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Game Object class - Source code.

// Class header include.
#include "GameObject.hpp"

// Class method implementations.
Component::Component(GameObject& associated, ComponentType type) noexcept :
  associated(associated),
  type(type) {};

// Public method implementations.
void Component::attachToAssociatedGameObject() {
  associated.addComponent(this);
};

bool Component::is(ComponentType type) const noexcept {
  return this->type == type;
};

void GameObject::addComponent(Component* new_component) {
  this->components.emplace_back(std::unique_ptr<Component>(new_component));
};

bool GameObject::deletionWasRequested() const noexcept {
  return this->state == DeletionState;
};

Component* GameObject::getComponent(ComponentType type) noexcept {
  component_const_iter result = this->searchComponentsByType(type);

  return result != this->components.end() ?
    result->get() :
    nullptr;
};

GameObjectState GameObject::getState() const noexcept {
  return this->state;
};

bool GameObject::hasComponentType(ComponentType type) const noexcept {
  return this->searchComponentsByType(type) != this->components.end();
};

bool GameObject::isAlive() const noexcept {
  return this->state == AliveState;
};

void GameObject::removeComponent(Component* removal_target) {
  component_const_iter removal_position = this->searchComponentsByValue(
    removal_target
  );

  if(removal_position != this->components.end())
    this->components.erase(removal_position);
};

void GameObject::removeComponent(ComponentType removal_target_type) {
  if(this->hasComponentType(removal_target_type))
    this->removeComponent(this->getComponent(removal_target_type));  
};

void GameObject::render(SDL_Renderer* renderer) {
  for(auto& component : this->components)
    component->render(renderer);
};

void GameObject::requestDeletion() noexcept {
  this->state = DeletionState;
};

void GameObject::resolveDeath() {
  this->state = DeadState;
  this->removeComponent(ComponentType::FaceComponent);
  this->removeComponent(ComponentType::SpriteComponent);
};

void GameObject::setCenterCoordinates(
  const VectorR2& center_coordinates
) noexcept {
  VectorR2 distance_from_upper_left_corner_to_center = VectorR2(
    this->box.width,
    this->box.height
  );

  this->box.upper_left_corner = \
    center_coordinates - distance_from_upper_left_corner_to_center;
};

void GameObject::setDimensions(double width, double height) noexcept {
  this->box.width = width;
  this->box.height = height;
};

void GameObject::update(double dt) {
  for(auto& component : this->components)
    component->update(dt);
};

// Private method implementations.
component_const_iter GameObject::searchComponentsByType(
  ComponentType search_parameter
) const noexcept {
  auto component_type_matches_search_parameter = [&search_parameter](
    const std::unique_ptr<Component>& component
  ) noexcept {
    return component->is(search_parameter);
  };

  return find_if(
    this->components.begin(),
    this->components.end(),
    component_type_matches_search_parameter
  );
};

component_const_iter GameObject::searchComponentsByValue(
  Component* search_parameter
) const noexcept {
  auto component_matches_search_parameter = [&search_parameter](
    const std::unique_ptr<Component>& component
  ) noexcept {
    return component.get() == search_parameter;
  };

  return find_if(
    this->components.begin(),
    this->components.end(),
    component_matches_search_parameter
  );
};
