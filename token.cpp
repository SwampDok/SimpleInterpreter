#include "token.h"

Token::Token () {
	value_ = "";
	constant_ = false;
	identifir_ = false;
}

Token::Token (const QString &value) :
  value_(value), constant_(false), identifir_(false) {}

Token::Token (const QString &value, bool constant, bool identifir) :
  value_(value) {

	// Можно все ифы заменить одним логическим выражанием, но так нагляднее
	if (constant) {
		constant_ = true;
		identifir_ = false;
		return;
	}

	if (identifir) {
		constant_ = false;
		identifir_ = true;
		return;
	}

	constant_ = false;
	identifir_ = false;
}

Token::Token (const Token &token) :
  value_(token.get_value ()), constant_ (token.IsConstant ()), identifir_(token.IsIdentifir ()) {}

bool Token::IsConstant () const{
	return constant_;
}


bool Token::IsIdentifir () const{
	return identifir_;
}

QString Token::get_value () const{
	return value_;
}

void Token::set_value (const QString &value) {
	value_ = value;
}

void Token::set_constant (bool constant) {
	if (constant) {
		constant_ = true;
		identifir_ = false;
	}
}

void Token::set_identifir (bool identifir) {
	if (identifir) {
		constant_ = false;
		identifir_ = true;
	}
}
