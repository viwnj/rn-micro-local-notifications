#include "Container.h"

Container::Container() : Container(Position(0, 0), Dimension(0, 0)) {}

Container::Container(Position pos) : Container(pos, Dimension(0, 0)) {}

Container::Container(Position pos, Dimension dim) : position(pos), dimension(dim) {
	// TODO: compute real dimension
}

void Container::append_child(Container* container) {
	// TODO: do less copies of container
	container->setPosition(container->position + this->position);
	this->children.emplace_back(container);
}

void Container::setPosition(Position p) {
	this->position = p;
}

Position Container::getPosition() {
	return this->position;
}

Dimension Container::getDimension() {
	return this->dimension;
}

void Container::setParent(Container* parent) {
	this->parent = parent;
}

void Container::remove_child() {}

void Container::set_display_mode(std::string& display_mode) {}

void Container::render() {
	for (Container* c : this->children) {
		c->render();
	}
}