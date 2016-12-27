#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	// Инициализируем исполнитель
	impl_.set_parser (&p_);

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

void MainWindow::UpdataTableIds () {
	ui->tableWidget_variables->clear ();
	ui->tableWidget_variables->setRowCount (impl_.get_count_ids ());

	QTableWidgetItem *MyItem=new QTableWidgetItem();


	for (int i = 0; i < impl_.get_count_ids (); ++i) {
		// Тут нужно добавить очистку память, так как каждный раз будет новая выделяться
		MyItem = new QTableWidgetItem(impl_.get_id (i).get_name ());
		ui->tableWidget_variables->setItem (i, 0,MyItem);

		MyItem = new QTableWidgetItem(QString::number (impl_.get_id (i).get_value ()));
		ui->tableWidget_variables->setItem (i, 1,MyItem);
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

	impl_.Run ();

	UpdataTableIds ();

	ui->statusBar->showMessage ("Синтасический анализ проведен!");
}
