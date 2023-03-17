#include"viewdialog.h"
#include"ui_viewdialog.h"
#include"globalsignal.h"
#include"codec.h"
ViewDialog::ViewDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ViewDialog){
	ui->setupUi(this);
	view_index.clear();
	current_page=0;
	connect(&GS,&GlobalSignal::DeleteSignal,this,&::ViewDialog::DeleteEvent);
	connect(&GS,&GlobalSignal::AddSignal,this,&::ViewDialog::AddEvent);
}
ViewDialog::~ViewDialog(){
	delete ui;
}
void ViewDialog::get_result(){
	view_index.clear();
	for(int i=0;i<(int)QuestionList.size();i++) view_index.push_back(i);
	refresh();
}
void ViewDialog::get_result(const QString &str){
	SearchQuestionByString(str,view_index); refresh();
}
void ViewDialog::get_result(const QStringList &tags){
	SearchQuestionByTags(tags,view_index); refresh();
}
void ViewDialog::get_result(const Question &q){
	SearchQuestionByQuestion(q,view_index); refresh();
}
void ViewDialog::refresh(){
	if(!view_index.empty()){
		ui->page_lineEdit->setText(QString::number(current_page+1));
		ui->first_page_label->setText("1");
		ui->last_page_label->setText(QString::number(view_index.size()));
		ui->textBrowser->setHtml(QuestionList[view_index[current_page]].to_html());
	}
	else{
		
	}
}
void ViewDialog::DeleteEvent(int index){
	for(int i=0;i<(int)view_index.size();i++){
		if(view_index[i]>index) view_index[i]--;
		else if(view_index[i]==index){
			view_index.erase(view_index.begin()+i);
		}
	}
	if(current_page<0) current_page=0;
	if(current_page>=(int)view_index.size()) current_page=view_index.size()-1;
	
}
void ViewDialog::AddEvent(){
	
}
void ViewDialog::on_prev_pushButton_clicked(){
    current_page--;
    if(current_page<0) current_page=0;
    else refresh();
}
void ViewDialog::on_next_pushButton_clicked(){
    current_page++;
    if(current_page>=(int)view_index.size()) current_page=view_index.size()-1;
    else refresh();
}
void ViewDialog::on_getsim_pushButton_clicked(){
    ViewDialog *chd_dia=new ViewDialog();
	chd_dia->setWindowTitle("查找相似问题");
	chd_dia->get_result(QuestionList[view_index[current_page]]);
	chd_dia->show();
}
void ViewDialog::on_delete_pushButton_clicked(){
    
}
