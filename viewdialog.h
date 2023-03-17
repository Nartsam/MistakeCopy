#ifndef VIEWDIALOG_H
#define VIEWDIALOG_H

#include<QDialog>
#include<vector>
#include"question.h"
namespace Ui {
class ViewDialog;
}

class ViewDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit ViewDialog(QWidget *parent = nullptr);
	~ViewDialog();
	void refresh();
	void get_result();
	void get_result(const Question &q);
	void get_result(const QString &str);
	void get_result(const QStringList &tags);

private slots:
	void DeleteEvent(int index);
	void AddEvent();
	void on_prev_pushButton_clicked();
	void on_next_pushButton_clicked();
	void on_getsim_pushButton_clicked();
	void on_delete_pushButton_clicked();
	
private:
	Ui::ViewDialog *ui;
	int current_page;
	std::vector<int> view_index;
};

#endif // VIEWDIALOG_H
