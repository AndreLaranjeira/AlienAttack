// Copyright (c) 2021 André Filipe Caldas Laranjeira
// MIT License

// Alien Attack - Game Object class - Source code.

// Class header include.
#include "GameObject.hpp"

// Class method implementations.
Component::Component(GameObject& associated, ComponentType type) :
  associated(associated),
  type(type) {};

// Public method implementations.
bool Component::is(ComponentType type) const {
  return this->type == type;
};

void GameObject::addComponent(Component* new_component) {
  this->components.emplace_back(std::unique_ptr<Component>(new_component));
};

Component* GameObject::getComponent(ComponentType type) {
  component_const_iter result = this->searchComponentsByType(type);

  return result != this->components.end() ?
    result->get() :
    nullptr;
};

bool GameObject::isDead() const {
  return this->is_dead;
};

void GameObject::removeComponent(Component* removal_target) {
  component_const_iter removal_position = this->searchComponentsByValue(
    removal_target
  );

  if(removal_position != this->components.end())
    this->components.erase(removal_position);
};

void GameObject::render(SDL_Renderer* renderer) {
  for(auto& component : this->components)
    component->render(renderer);
};

void GameObject::requestDelete() {
  this->is_dead = true;
};

void GameObject::setDimensions(double width, double height) {
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
) const {
  auto component_type_matches_search_parameter = [&search_parameter](
    const std::unique_ptr<Component>& component
  ) {
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
) const {
  auto component_matches_search_parameter = [&search_parameter](
    const std::unique_ptr<Component>& component
  ) {
    return component.get() == search_parameter;
  };

  return find_if(
    this->components.begin(),
    this->components.end(),
    component_matches_search_parameter
  );
};
