#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QVector>

#include "token.h"

class Expression
{
	QVector<Token> tokens_;
public:
	Expression ();

	Expression (const QVector<Token> &tokens);
	// Создается выражение из переданных слов
	// Параметры инициализируются нулям
	Expression (const QVector<QString> &tokens);

	// Удаляет все токены выражения
	void Clear ();

	int get_size();

	Token get_token (int id);

	QString get_string_token (int id);

	void set_token (int id, const QString &value, bool identifir, bool constant);

	void AddToken (const Token &token);

	void AddToken (const QString &value);

	void AddToken (const QString &value, bool constant, bool identifir);
};

#endif // EXPRESSION_H
