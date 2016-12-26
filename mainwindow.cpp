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

void MainWindow::on_pushButton_get_tokens_clicked() {
	Parser p;
	p.LexicalAnalysis (ui->textEdit_source->toPlainText ());

	ui->listWidget_tokens->clear ();

	QVector<Expression> lines = *p.get_lines ();

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
