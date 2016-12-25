#include "expression.h"

Expression::Expression() {}

Expression::Expression (const QVector<QString> &tokens) {
	Token token;

	for (int i = 0; i < tokens.size (); ++i) {
		token.set_value (tokens[i]);
		tokens_.push_back (token);
	}
}

Expression::Expression (const QVector<Token> &tokens) {
	tokens_ << tokens;
}

int Expression::get_size () {
	return tokens_.size ();
}

Token Expression::get_token (int id) {
	return tokens_[id];
}

QString Expression::get_string_token (int id) {
	return tokens_[id].get_value ();
}

void Expression::AddToken (const QString &value) {
	Token token (value);
	tokens_.push_back (token);
}

void Expression::AddToken (const Token &token) {
	tokens_.push_back (token);
}

void Expression::AddToken (const QString &value,
                           bool constant,
                           bool identifir) {
	Token token (value, constant, identifir);
	tokens_.push_back (token);
}


