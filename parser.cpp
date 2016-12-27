#include "parser.h"

Parser::Parser() {

}

void Parser::LexicalAnalysis (const QString &source) {
	QString word = "";
	Expression expr;
	bool ok1 = false;
	bool ok2 = false;

	lines_.clear ();

	for (int i = 0; i < source.size (); ++i) {
		if (source[i] == ' ' || source[i] == '\n' || source[i] == '\0') {
			// Токен является ключевым словом
			ok1 = key_words.contains (word);
			if (ok1)
				expr.AddToken (word, false, false);

			ok2 = false;

			word.toInt (&ok2);
			// Токен является числом
			if (ok2)
				expr.AddToken (word, true, false);

			// Токен является идентификатором
			if (ok1 == false && ok2 == false)
				expr.AddToken (word, false, true);

			// Конец строки
			if (source[i] == '\n' || source[i] == '\0') {
				lines_.push_back (expr);
			}

			word.clear ();
			continue;
		}

		word += source[i];
	}
}

void Parser::CreateCell (TreeCell *root,
                         Expression &expr,
                         const QString &operation,
                         int separator,
                         bool flag) {

	TreeCell *cell;
	Expression tmp;
	int i = separator;

	cell = new TreeCell;

	// Устанавливает указатель родителя
	// флаг=1 - новая ячейка справа
	// флаг=0 - новая ячейка слева
	if (root != 0) {
		if (flag == 0) {
			root->left_cell = cell;
			cell->flag = 0;
		} else {
			root->right_cell = cell;
			cell->flag = 1;
		}
	}

	// Обрабатываем левую часть выражения
	for (int j = 0; j < i; ++j)
		tmp.AddToken (expr.get_token (j));

	cell->left = tmp;
	tmp.Clear ();

	if (cell->left.get_size () < 2) {
		cell->left_cell = 0;
	}

	// Обрабатываем правую часть выражения
	for (int j = i + 1; j < expr.get_size (); ++j)
		tmp.AddToken (expr.get_token (j));

	cell->right = tmp;
	tmp.Clear ();

	if (cell->right.get_size () < 2) {
		cell->right_cell = 0;
	}

	cell->parent = root;
	cell->operation = operation;

	// Сохраняется адрес начала дерева
	// Это будет корень дерева
	// Он содержит операцию равно
	if (root == 0)
		root_ = cell;

	// Обход левых ветвей
	if (cell->left.get_size () > 1)
		Parsing (cell, cell->left, 0);
	// Обход правых ветвей
	if (cell->right.get_size () > 1)
		Parsing (cell, cell->right, 1);

	return;
}

void Parser::Parsing (TreeCell *root, Expression &expr, bool flag) {

	// Порядок проверок задает приоритетность операций
	for (int i = 0; i < expr.get_size (); ++i) {
		if (expr.get_string_token (i) == "=") {
			CreateCell (root, expr, "=", i, flag);
			return;
		}
	}

	// В цикле операции одного приоритета
	for (int i = 0; i < expr.get_size (); ++i) {
		if (expr.get_string_token (i) == "+")  {
			CreateCell (root, expr, "+", i, flag);
			return;
		}
		if (expr.get_string_token (i) == "-")  {
			CreateCell (root, expr, "-", i, flag);
			return;
		}
	}

	// В цикле операции одного приоритета
	for (int i = 0; i < expr.get_size (); ++i) {
		if (expr.get_string_token (i) == "*")  {
			CreateCell (root, expr, "*", i, flag);
			return;
		}
		if (expr.get_string_token (i) == "/")  {
			CreateCell (root, expr, "/", i, flag);
			return;
		}
	}
}

bool Parser::CreateTrees (int &incorrect_line) {
	if (lines_.empty ())
		return false;

	trees_.clear ();
	ids_.clear ();

	for (int i = 0; i < lines_.size (); ++i) {
		Parsing (0, lines_[i], 1);
		trees_.push_back (root_);
	}

	return true;
}

void Parser::Clear () {
	trees_.clear ();
	ids_.clear ();
	lines_.clear();
}

TreeCell* Parser::get_tree (int id) {
	if (trees_.empty ())
		return 0;

	return trees_[id];
}

const Identifier* Parser::get_identifier (int id) {
	if (ids_.empty ())
		return 0;

	return &ids_[id];
}

const QVector<Identifier>* Parser::get_identifiers () {
	if (ids_.empty ())
		return 0;

	return &ids_;
}

int Parser::get_count_identifiers () {
	return ids_.size ();
}

int Parser::get_count_trees () {
	return trees_.size ();
}


const QVector<Expression>* Parser::get_lines () {
	return &lines_;
}
