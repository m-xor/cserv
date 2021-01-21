#include "button.h"
#include "credential.h"
#include "config.h"
#include <QDebug>
#include "devicesec.h"
#include <QMessageBox>
#include "credential.h"
#include "credential.h"
#include "config.h"


QWidget * Button::parent;

void Button::setParent(QWidget *parent)
{
    Button::parent = parent;
}

Button::Button(
        int btnId,
        QLineEdit *lbl,
        QLineEdit *credentials,
        QPushButton *newline,
        QPushButton *tabulator,
        QPushButton *remove,
        QPushButton *restore,
        QPushButton *save
        )
    : btnId(btnId),
      lbl(lbl),
      credentials(credentials),
      newline(newline),
      tabulator(tabulator),
      rm(remove),
      restor(restore),
      sav(save)
{
}


void Button::populateButton()
{
    QString str;

    Config::readLabel(DeviceSec::getDeviceSN(),btnId,str);
    lbl->setText(str);
    lbl->setEnabled(true);

    if(Credential::getCredential(btnId,str)) {
        credentials->setText(str);
        rm->setEnabled(true); //usuń
    }
    credentials->setEnabled(true);
    //   bt.restore->setEnabled(true); //przywroc
    newline->setEnabled(true); //nl
    tabulator->setEnabled(true); //tab
}

void Button::clearButton()
{
    lbl->clear();
    credentials->clear();
    credentials->setEnabled(false);
    lbl->setEnabled(false);
    newline->setEnabled(false);
    rm->setEnabled(false);
    restor->setEnabled(false);
    sav->setEnabled(false);
    tabulator->setEnabled(false);
}

void Button::changedCred()
{
    restor->setEnabled(true);
    sav->setEnabled(true);
}

bool Button::isSaved() const
{
    return ! sav->isEnabled();
}


void Button::remove()
{
    if(QMessageBox::Ok != QMessageBox::warning(
                Button::parent,
                "Usuń",
                "Kliknięcie OK spowoduje bezpowrotne\nusunięcie "
                "hasła z urządzenia",
                QMessageBox::Ok,
                QMessageBox::Cancel)) {
        return;
    }
    Credential::clearCredential(btnId);
    this->clearButton();
    this->populateButton();
}

void Button::restore()
{
    this->clearButton();
    this->populateButton();
}

void Button::save()
{
    if(!Credential::validateCredential(credentials->text())) {
        QMessageBox::warning(Button::parent,"Zapisz","Hasło jest zbyt długie\nlub zawiera niedozwolone znaki");
        return;
    }

    if(QMessageBox::Ok != QMessageBox::warning(
                Button::parent,
                "Zapisz",
                "Potwierdź zapisanie nowego hasła"
                "",
                QMessageBox::Ok,
                QMessageBox::Cancel)) {
        qDebug() << "cancel save pwd";
        return;
    }

    if(!Credential::setCredential(btnId,credentials->text())) {
        QMessageBox::warning(Button::parent,"Zapisz","Hasło jest zbyt długie\nlub zawiera niedozwolone znaki");
        return;
    }

    this->clearButton();
    this->populateButton();
}

void Button::change()
{
    this->changedCred();
}

void Button::insert(QChar c)
{
    QString str = credentials->text();
    int pos = credentials->cursorPosition();
    str.insert(pos,c);
    credentials->setText(str);
    credentials->setCursorPosition(pos+1);
    this->changedCred();
    credentials->setFocus();
}

void Button::label(const QString& lbl)
{
    Config::writeLabel(DeviceSec::getDeviceSN(), btnId, lbl);
}
