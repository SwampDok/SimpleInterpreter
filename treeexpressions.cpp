#include "treeexpressions.h"

TreeExpressions::TreeExpressions() {
	root_ = 0;
}

TreeExpressions::TreeExpressions (TreeCell *root) :
  root_ (root) {}

TreeCell* TreeExpressions::get_root () {
	return root_;
}

void TreeExpressions::set_root (TreeCell *root) {
	root_ = root;
}
