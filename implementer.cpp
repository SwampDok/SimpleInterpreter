#include "implementer.h"

Implementer::Implementer() {
	pars_ = 0;
}

Implementer::Implementer (Parser *pars) {
	pars_ = pars;
}

bool Implementer::AddId (const QString &name, int value) {
	bool flag = false;

	for (int i = 0; i < ids_.size (); ++i) {
		if (ids_[i].get_name ()== name) {
			flag = true;
			break;
		}
	}

	if (flag == false) {
		Identifier id (name, value);
		ids_.push_back (id);
		return true;
	}

	return false;
}

void Implementer::ClearIds () {
	ids_.clear ();
}

bool Implementer::IdExists (const QString &name) {
	for (int i = 0; i < ids_.size (); ++i) {
		if (ids_[i].get_name ()== name) {
			return true;
		}
	}

	return false;
}

void Implementer::Run (TreeCell *cell) {
	// Ячейка корня дерева
	// В левом выражении всегда приемник из одной переменной
	if (cell->parent == 0) {
		if (cell->right_cell != 0 && cell->right_cell->viewed == false) {
			Run (cell->right_cell);
		}
		AddId (cell->left.get_string_token (0), cell->right.get_string_token (0).toInt ());
		set_value (cell->left.get_string_token (0), cell->right.get_string_token (0).toInt ());
		return;
	}

	// В текущей ячейке дерева слева и справа по одному токену
	// Это значит, что мы можем вычислить ячейку и заменить переменные на числа
	if (cell->left.get_size () == 1 &&
	    cell->right.get_size () == 1 &&
	    cell->viewed == false) {
		if (cell->left.get_token (0).IsIdentifir ()) {
			AddId(cell->left.get_string_token (0), 0);
			cell->left.set_token (0,
			                      QString::number (get_value (cell->left.get_string_token (0))),
			                                       false,
			                                       true);
		}
		if (cell->right.get_token (0).IsIdentifir ()) {
			AddId(cell->right.get_string_token (0), 0);
			cell->right.set_token (0,
			                      QString::number (get_value (cell->right.get_string_token (0))),
			                                       false,
			                                       true);
		}

		// Сложение
		if (cell->operation == "+") {
			// Ячейка вышла из левого выражения
			if (cell->flag == 0) {
				cell->parent->left.Clear ();
				cell->parent->left.AddToken (QString::number (cell->left.get_string_token (0).toInt () +
				                                              cell->right.get_string_token (0).toInt ()),
				                             true, false);
			} else { // Ячейка вышла их левого выражения
				cell->parent->right.Clear ();
				cell->parent->right.AddToken (QString::number (cell->left.get_string_token (0).toInt () +
				                                              cell->right.get_string_token (0).toInt ()),
				                             true, false);
			}
		}
		// Вычитание
		if (cell->operation == "-") {
			// Ячейка вышла из левого выражения
			if (cell->flag == 0) {
				cell->parent->left.Clear ();
				cell->parent->left.AddToken (QString::number (cell->left.get_string_token (0).toInt () -
				                                              cell->right.get_string_token (0).toInt ()),
				                             true, false);
			} else { // Ячейка вышла их левого выражения
				cell->parent->right.Clear ();
				cell->parent->right.AddToken (QString::number (cell->left.get_string_token (0).toInt () -
				                                              cell->right.get_string_token (0).toInt ()),
				                             true, false);
			}
		}

		// Умножение
		if (cell->operation == "*") {
			// Ячейка вышла из левого выражения
			if (cell->flag == 0) {
				cell->parent->left.Clear ();
				cell->parent->left.AddToken (QString::number (cell->left.get_string_token (0).toInt () *
				                                              cell->right.get_string_token (0).toInt ()),
				                             true, false);
			} else { // Ячейка вышла их правого выражения
				cell->parent->right.Clear ();
				cell->parent->right.AddToken (QString::number (cell->left.get_string_token (0).toInt () *
				                                              cell->right.get_string_token (0).toInt ()),
				                             true, false);
			}
		}

		// Деление
		if (cell->operation == "/") {
			// Ячейка вышла из левого выражения
			if (cell->flag == 0) {
				cell->parent->left.Clear ();
				cell->parent->left.AddToken (QString::number (cell->left.get_string_token (0).toInt () /
				                                              cell->right.get_string_token (0).toInt ()),
				                             true, false);
			} else { // Ячейка вышла их левого выражения
				cell->parent->right.Clear ();
				cell->parent->right.AddToken (QString::number (cell->left.get_string_token (0).toInt () /
				                                              cell->right.get_string_token (0).toInt ()),
				                             true, false);
			}
		}

		cell->viewed = true;
		if (cell->parent != 0)
			Run (cell->parent);
		return;
	}

	// Обходим левые ветки
	if (cell->left_cell != 0)
		if (cell->left_cell->viewed == false )
			Run (cell->left_cell);

	// Обходим правые ветки
	if (cell->right_cell != 0)
		if (cell->right_cell->viewed == false)
			Run (cell->right_cell);

}

void Implementer::Run () {

	for (int i = 0; i < pars_->get_count_trees (); ++i) {
		Run (pars_->get_tree (i));
	}
}

void Implementer::Run(int number_line) {

}



bool Implementer::set_value (const QString &name, int value) {
	for (int i = 0; i < ids_.size (); ++i) {
		if (ids_[i].get_name ()== name) {
			ids_[i].set_value (value);
			return true;
		}
	}

	return false;
}

bool Implementer::set_parser (Parser *pars) {
	if (pars == 0)
		return false;

	pars_ = pars;

	return true;
}

const QVector<Identifier>* Implementer::get_ids () {
	return &ids_;
}

Identifier Implementer::get_id (int id) {
	return ids_[id];
}

int Implementer::get_value (const QString &name) {
	for (int i = 0; i < ids_.size (); ++i) {
		if (ids_[i].get_name ()== name) {
			return ids_[i].get_value ();
		}
	}

	return -1;
}

int Implementer::get_count_ids () {
	return ids_.size ();
}
