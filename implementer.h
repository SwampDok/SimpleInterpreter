#ifndef IMPLEMENTER_H
#define IMPLEMENTER_H

#include <QVector>
#include <QString>

#include "parser.h"

/*
 * 2016 (c) Swamp_Dok
 * Класс реализующий выполнение дерева выражений
 *
 */
class Implementer
{
	// Список всех найденных переменных без повторений
	QVector<Identifier> ids_;
	// Объект класса парсер
	Parser *pars_;

	// Метод служит для рекурсивной обработки деревьев
	// Флаг = 0 - выражение вышло из правой ячейки родителя
	// Флаг = 1 - выражение вышло из правой ячейки родителя
	void Run (TreeCell *cell, bool flag);
public:
	Implementer ();
	Implementer (Parser *pars);

	// Добавляет идентификатор без повторений
	bool AddId (const QString &name, int value);

	// Очистить список переменных
	void ClearIds ();

	// Выполняет все деревья
	void Run();

	// Выполняет указанное дерево
	void Run (int number_line);

	bool IdExists (const QString &name);

	// False, если переменная не найдена
	bool set_value (const QString &name, int value);

	bool set_parser (Parser *pars);

	// Возвращает список идентификаторов
	const QVector<Identifier>* get_ids ();

	// Возвращает указатель на идентификатор
	const Identifier* get_id (int id);

	// Возвращает значение идентификатора по имени
	// Если такого идентификатора нет, то возвращает -1
	int get_value (const QString &name);

	// Возвращает количество идентификаторов
	int get_count_ids ();
};

#endif // IMPLEMENTER_H
