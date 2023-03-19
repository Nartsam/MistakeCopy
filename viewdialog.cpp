#include"viewdialog.h"
#include"ui_viewdialog.h"
#include<QValidator>
#include<QMessageBox>
#include"globalsignal.h"
#include"codec.h"
ViewDialog::ViewDialog(const QString &append_str,QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ViewDialog){
	ui->setupUi(this);
	view_index.clear();
	current_page=0;
	ui->viewing_label->setText("正在查看: "+append_str);
	ui->page_lineEdit->setValidator(new QIntValidator(ui->page_lineEdit));
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
		ui->page_lineEdit->setReadOnly(false);
		ui->page_lineEdit->setText(QString::number(current_page+1));
		ui->first_page_label->setText("1");
		ui->last_page_label->setText(QString::number(view_index.size()));
		ui->textBrowser->setHtml(QuestionList[view_index[current_page]].to_html());
		ui->delete_pushButton->setEnabled(true);
		ui->getsim_pushButton->setEnabled(true);
	}
	else{
		ui->page_lineEdit->clear(); ui->page_lineEdit->setReadOnly(true);
		ui->delete_pushButton->setEnabled(false);
		ui->getsim_pushButton->setEnabled(false);
		ui->textBrowser->setHtml("<h1> 该分类下没有符合条件的题目 </h1>");
	}
	if(current_page>0) ui->prev_pushButton->setEnabled(true);
	else ui->prev_pushButton->setEnabled(false);
	if(current_page<(int)view_index.size()-1) ui->next_pushButton->setEnabled(true);
	else ui->next_pushButton->setEnabled(false);
	//cancel focus
	ui->prev_pushButton->setDefault(false);
	ui->next_pushButton->setDefault(false);
	ui->delete_pushButton->setDefault(false);
	ui->getsim_pushButton->setDefault(false);
}
void ViewDialog::DeleteEvent(int index){
	int del_index=-1;
	for(int i=0;i<(int)view_index.size();i++){
		if(view_index[i]>index) view_index[i]--;
		else if(view_index[i]==index) del_index=i;
	}
	if(del_index!=-1) view_index.erase(view_index.begin()+del_index);
	if(current_page<0) current_page=0;
	if(current_page>=(int)view_index.size()) current_page=view_index.size()-1;
	refresh();
}
void ViewDialog::AddEvent(){
	if(this->windowTitle()==QString("查看所有题目")){
		view_index.push_back(view_index.size());
	}
	refresh();
}
void ViewDialog::on_prev_pushButton_clicked(){
    current_page--;
    if(current_page<0) current_page=0;
    refresh();
}
void ViewDialog::on_next_pushButton_clicked(){
    current_page++;
    if(current_page>=(int)view_index.size()) current_page=view_index.size()-1;
    refresh();
}
void ViewDialog::on_getsim_pushButton_clicked(){
    ViewDialog *chd_dia=new ViewDialog("\"问题 "+
				QString::number(view_index[current_page]+1)+"\" 的相似问题");
	chd_dia->setWindowTitle("查找相似问题");
	chd_dia->get_result(QuestionList[view_index[current_page]]);
	chd_dia->show();
}
void ViewDialog::on_delete_pushButton_clicked(){
	QMessageBox::StandardButton res=QMessageBox::question(this,"提示","永久删除该题目, 确定吗?");
	if(res==QMessageBox::No) return;
	emit GS.DeleteSignal(view_index[current_page]);
	QMessageBox::information(this,"提示","删除完成");
}
void ViewDialog::on_page_lineEdit_editingFinished(){
    int page=ui->page_lineEdit->text().toInt();
	if(page<1||page>(int)view_index.size()){
		QMessageBox::critical(this,"错误","页码不存在");
	}
	else{
		current_page=page-1;
		refresh();
	}
}

