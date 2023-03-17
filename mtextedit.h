#ifndef MTEXTEDIT_H
#define MTEXTEDIT_H

#include <QTextEdit>

class MTextEdit : public QTextEdit
{
public:
	MTextEdit(QWidget *parent=nullptr);
	bool canInsertFromMimeData(const QMimeData *source) const;
	void insertFromMimeData(const QMimeData *source);
	void dropImage(const QUrl &url, const QImage &image);
	void dropTextFile(const QUrl &url);
};

#endif // MTEXTEDIT_H
