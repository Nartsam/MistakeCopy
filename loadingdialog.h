#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QMovie>
#include <QLabel>
#include <QDialog>
#include <QPainter>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>

#define USER_CANCEL -1
class LoadingDialog : public QDialog{
	Q_OBJECT
public:
	explicit LoadingDialog(QWidget *parent = nullptr);
	~LoadingDialog();
	void setTipsText(QString strTipsText);
	void setCanCancel(bool bCanCancel); //cancel the waiting button
	void moveToCenter(QWidget* pParent); //Display in target window center
protected:
	void paintEvent(QPaintEvent *event) override;
private:
	void initUi();
Q_SIGNALS:
	void cancelWaiting();
private slots:
	void cancelBtnClicked();
private:
	QFrame *m_pCenterFrame;
	QLabel *m_pMovieLabel;
	QMovie *m_pLoadingMovie;
	QLabel *m_pTipsLabel;
	QPushButton *m_pCancelBtn;
};

#endif // LOADINGDIALOG_H
