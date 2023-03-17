#ifndef GLOBALSIGNAL_H
#define GLOBALSIGNAL_H

#include <QObject>

class GlobalSignal : public QObject
{
	Q_OBJECT
public:
	explicit GlobalSignal(QObject *parent = nullptr);
	
signals:
	void DeleteSignal(int x);
	void AddSignal();
};

extern GlobalSignal GS;

#endif // GLOBALSIGNAL_H
