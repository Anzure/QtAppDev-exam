#include "textdialog.h"
#include <QVBoxLayout>
#include <QFile>
#include <QMessageBox>

TextDialog::TextDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &TextDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttonBox);
}

void TextDialog::accept()
{
    QString content = textEdit->toPlainText();
    QMessageBox::information(this, "Text", content);
    QDialog::accept();

    QString fileName = "C:\\Temp\\Note.txt";

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << content;

}
