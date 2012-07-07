#include "qonsole.h"
#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <Qsci/qscilexerbash.h>
#include <Qsci/qscilexerbatch.h>
#include <Qsci/qscilexercmake.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexercsharp.h>
#include <Qsci/qscilexercss.h>
#include <Qsci/qscilexerdiff.h>
#include <Qsci/qscilexerd.h>
#include <Qsci/qscilexerfortran.h>
#include <Qsci/qscilexerfortran77.h>
#include <Qsci/qscilexerhtml.h>
#include <Qsci/qscilexeridl.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qscilexerlua.h>
#include <Qsci/qscilexermakefile.h>
#include <Qsci/qscilexerpascal.h>
#include <Qsci/qscilexerperl.h>
#include <Qsci/qscilexerpostscript.h>
#include <Qsci/qscilexerpov.h>
#include <Qsci/qscilexerproperties.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexerruby.h>
#include <Qsci/qscilexerspice.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qscilexertcl.h>
#include <Qsci/qscilexertex.h>
#include <Qsci/qscilexerverilog.h>
#include <Qsci/qscilexervhdl.h>
#include <Qsci/qscilexerxml.h>
#include <Qsci/qscilexeryaml.h>


/** TODO: - Colorations syntaxique
          - Personnalisation de thème via fichier de config
**/

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    term = new Term(this);
    ui->layoutTerm->addWidget(term);
    QPushButton* buttonNew = new QPushButton(QIcon(":rc/iNew"), QString(), this);
    QPushButton* buttonSaveAs = new QPushButton(QIcon(":rc/iSaveAs"), QString(), this);
    QPushButton* buttonSave = new QPushButton(QIcon(":rc/iSave"), QString(), this);
    QPushButton* buttonOpen = new QPushButton(QIcon(":rc/iOpen"), QString(), this);
    highligtherBox = new QComboBox(this);

    ui->toolBar->addWidget(buttonNew);
    ui->toolBar->addWidget(buttonOpen);
    ui->toolBar->addWidget(buttonSave);
    ui->toolBar->addWidget(buttonSaveAs);
    ui->toolBar->addWidget(highligtherBox);

    ui->actionNouveau->setIcon(QIcon(":rc/iNew"));
    ui->actionNouveau->setIconVisibleInMenu(true);
    ui->actionEnregistrer->setIcon(QIcon(":rc/iSave"));
    ui->actionEnregistrer->setIconVisibleInMenu(true);
    ui->actionEnregistrer_sous->setIcon(QIcon(":rc/iSaveAs"));
    ui->actionEnregistrer_sous->setIconVisibleInMenu(true);
    ui->actionOuvrir->setIcon(QIcon(":rc/iOpen"));
    ui->actionOuvrir->setIconVisibleInMenu(true);

    setupHighlighterBox();


    connect(buttonOpen, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(buttonNew, SIGNAL(clicked()), this, SLOT(newFile()));
    connect(buttonSaveAs, SIGNAL(clicked()), this, SLOT(saveFileAs()));
    connect(buttonSave, SIGNAL(clicked()), this, SLOT(saveFile()));

    setupConnexion();

}

void mainWindow::setupConnexion()
{
    connect(highligtherBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setHighlighter(int)));
    ui->actionOuvrir->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    ui->actionEnregistrer->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    ui->actionEnregistrer_sous->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
    ui->actionNouveau->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    connect(ui->actionOuvrir, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionEnregistrer, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionEnregistrer_sous, SIGNAL(triggered()), this, SLOT(saveFileAs()));
    connect(ui->actionA_propos_de_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(ui->actionNouveau, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionLicence, SIGNAL(triggered()), this, SLOT(licence()));
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::setHighlighter(int val)
{
    int index = ui->tabWidget->currentIndex();

    if(index != -1)
    {
        switch(val)
        {
            case 0:
            docs[index]->doc.setLexer(0);
            break;

            case 1:
            docs[index]->doc.setLexer(new QsciLexerCPP);
            break;

            case 2:
            docs[index]->doc.setLexer(new QsciLexerBash);
            break;

            case 3:
            docs[index]->doc.setLexer(new QsciLexerBatch);
            break;

            case 4:
            docs[index]->doc.setLexer(new QsciLexerCMake);
            break;

            case 5:
            docs[index]->doc.setLexer(new QsciLexerCPP);
            break;

            case 6:
            docs[index]->doc.setLexer(new QsciLexerCSharp);
            break;

            case 7:
            docs[index]->doc.setLexer(new QsciLexerCSS);
            break;

            case 8:
            docs[index]->doc.setLexer(new QsciLexerD);
            break;

            case 9:
            docs[index]->doc.setLexer(new QsciLexerDiff);
            break;

            case 10:
            docs[index]->doc.setLexer(new QsciLexerFortran);
            break;

            case 11:
            docs[index]->doc.setLexer(new QsciLexerFortran77);
            break;

            case 12:
            docs[index]->doc.setLexer(new QsciLexerHTML);
            break;

            case 13:
            docs[index]->doc.setLexer(new QsciLexerIDL);
            break;

            case 14:
            docs[index]->doc.setLexer(new QsciLexerJava);
            break;

            case 15:
            docs[index]->doc.setLexer(new QsciLexerJavaScript);
            break;

            case 16:
            docs[index]->doc.setLexer(new QsciLexerLua);
            break;

            case 17:
            docs[index]->doc.setLexer(new QsciLexerMakefile);
            break;

            case 18:
            docs[index]->doc.setLexer(new QsciLexerPascal);
            break;

            case 19:
            docs[index]->doc.setLexer(new QsciLexerPerl);
            break;

            case 20:
            docs[index]->doc.setLexer(new QsciLexerPostScript);
            break;

            case 21:
            docs[index]->doc.setLexer(new QsciLexerPOV);
            break;

            case 22:
            docs[index]->doc.setLexer(new QsciLexerProperties);
            break;

            case 23:
            docs[index]->doc.setLexer(new QsciLexerPython);
            break;

            case 24:
            docs[index]->doc.setLexer(new QsciLexerRuby);
            break;

            case 25:
            docs[index]->doc.setLexer(new QsciLexerSpice);
            break;

            case 26:
            docs[index]->doc.setLexer(new QsciLexerSQL);
            break;

            case 27:
            docs[index]->doc.setLexer(new QsciLexerTCL);
            break;

            case 28:
            docs[index]->doc.setLexer(new QsciLexerTeX);
            break;

            case 29:
            docs[index]->doc.setLexer(new QsciLexerVerilog);
            break;

            case 30:
            docs[index]->doc.setLexer(new QsciLexerVHDL);
            break;

            case 31:
            docs[index]->doc.setLexer(new QsciLexerXML);
            break;

            case 32:
            docs[index]->doc.setLexer(new QsciLexerYAML);
            break;
        }

        highligtherBox->setCurrentIndex(val);
    }
}

void mainWindow::setupHighlighterBox()
{
    QStringList highligthers;
    highligthers << "Text" << "C" << "Bash" << "Batch" << "CMake"
                 << "C++" << "C#" << "CSS" << "D" << "Diff"
                 << "Fortran" << "Fortran77" << "HTML" << "IDL" << "Java"
                 << "JavaScript" << "Lua" << "Makefile"
                 << "Pascal" << "Perl" << "PostScript" << "POV" << "Properties"
                 << "Python" << "Ruby" << "Spice" << "SQL" << "TCL"
                 << "TeX" << "Verilog" << "VHDL" << "XML" << "YAML";
    highligtherBox->addItems(highligthers);

}

void mainWindow::testExtension(QString extension)
{
    if(extension == "c" || extension == "h")
    {
        setHighlighter(1);
    }
    else if(extension == "sh")
    {
        setHighlighter(2);
    }
    else if(extension == "batch")
    {
        setHighlighter(3);
    }
    else if(extension == "cpp" || extension == "hpp")
    {
        setHighlighter(5);
    }
    else if(extension == "cs")
    {
        setHighlighter(6);
    }
    else if(extension == "css")
    {
        setHighlighter(7);
    }
    else if(extension == "d")
    {
        setHighlighter(8);
    }
    else if(extension == "diff")
    {
        setHighlighter(9);
    }
    else if(extension == "f")
    {
        setHighlighter(12);
    }
    else if(extension == "html" || extension == "htm")
    {
        setHighlighter(13);
    }
    else if(extension == "idl")
    {
        setHighlighter(14);
    }
    else if(extension == "java")
    {
        setHighlighter(15);
    }
    else if(extension == "js")
    {
        setHighlighter(16);
    }
    else if(extension == "lua")
    {
        setHighlighter(17);
    }
    else if(extension == "pp" || extension == "p" || extension == "pas")
    {
        setHighlighter(18);
    }
    else if(extension == "pl")
    {
        setHighlighter(19);
    }
    else if(extension == "ps")
    {
        setHighlighter(20);
    }
    else if(extension == "pov")
    {
        setHighlighter(21);
    }
    else if(extension == "py")
    {
        setHighlighter(23);
    }
    else if(extension == "rb")
    {
        setHighlighter(24);
    }
    else if(extension == "ckt")
    {
        setHighlighter(25);
    }
    else if(extension == "sql")
    {
        setHighlighter(26);
    }
    else if(extension == "tcl")
    {
        setHighlighter(27);
    }
    else if(extension == "tex")
    {
        setHighlighter(28);
    }
    else if(extension == "v")
    {
        setHighlighter(29);
    }
    else if(extension == "xml")
    {
        setHighlighter(31);
    }
    else if(extension == "yaml")
    {
        setHighlighter(32);
    }
    else
    {
        setHighlighter(0);
    }
}

void mainWindow::resetChanged()
{
    QString name;
    QString title;
    int index = ui->tabWidget->currentIndex();

    if(docs[index]->modified == 0)
    {
        if(docs[index]->path.isEmpty())
        {
            name = ui->tabWidget->tabText(index);
            name.remove(name.count()-1, 1);
            ui->tabWidget->setTabText(index, name);
        }
        else
        {
            name = docs[index]->path;
            title = name.mid(name.lastIndexOf('/'));
            title.remove(0, 1);
            title.remove(title.count()-1, 1);
            ui->tabWidget->setTabText(index, title);
        }
    }
}

void mainWindow::saveFile()
{
    QFileInfo infos;
    QString extension;

    int index = ui->tabWidget->currentIndex();

    if(index != -1)
    {

        if(docs[index]->path.isEmpty())
        {
            saveFileAs();
        }
        else
        {
            QFile file(docs[index]->path);

            infos.setFile(file);

            extension = infos.suffix();

            if(file.open(QFile::WriteOnly | QFile::Text))
            {
                QTextStream out(&file);

                out << docs[index]->doc.text();
            }
            docs[index]->modified = 0;
            resetChanged();

            testExtension(extension);
        }
    }
}

void mainWindow::licence()
{
    QMessageBox::information(this, "Licence", "Vous pouvez trouver le texte de la GPLv3 ici:\n"
                                    "http://www.gnu.org/licenses/gpl-3.0.txt");
}

void mainWindow::about()
{
    QMessageBox::about(this, "About", "Ce programme a été fait avec Qt.\n"
                             "Il est sous licence GPLv3. Voir dans le menu Licence.\n"
                             "Vous pouvez trouver la page d'accueil du programme ici:\n"
                             "http://konosprod.free.fr/");

}

void mainWindow::saveFileAs()
{
    QFileInfo infos;
    QString extension;

    int index = ui->tabWidget->currentIndex();

    if(index != -1)
    {
        QString name = QFileDialog::getSaveFileName(this, "Enregistrer sous");

        if(!name.isEmpty())
        {
            QFile file(name);

            infos.setFile(file);

            extension = infos.suffix();

            if(file.open(QFile::WriteOnly | QFile::Text))
            {
                QTextStream out(&file);

                out << docs[index]->doc.text();
            }
            docs[index]->path = name;
            docs[index]->modified = 0;
            resetChanged();

            testExtension(extension);
        }
    }
}

void mainWindow::newFile()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    docs.append(new document);
    docs[docs.count()-1]->modified = 0;
    docs[docs.count()-1]->doc.setFont(font);
    docs[docs.count()-1]->doc.setPalette(QPalette(QColor(0, 0, 0)));

    ui->tabWidget->addTab(&docs[docs.count()-1]->doc ,"Nouveau Doc");
    docs[docs.count()-1]->doc.setMarginLineNumbers(1,true);
    ui->tabWidget->setCurrentIndex(docs.count()-1);
    connect(&docs[docs.count()-1]->doc, SIGNAL(textChanged()), this, SLOT(hasChanged()));
}

void mainWindow::closeTab(int tab)
{
    if(docs[tab]->modified)
    {
        if(QMessageBox::information(this, "Attention", "Le fichier a été modifié et les changements\nn'ont pas été enregister. Voulez-vous les\nsauvegarder ?",
                                    QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
        {
            if(docs[docs.count()-1]->path.isEmpty())
            {
                saveFileAs();
            }
            else
            {
                saveFile();
            }
        }

    }
    docs.remove(tab);
    ui->tabWidget->removeTab(tab);
}

void mainWindow::writeFile(const QString &name, QsciScintilla* doc)
{
    QFile file(name);

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        doc->setText(file.readAll());
    }
}

void mainWindow::hasChanged()
{
    QString name;
    int index = ui->tabWidget->currentIndex();

    if(docs[index]->modified != 1)
    {
        name = ui->tabWidget->tabText(index);
        name += "*";
        ui->tabWidget->setTabText(index, name);
        docs[index]->modified = 1;
    }
}

void mainWindow::openFile()
{
    QFileInfo infos;
    QString extension;
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    QString title;
    QString name = QFileDialog::getOpenFileName(this, "Selectionner un fichier", QString(), QString());

    if(!name.isEmpty())
    {
        docs.append(new document);
        docs[docs.count()-1]->modified = 0;
        docs[docs.count()-1]->doc.setFont(font);
        docs[docs.count()-1]->doc.setPalette(QPalette(QColor(0, 0, 0)));
        docs[docs.count()-1]->path = name;

        infos.setFile(name);

        extension = infos.suffix();

        title = name.mid(name.lastIndexOf('/'));
        title.remove(0, 1);
        docs[docs.count()-1]->doc.setMarginLineNumbers(1,true);
        ui->tabWidget->addTab(&docs[docs.count()-1]->doc ,title);
        writeFile(name, &docs[docs.count()-1]->doc);
        ui->tabWidget->setCurrentIndex(docs.count()-1);

        testExtension(extension);

        connect(&docs[docs.count()-1]->doc, SIGNAL(textChanged()), this, SLOT(hasChanged()));
    }
}
