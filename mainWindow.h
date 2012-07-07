#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qsci/qsciscintilla.h>
#include "qonsole.h"

namespace Ui {
    class mainWindow;
}


typedef struct document
{
    QsciScintilla doc;
    QString path;
    qint8 modified;
}document;

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = 0);
    void writeFile(const QString& name, QsciScintilla* doc);
    void testExtension(QString extension);
    ~mainWindow();

protected:


public slots:
    void licence();
    void about();
    void openFile();
    void newFile();
    void saveFileAs();
    void saveFile();
    void closeTab(int tab);
    void setHighlighter(int val);
    void hasChanged();
    void resetChanged();

private:
    void setupHighlighterBox();
    void setupConnexion();

    Ui::mainWindow *ui;
    Term* term;
    QVector <document*> docs;
    QComboBox* highligtherBox;
};

#endif // MAINWINDOW_H
