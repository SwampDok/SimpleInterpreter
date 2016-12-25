#include "identifier.h"

Identifier::Identifier(const QString &name, int value) :
  name_(name), value_(value) {}


QString Identifier::get_name () const {
	return name_;
}

int Identifier::get_value () const {
	return value_;
}

void Identifier::set_name (const QString &name) {
	name_ = name;
}

void Identifier::set_value (int value) {
	value_ = value;
}
