#ifndef TEXTDIALOG_H
#define TEXTDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QDialogButtonBox>

class TextDialog : public QDialog
{
    Q_OBJECT

public:
    TextDialog(QWidget *parent = nullptr);

private slots:
    void accept();

private:
    QTextEdit *textEdit;
    QDialogButtonBox *buttonBox;
};

#endif
