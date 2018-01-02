#include "visualable.h"

Visualable::Visualable(const std::string& name)
	: name_(name){ }

Visualable::~Visualable() { }

const std::string &Visualable::Name() const {
	return name_;
}