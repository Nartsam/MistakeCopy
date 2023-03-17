#ifndef QUESTION_H
#define QUESTION_H

#include<QString>
#include<QDate>
#include<vector>
class Question{
private:
	QString text; //题目内容
	QString correction; //改正记录
	QString answer; //答案
	QString notes; //学习笔记
	QStringList tags;
	QDate creation_date;
public:
	void clear();
	Question();
	Question(const QString &date_str);
	QString get_text()const{return text;}
	QString get_correction()const{return correction;}
	QString get_answer()const{return answer;}
	QString get_notes()const{return notes;}
	QStringList get_tags()const{return tags;}
	void set_text(const QString &str);
	void set_correction(const QString &str);
	void set_answer(const QString &str);
	void set_notes(const QString &str);
	void set_tags_by_string(const QString &str);
	void append_text(const QString &str);
	void append_correction(const QString &str);
	void append_answer(const QString &str);
	void append_notes(const QString &str);
	void all_trimmed();
	QString get_filename(int index)const;
	QString to_html()const;
};
//All Questions stored here
extern std::vector<Question> QuestionList;

#define DataDir "data\\"
extern QString SptorStr; //Separator in file
void WriteQuestionListToDir();
void ReadQuestionListFromDir();
void WriteQuestionToFile(const QString &path,const Question &q);
Question ReadQuestionFromFile(const QString &path);

#endif // QUESTION_H
