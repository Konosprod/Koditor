#ifndef QONSOLE_H
#define QONSOLE_H

#include <QtGui>

class Term : public QWidget
{
    Q_OBJECT

public:
    Term(QWidget* parent);

public slots:
    void execute();
    void showLog();
    void killProcess();

protected:
    QTextEdit *logView;
    QProcess *process;
    QLineEdit *entry;
};

#endif // QONSOLE_H
