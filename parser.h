#ifndef PARSER_H
#define PARSER_H

#include <QVector>
#include <QString>

#include "treeexpressions.h"
#include "identifier.h"
#include "expression.h"

/* Данный класс отвечает за синтаксический разбор
 * и формирование деревьев выражений.
 * Тут же определяется синтаксис языка.
 * Желательно добавить возможность загружать синтаксис из вне.
 */
class Parser
{
	// Список все деревьев по количеству строк кода
	QVector<TreeExpressions> trees_;
	// Список всех найденных переменных без повторений
	QVector<Identifier> ids_;
	// Список токенов/лексем по строкам
	QVector<Expression> lines_;

	QStringList key_words = {"=", "+", "-", "*", "/"};

	// Метод создает ячейку дерева
	void CreateCell (TreeCell *root,
	                 Expression &expr,
	                 const QString &operation,
	                 int separator,
	                 TreeCell &first_cell);

	// В первой ячейке расположена операция присвоения
	// При первом вызове передать 0 и исходное выражение
	void Parsing(TreeCell *root, Expression &expr, TreeCell &first_cell);

public:
	Parser();

	// Разбивает исходный код по строкам и токенам/лексемам
	void LexicalAnalysis (const QString &source);

	// Метод создает список деревьев из входного текста
	// Каждая строка исходного кода - новое дерево
	// Все входные лексемы должны разделяться одним пробелом
	// Каждая строка должна завершаться переводом строки
	// Ака синтксический анализ
	// Возвращет 0, если список лексем пуст
	bool CreateTrees (int &incorrect_line);

	// Удаляет все деревья и переменные
	void Clear ();

	// Возвращает указатель на одно дерево
	// Номер дерева соответсвует номеру строки
	// Возвращает 0, если деревьев нет
	const TreeExpressions* get_tree (int id);

	// Возвращает указатель на список всех деревьев
	// Возвращает 0, если деревьев нет
	const QVector<TreeExpressions>* get_trees ();

	// Возвращает идентификатор
	// 0, если пусто
	const Identifier* get_identifier (int id);
	// Возвращает все идентификаторы
	// 0, если пусто
	const QVector<Identifier>* get_identifiers ();

	// Возвращает количество идентификаторов в коде
	int get_count_identifiers ();
	// Возвращает количество деревьев (не в лесу)
	int get_count_trees ();

	// Возвращает все строки с токенами
	const QVector<Expression>* get_lines ();

};

#endif // PARSER_H
