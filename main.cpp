#include"mainwindow.h"
#include<QApplication>
#include"question.h"
int main(int argc, char *argv[]){
    qputenv("QT_SCALE_FACTOR","1.0");
	QApplication a(argc, argv);
	int return_value=0;
	try{
		ReadQuestionListFromDir();
		MainWindow w;
		w.show();
		return_value=a.exec();
		WriteQuestionListToDir();
	}catch(const char *str){
		
	}
	return return_value;
}
