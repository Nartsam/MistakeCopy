#include"mainwindow.h"
#include"ui_mainwindow.h"
#include"globalsignal.h"
#include"adddialog.h"
#include"viewdialog.h"
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow){
	ui->setupUi(this);
	setWindowTitle("电子错题本");
	setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);
	setFixedSize(this->size());
	button_bonding();
	connect(&GS,&GlobalSignal::DeleteSignal,this,&::MainWindow::DeleteEvent);
	connect(&GS,&GlobalSignal::AddSignal,this,&::MainWindow::AddEvent);
	setup_tags_index();
}
void MainWindow::button_bonding(){
	tags_button[0]=ui->pushButton_1; tags_button[1]=ui->pushButton_2;
	tags_button[2]=ui->pushButton_3; tags_button[3]=ui->pushButton_4;
	tags_button[4]=ui->pushButton_5; tags_button[5]=ui->pushButton_6;
}
MainWindow::~MainWindow(){
	delete ui;
}
inline bool tags_pair_cmp(const std::pair<QString,int> &a,const std::pair<QString,int> &b){
	return a.second>b.second;
}
void MainWindow::setup_tags_index(){
	TagsMap.clear();
	for(const Question &q:QuestionList){
		QStringList tags=q.get_tags();
		for(const auto &i:tags) ++TagsMap[i];
	}
	std::vector<std::pair<QString,int> > v(TagsMap.begin(),TagsMap.end());
	std::sort(v.begin(),v.end(),tags_pair_cmp);
	int length=std::min(6,(int)v.size());
	for(int i=0;i<length;i++){
		tags_button[i]->setText(v[i].first); tags_button[i]->setVisible(true);
	}
	while(length<6) tags_button[length++]->setVisible(false);
}
void MainWindow::AddEvent(){
}
void MainWindow::DeleteEvent(int index){
	QuestionList.erase(QuestionList.begin()+index);
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
void MainWindow::on_str_search_pushButton_clicked(){
	ViewDialog *view=new ViewDialog();
	view->setWindowTitle("按内容搜索");
	view->get_result(ui->search_lineEdit->text().trimmed());
	view->show();
}
void MainWindow::on_tags_search_pushButton_clicked(){
    QStringList spt=ui->tags_lineEdit->text().split(";");
	QStringList ref;
	for(const QString &i:spt){
		if(!i.trimmed().isEmpty()) ref.push_back(i.trimmed());
	}
	ViewDialog *view=new ViewDialog();
	view->setWindowTitle("按标签搜索");
	view->get_result(ref);
	view->show();
}
void MainWindow::on_tags_button_clicked(int pos)const{
	--pos;
	ViewDialog *view=new ViewDialog();
	view->setWindowTitle("按标签查看");
	view->get_result(QStringList(tags_button[pos]->text()));
	view->show();
}
void MainWindow::on_pushButton_1_clicked(){on_tags_button_clicked(1);}
void MainWindow::on_pushButton_2_clicked(){on_tags_button_clicked(2);}
void MainWindow::on_pushButton_3_clicked(){on_tags_button_clicked(3);}
void MainWindow::on_pushButton_4_clicked(){on_tags_button_clicked(4);}
void MainWindow::on_pushButton_5_clicked(){on_tags_button_clicked(5);}
void MainWindow::on_pushButton_6_clicked(){on_tags_button_clicked(6);}
