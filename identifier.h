#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <QString>

/* Класс реализует контейнер для хранения переменных
 *
 */
class Identifier
{
	QString name_;
	int value_;

public:

	Identifier (const QString &name, int value = 0);

	QString get_name () const;
	int get_value () const;

	void set_value (int value);
	void set_name (const QString &name);
};

#endif // IDENTIFIER_H
