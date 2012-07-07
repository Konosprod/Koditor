#include "qonsole.h"

Term::Term(QWidget* parent): QWidget(parent)
{
    QGridLayout* layout = new QGridLayout;

    logView = new QTextEdit(this);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    logView->setReadOnly(true);
    logView->append("-------- Log --------");
    logView->setPalette(QPalette(QColor(0, 0, 0)));
    layout->addWidget(logView, 0, 0, 4, 4);

    entry = new QLineEdit(this);
    entry->setText("Entrez votre commande ici");
    connect(entry, SIGNAL(returnPressed()), this, SLOT(execute()));
    layout->addWidget(entry, 5, 0);

    this->setLayout(layout);

    process = new QProcess(parent);
    process->setReadChannelMode(QProcess::MergedChannels);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(showLog()));
    connect(qApp, SIGNAL(aboutToQuit()), process, SLOT(kill()));
    process->start("bash", QStringList() << "-i");
}

void Term::killProcess()
{
    process->kill();
}

void Term::execute()
{
    QString commande(entry->text() + '\n');
    entry->setText("");
    QByteArray bytes(commande.toUtf8());
    process->write(bytes);
}

void Term::showLog()
{
    QByteArray bytes(process->readAllStandardOutput());
    QStringList lines(QString(bytes).split('\n'));
    foreach(QString line, lines)
    {
        line.remove(line.count(), 1);
        logView->append(line);
    }
}
