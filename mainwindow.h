#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QAbstractItemView>
#include "textdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddItemButtonClicked();
    void onClearButtonClicked();
    void onItemListChange();
    void showFileContents();
    void showTextDialog();
    void saveToFile();
    void loadFromFile();

private:
    Ui::MainWindow *ui;
    TextDialog *textDialog;
};

#endif
