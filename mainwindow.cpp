#include"mainwindow.h"
#include"ui_mainwindow.h"
#include"globalsignal.h"
#include"adddialog.h"
#include"viewdialog.h"
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow){
	ui->setupUi(this);
	button_bonding();
	connect(&GS,&GlobalSignal::DeleteSignal,this,&::MainWindow::DeleteEvent);
	connect(&GS,&GlobalSignal::AddSignal,this,&::MainWindow::AddEvent);
}
void MainWindow::button_bonding(){
	tags_button[0]=ui->pushButton_1; tags_button[1]=ui->pushButton_2;
	tags_button[2]=ui->pushButton_3; tags_button[3]=ui->pushButton_4;
	tags_button[4]=ui->pushButton_5; tags_button[5]=ui->pushButton_6;
}
MainWindow::~MainWindow(){
	delete ui;
}
void MainWindow::AddEvent(){
	
}
void MainWindow::DeleteEvent(int index){
	
}
void MainWindow::on_add_pushButton_clicked(){
    AddDialog *ad=new AddDialog();
	ad->show();
}
void MainWindow::on_view_all_pushButton_clicked(){
    ViewDialog *view=new ViewDialog();
	view->setWindowTitle("查看所有题目");
	view->get_result();
	view->show();
}
