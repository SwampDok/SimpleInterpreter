#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <QString>

/* Класс реализует контейнер для хранения переменных
 *
 */
class Identifier
{
	// Имя переменной
	QString name_;
	// Значение переменной
	int value_;

public:
	Identifier ();
	Identifier (const QString &name);
	Identifier (const QString &name, int value);

	QString get_name () const;
	int get_value () const;

	void set_value (int value);
	void set_name (const QString &name);
};

#endif // IDENTIFIER_H
