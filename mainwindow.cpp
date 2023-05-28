#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QAction>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setter opp hovedvinduet
    ui->setupUi(this);
    textDialog = new TextDialog(this);
    qInfo() << "Constructed main window";

    // Metodene kalles ved endringer
    connect(ui->addItemButton, &QPushButton::clicked, this, &MainWindow::onAddItemButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);

    // Konfigurerer meny bar
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *addNoteAction = new QAction(tr("&Add Note"), this);
    QAction *openFileAction = new QAction(tr("&Open File"), this);
    fileMenu->addAction(addNoteAction);
    fileMenu->addAction(openFileAction);

    connect(addNoteAction, &QAction::triggered, this, &MainWindow::showTextDialog);
    connect(openFileAction, &QAction::triggered, this, &MainWindow::showFileContents);

    // Klargjør dropdown combobox
    ui->comboBox->addItem("C++");
    ui->comboBox->addItem("C#");
    ui->comboBox->addItem("Java");
    ui->comboBox->addItem("Python");
    ui->comboBox->addItem("PHP");

    // Klargjør standard liste
    ui->itemList->addItem("Python");
    loadFromFile();
    onItemListChange();
}

MainWindow::~MainWindow()
{
    // Lukker/fjerner hovedvinduet
    delete ui;
    qInfo() << "Destructed main window";
    saveToFile();
}

void MainWindow::onAddItemButtonClicked()
{
    // Henter ut navn på valgt element
    QComboBox* comboBox = ui->comboBox;
    QString text = comboBox->currentText();

    // Legger til valgt element i listen
    ui->itemList->addItem(text);
    qInfo() << "Added" << text << "to list";

    // Trigger statuslinje oppdatering
    onItemListChange();
}

void MainWindow::onClearButtonClicked()
{
    // Fjerner alle elementer i listen
    ui->itemList->clear();
    qInfo() << "Cleared all items in list.";

    // Trigger statuslinje oppdatering
    onItemListChange();
}

void MainWindow::onItemListChange()
{
    // Hent og debug listens størrelse
    int size = ui->itemList->count();
    qDebug() << "New item list size:" << size;

    // Konverter til tekst og oppdater statusbar
    QString sizeStr = QString::number(size);
    statusBar()->showMessage(sizeStr + " items");
}

void MainWindow::showTextDialog()
{
    // Åpne ekstra vindu (dialog)
    textDialog->exec();
}

void MainWindow::showFileContents()
{
    // Stopp hvis feil med fil
    QFile file("note.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Cannot open file:" << file.errorString();
        return;
    }

    // Hent tekst innhold i fil
    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    // Logg tekst og åpne popup
    qDebug() << "File content:" << fileContent;
    QMessageBox::information(this, "Note", fileContent);
}

void MainWindow::saveToFile()
{
    // Ignorer lagring hvis I/O feil
    QFile file("list.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot save file:" << file.errorString();
        return;
    }

    // Lagre alle elementene til filen
    QTextStream out(&file);
    for (int i = 0; i < ui->itemList->count(); ++i)
        out << ui->itemList->item(i)->text() << "\n";
    file.close();
}

void MainWindow::loadFromFile()
{
    // Ignorer hvis fil ikke finnes
    QFile file("list.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    // Les hver linje og legg til liste
    ui->itemList->clear();
    QTextStream in(&file);
    while (!in.atEnd())
        ui->itemList->addItem(in.readLine());
    file.close();
}
