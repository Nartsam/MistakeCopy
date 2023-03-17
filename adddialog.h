#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include<QDialog>
#include<QTextEdit>
#include"question.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
	Q_OBJECT
	
public:
	explicit AddDialog(QWidget *parent = nullptr);
	~AddDialog();
	Question input;
	bool has_input()const;
	
private slots:
	void on_text_radioButton_toggled(bool checked);
	void on_correction_radioButton_toggled(bool checked);
	void on_answer_radioButton_toggled(bool checked);
	void on_notes_radioButton_toggled(bool checked);
	void on_buttonBox_accepted();
	
private:
	Ui::AddDialog *ui;
	void (AddDialog::*current_state)(bool);
};

#endif // ADDDIALOG_H
