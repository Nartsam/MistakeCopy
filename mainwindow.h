#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	
private slots:
	void AddEvent();
	void DeleteEvent(int index);
	void on_add_pushButton_clicked();
	void on_view_all_pushButton_clicked();
	
private:
	Ui::MainWindow *ui;
	QPushButton *tags_button[6];
	void button_bonding();
};
#endif // MAINWINDOW_H
