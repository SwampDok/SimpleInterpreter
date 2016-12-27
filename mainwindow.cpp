#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QStringList headers = {"Идентифактор", "Значение"};


	ui->tableWidget_variables->setColumnCount (2);
	ui->tableWidget_variables->setHorizontalHeaderLabels (headers);
	ui->tableWidget_variables->setEditTriggers (QAbstractItemView::NoEditTriggers);

}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::UpdateListTokens () {
	ui->listWidget_tokens->clear ();
	QVector<Expression> lines = *p_.get_lines ();
	for (int i = 0; i < lines.size (); ++i) {
		ui->listWidget_tokens->addItem ("Строка " + QString::number (i) + ":");

		for (int j = 0; j < lines[i].get_size (); ++j) {
			ui->listWidget_tokens->addItem (lines[i].get_string_token (j) +
			                                (lines[i].get_token (j).IsConstant () ? " Число" : "") +
			                                (lines[i].get_token (j).IsIdentifir () ? " Идентификатор" : "") +
			                                (lines[i].get_token (j).IsConstant () == false && lines[i].get_token (j).IsIdentifir () == false ? " Ключевое слово" : "") );
		}
	}
}

QString PrintExpression (Expression expr) {
	QString tmp = "";
	for (int i = 0; i < expr.get_size (); ++i)
		tmp += expr.get_string_token (i);

	return tmp;
}

void PrintTree (const TreeCell *root) {
	if (root == 0)
		return;

	qDebug() << PrintExpression (root->left) << root->operation << PrintExpression (root->right);
	PrintTree (root->left_cell);
	PrintTree (root->right_cell);
}

void MainWindow::on_pushButton_run_all_clicked() {

	int i = 0;

	p_.Clear ();
	p_.LexicalAnalysis (ui->textEdit_source->toPlainText ());

	UpdateListTokens ();

	p_.CreateTrees (i);
	qDebug () << "Count trees: " << p_.get_count_trees ();

	PrintTree (p_.get_tree (0));

	ui->statusBar->showMessage ("Синтасический анализ проведен!");
}
