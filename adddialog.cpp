#include"adddialog.h"
#include"ui_adddialog.h"
#include<QFile>
#include<QFileInfo>
#include<QMimeData>
#include<QMessageBox>
#include<QPushButton>
#include<QImageReader>
#include"globalsignal.h"
#include"codec.h"
AddDialog::AddDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddDialog){
	ui->setupUi(this);
	setWindowTitle("添加错题");
	ui->text_radioButton->setChecked(true);
	current_state=&AddDialog::on_text_radioButton_toggled;
	QPushButton *default_button=new QPushButton(this);
	default_button->setGeometry(0,0,0,0);
	default_button->setDefault(true);
}
AddDialog::~AddDialog(){
	delete ui;
}
bool AddDialog::has_input()const{
	return !ui->textEdit->toPlainText().isEmpty();
}
void AddDialog::on_text_radioButton_toggled(bool checked){
	if(checked){
		current_state=&AddDialog::on_text_radioButton_toggled;
		ui->textEdit->setHtml(input.get_text());
	}
	else if(has_input()){
		input.set_text(ui->textEdit->toHtml());
	}
	else input.set_text("");
}
void AddDialog::on_correction_radioButton_toggled(bool checked){
	if(checked){
		current_state=&AddDialog::on_correction_radioButton_toggled;
		ui->textEdit->setHtml(input.get_correction());
	}
	else if(has_input()){
		input.set_correction(ui->textEdit->toHtml());
	}
	else input.set_correction("");
}
void AddDialog::on_answer_radioButton_toggled(bool checked){
	if(checked){
		current_state=&AddDialog::on_answer_radioButton_toggled;
		ui->textEdit->setHtml(input.get_answer());
	}
	else if(has_input()){
		input.set_answer(ui->textEdit->toHtml());
	}
	else input.set_answer("");
}
void AddDialog::on_notes_radioButton_toggled(bool checked){
	if(checked){
		current_state=&AddDialog::on_notes_radioButton_toggled;
		ui->textEdit->setHtml(input.get_notes());
	}
	else if(has_input()){
		input.set_notes(ui->textEdit->toHtml());
	}
	else input.set_notes("");
}
void AddDialog::on_buttonBox_accepted(){ //check & save Question
	((*this).*current_state)(false);
    this->input.set_tags_by_string(ui->lineEdit->text());
	if(CheckQuestionValidity(this->input)){
		QuestionList.push_back(this->input);
		emit GS.AddSignal();
		QMessageBox::information(this,"提示","添加成功");
	}
	else{
		QMessageBox::critical(this,"错误","输入不合法, 添加失败");
	}
}
