#include"mainwindow.h"
#include<QApplication>
#include"question.h"
int main(int argc, char *argv[]){
	qputenv("QT_SCALE_FACTOR","1.0");
	QApplication a(argc, argv);
	ReadQuestionListFromDir();
	MainWindow w;
	w.show();
	int return_value=a.exec();
	WriteQuestionListToDir();
	return return_value;
}
