#include "textdialog.h"
#include <QVBoxLayout>
#include <QFile>
#include <QDir>
#include <QMessageBox>

TextDialog::TextDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Laster inn UI tekstfelt
    textEdit = new QTextEdit(this);
    layout->addWidget(textEdit);

    // Konfigurerer OK / Cancel
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &TextDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttonBox);
}

void TextDialog::accept()
{
    QString content = textEdit->toPlainText();

    // Stopp ved I/O feil
    QFile file("note.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qCritical() << "Cannot save file:" << file.errorString();
        return;
    }

    // Lagre tekst til fil
    QTextStream out(&file);
    out << content;
    file.close();

    // Åpne meldingsboks
    QMessageBox::information(this, "Saved", content);
    QDialog::accept();
}
