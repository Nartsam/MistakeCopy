#include"question.h"
#include<QDir>
#include<QTextEdit>
#include<vector>
#include<iostream>
#include<map>
#include"codec.h"
#include"loadingdialog.h"
std::vector<Question> QuestionList;
std::map<QString,int> TagsMap;
void Question::clear(){
	text.clear(); correction.clear(); answer.clear();
	notes.clear(); tags.clear();
	creation_date=QDate::currentDate();
}
Question::Question(){clear();}
Question::Question(const QString &date_str){
	clear(); creation_date=QDate::fromString(date_str,"yyyy-MM-dd");
}
void Question::set_text(const QString &str){
	text=str;
}
void Question::set_correction(const QString &str){
	correction=str;
}
void Question::set_answer(const QString &str){
	answer=str;
}
void Question::set_notes(const QString &str){
	notes=str;
}
void Question::set_tags_by_string(const QString &str){
	QStringList list=str.split(';');
	tags.clear();
	for(const QString &i:list){
		if(i.trimmed().isEmpty()) continue;
		tags.push_back(i.trimmed());
	}
}
void Question::append_text(const QString &str){
	text.append(str);
}
void Question::append_correction(const QString &str){
	correction.append(str);
}
void Question::append_answer(const QString &str){
	answer.append(str);
}
void Question::append_notes(const QString &str){
	notes.append(str);
}
void Question::all_trimmed(){
	text=text.trimmed(); correction=correction.trimmed();
	answer=answer.trimmed(); notes=notes.trimmed();
}
QString Question::get_filename(int index)const{
	return QString(QString::number(index+1000000)+"_"+creation_date.toString("yyyy-MM-dd"));
}
QString Question::to_html()const{
	QString res;
    res.append(TITLE_TEXT(">>> 题目内容")); res.append(text);
    res.append(TITLE_TEXT(">>> 改正记录")); res.append(correction);
    res.append(TITLE_TEXT(">>> 正确答案")); res.append(answer);
    res.append(TITLE_TEXT(">>> 学习笔记")); res.append(notes);
    res.append("<h3>创建日期  /  标签</h3>");
	res.append(creation_date.toString("yy-MM-dd")+"  /  ");
	bool isfirst=true;
	for(const auto &i:tags){
		if(!isfirst) res.append("; ");
		isfirst=false; res.append(i);
	}
    return res;
}

/**************************************************/
QString SptorStr("!@#$$==??|;;<~**^#@##;%!");
void WriteQuestionToFile(const QString &path,const Question &q){
	QFile data_file(path);
	if(!data_file.open(QIODevice::Truncate|QIODevice::WriteOnly|QIODevice::Text)){
		std::cout<<"Error: Write File "<<path.toStdString()<<" Open Failed"<<std::endl;
	}
	data_file.write(q.get_text().toUtf8());
	if(!q.get_text().endsWith('\n')) data_file.write("\n");
	data_file.write(SptorStr.toUtf8()); data_file.write("\n");
	data_file.write(q.get_correction().toUtf8());
	if(!q.get_correction().endsWith('\n')) data_file.write("\n");
	data_file.write(SptorStr.toUtf8()); data_file.write("\n");
	data_file.write(q.get_answer().toUtf8());
	if(!q.get_answer().endsWith('\n')) data_file.write("\n");
	data_file.write(SptorStr.toUtf8()); data_file.write("\n");
	data_file.write(q.get_notes().toUtf8());
	if(!q.get_notes().endsWith('\n')) data_file.write("\n");
	data_file.write(SptorStr.toUtf8()); data_file.write("\n");
	QStringList tags=q.get_tags();
	for(const auto &i:tags){
		data_file.write(i.toUtf8()); data_file.write(";");
	}
	data_file.close();
}
void RemoveAllFiles(const QDir &dir){
	QFileInfoList list=dir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot|QDir::Dirs);
	for(const auto &i:list){
		if(i.isFile()) QFile(i.absoluteFilePath()).remove();
	}
}
void WriteQuestionListToDir(){
	LoadingDialog wt; wt.setTipsText("写入数据中..."); wt.show();
	QDir data_dir(DataDir);
	if(!data_dir.exists()) data_dir.mkdir(data_dir.absolutePath());
	RemoveAllFiles(data_dir);
	int index=0;
	for(const Question &i:QuestionList){
		WriteQuestionToFile(DataDir+i.get_filename(++index),i);
	}
}
Question ReadQuestionFromFile(const QString &path){
	QFile data_file(path);
	QStringList filename_list=data_file.fileName().split('_');
	Question res(filename_list.last());
	if(!data_file.open(QIODevice::ReadOnly | QIODevice::Text)){
		std::cout<<"Error: Read File "<<path.toStdString()<<" Open Failed"<<std::endl;
	}
	QString str(data_file.readLine());
	while(!str.startsWith(SptorStr)){res.append_text(str);str=data_file.readLine();}
	str=data_file.readLine();
	while(!str.startsWith(SptorStr)){res.append_correction(str);str=data_file.readLine();}
	str=data_file.readLine();
	while(!str.startsWith(SptorStr)){res.append_answer(str);str=data_file.readLine();}
	str=data_file.readLine();
	while(!str.startsWith(SptorStr)){res.append_notes(str);str=data_file.readLine();}
	res.all_trimmed(); //reformat
	res.set_tags_by_string(data_file.readLine()); //tags
	data_file.close();
	return res;
}
void ReadQuestionListFromDir(){
	LoadingDialog rd; rd.setTipsText("读取数据中..."); rd.show();
	QuestionList.clear();
	QDir data_dir(DataDir);
	if(!data_dir.exists()) return;
	QFileInfoList list=data_dir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot|QDir::Dirs);
	for(const auto &i:list){
		if(i.isFile()){
			QuestionList.push_back(ReadQuestionFromFile(i.absoluteFilePath()));
		}
	}
}
