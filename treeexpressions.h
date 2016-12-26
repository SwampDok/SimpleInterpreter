#ifndef TREEEXPRESSIONS_H
#define TREEEXPRESSIONS_H

#include "expression.h"

/*
 * Структура реализует ячейку дерева
 */
struct TreeCell {
	// Узел, из которого выходит данная ячейка
	TreeCell *parent;
	// Левый порожденный узел
	TreeCell *left_cell;
	// Правый порожденный узел
	TreeCell *right_cell;
	// Операция данного узла
	// например, "+", "-" и т.д.
	QString operation;
	// Левый операнд узла
	Expression left;
	// Правый операнд узла
	Expression right;
};

/*
 * Класс реализуется контейнер для хранения дерева,
 * которое получается в результате синтаксического разбора кода
 */
class TreeExpressions
{
	// Корень дерева выражений
	TreeCell *root_;
public:
	TreeExpressions ();

	TreeExpressions (TreeCell *root);

	TreeCell* get_root ();

	void set_root (TreeCell *root);
};

#endif // TREEEXPRESSIONS_H
