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
	void setup_tags_index();
	void on_tags_button_clicked(int pos)const;
	
private slots:
	void AddEvent();
	void DeleteEvent(int index);
	void on_add_pushButton_clicked();
	void on_view_all_pushButton_clicked();
	void on_str_search_pushButton_clicked();
	void on_tags_search_pushButton_clicked();
	void on_pushButton_1_clicked();
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
	
private:
	Ui::MainWindow *ui;
	QPushButton *tags_button[6];
	void button_bonding();
};
#endif // MAINWINDOW_H
