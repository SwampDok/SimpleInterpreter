#include "parser.h"

Parser::Parser() {

}

void Parser::LexicalAnalysis (const QString &source) {
	QString word = "";
	Expression expr;
	bool ok1 = false;
	bool ok2 = false;

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
                         TreeCell &first_cell) {

	TreeCell *cell;
	Expression tmp;
	int i = separator;

	cell = new TreeCell;

	// Обрабатываем левую часть выражения
	for (int j = 0; j < i; ++j)
		tmp.AddToken (expr.get_token (j));

	cell->left = tmp;
	tmp.Clear ();

	if (cell->left.get_size () > 1) {
		cell->left_cell = new TreeCell;
	} else {
		cell->left_cell = 0;
	}

	// Обрабатываем правую часть выражения
	for (int j = i + 1; j < expr.get_size (); ++j)
		tmp.AddToken (expr.get_token (j));

	cell->right = tmp;
	tmp.Clear ();

	if (cell->right.get_size () > 1) {
		cell->right_cell = new TreeCell;
	} else {
		cell->right_cell = 0;
	}

	cell->parent = root;
	cell->operation = operation;

	// Сохраняется адрес начала дерева
	// Это будет корень дерева
	// Он содержит операцию равно
	if (root == 0)
		first_cell = *cell;

	// Обход левых ветвей
	Parsing (cell, cell->left, first_cell);
	// Обход правых ветвей
	Parsing (cell, cell->right, first_cell);
}

void Parser::Parsing (TreeCell *root, Expression &expr, TreeCell &first_cell) {

	for (int i = 0; i < expr.get_size (); ++i) {
		// Порядок проверок задает приоритетность операций
		if (expr.get_string_token (i) == "=") {
			CreateCell (root, expr, "=", i, first_cell);
			break;
		}
		if (expr.get_string_token (i) == "+")  {
			CreateCell (root, expr, "+", i, first_cell);
			break;
		}
		if (expr.get_string_token (i) == "-")  {
			CreateCell (root, expr, "-", i, first_cell);
			break;
		}
		if (expr.get_string_token (i) == "*")  {
			CreateCell (root, expr, "*", i, first_cell);
			break;
		}
		if (expr.get_string_token (i) == "/")  {
			CreateCell (root, expr, "/", i, first_cell);
			break;
		}
	}
}

bool Parser::CreateTrees (int &incorrect_line) {
	if (lines_.empty ())
		return false;

	TreeCell root;
	TreeExpressions tree;

	for (int i = 0; i < lines_.size (); ++i) {
		Parsing (0, lines_[i],root);
		tree.set_root (&root);
		trees_.push_back (tree);
	}

	return true;
}

void Parser::Clear () {
	trees_.clear ();
	ids_.clear ();
}

const TreeExpressions* Parser::get_tree (int id) {
	if (trees_.empty ())
		return 0;

	return &trees_[id];
}

const QVector<TreeExpressions>* Parser::get_trees () {
	if (trees_.empty ())
		return 0;

	return &trees_;
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
