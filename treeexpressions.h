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
	// Содержимое данной ячейки дерева
	Expression content;
};

/*
 * Класс реализуется контейнер для хранения дерева,
 * которое получается в результате синтаксического разбора кода
 */
class TreeExpressions
{
	TreeCell *root_;
public:
	TreeExpressions ();

	TreeExpressions (TreeCell *root);

	TreeCell* get_root ();

	void set_root (TreeCell *root);
};

#endif // TREEEXPRESSIONS_H
