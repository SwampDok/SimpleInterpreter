#ifndef TOKEN_H
#define TOKEN_H

#include<QString>

/* Данный класс реализует контейнер для хранения токенов/лексем программы
 *
 *
 */

class Token {
	// Хранит значение токена (лексемы) взятое из исходника
	QString value_;

	// True - лексема является константой (числом)
	bool constant_;

	// True - переменная является идентификатором
	bool identifir_;

public:

	Token ();

	Token (const QString &value);

	Token (const QString &value, bool constant, bool identifir);

	Token (const Token &token);

	bool IsIdentifir () const;

	bool IsConstant () const;

	void set_value (const QString &value);

	// Устанавливает, является ли токен идентификатором
	// Если ранее токен был константой, то флаг константы обнуляется
	// И наоборот
	void set_identifir (bool identifir);

	// Устанавливает, является ли токен константой
	void set_constant (bool constant);

	QString get_value () const;
};

#endif // TOKEN_H
