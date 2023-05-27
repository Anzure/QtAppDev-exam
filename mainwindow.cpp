#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setter opp hovedvinduet
    ui->setupUi(this);
    qInfo() << "Constructed main window";

    // Klargjør dropdown combobox
    ui->comboBox->addItem("C++");
    ui->comboBox->addItem("C#");
    ui->comboBox->addItem("Java");
    ui->comboBox->addItem("Python");
    ui->comboBox->addItem("PHP");

    // Klargjør standard liste
    ui->itemList->addItem("Python");
    onItemListChange();

    // Metodene kalles ved endringer
    connect(ui->addItemButton, &QPushButton::clicked, this, &MainWindow::onAddItemButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);
}

MainWindow::~MainWindow()
{
    // Lukker/fjerner hovedvinduet
    delete ui;
    qInfo() << "Destructed main window";
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
