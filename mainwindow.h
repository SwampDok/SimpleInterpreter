#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>

#include <QVector>
#include <QString>

#include "parser.h"
#include "treeexpressions.h"
#include "implementer.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	// Служит для получения дерева разбора выражений
	Parser p_;

	Implementer impl_;
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_pushButton_get_tokens_clicked();

	void on_pushButton_run_all_clicked();

	void on_pushButton_clear_variables_clicked();

private:
	Ui::MainWindow *ui;

	void UpdateListTokens ();
	void UpdataTableIds ();
};

#endif // MAINWINDOW_H
