#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->itemList->addItem("Python");
    onItemListChange();

    ui->comboBox->addItem("C++");
    ui->comboBox->addItem("C#");
    ui->comboBox->addItem("Java");
    ui->comboBox->addItem("Python");
    ui->comboBox->addItem("PHP");

    connect(ui->addItemButton, &QPushButton::clicked, this, &MainWindow::onAddItemButtonClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddItemButtonClicked()
{
    QComboBox* comboBox = ui->comboBox;
    QString text = comboBox->currentText();
    ui->itemList->addItem(text);
    onItemListChange();
    qInfo() << "Added " + text + " to list";
}

void MainWindow::onClearButtonClicked()
{
    ui->itemList->clear();
    onItemListChange();
    qInfo() << "Cleared item list.";
}

void MainWindow::onItemListChange()
{
    int listSize = ui->itemList->count();
    statusBar()->showMessage(QString::number(listSize) + " items");
}
