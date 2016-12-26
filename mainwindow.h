#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>

#include <QVector>
#include <QString>

#include "parser.h"
#include "treeexpressions.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_pushButton_get_tokens_clicked();

	void on_pushButton_run_all_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
