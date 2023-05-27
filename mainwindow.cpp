#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->itemList->addItem("Python");

    ui->comboBox->addItem("C++");
    ui->comboBox->addItem("C#");
    ui->comboBox->addItem("Java");
    ui->comboBox->addItem("Python");
    ui->comboBox->addItem("PHP");

    connect(ui->addItemButton, &QPushButton::clicked, this, &MainWindow::onAddItemButtonClicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::onResetButtonClicked);

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
    qInfo() << "Added " << text << " to list";
}

void MainWindow::onResetButtonClicked()
{
    ui->itemList->clear();
    qInfo() << "Cleared item list.";
}
