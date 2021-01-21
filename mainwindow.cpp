#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "devicesec.h"
#include "commands.h"

#include "credential.h"
#include "config.h"

#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QStandardPaths>
#include <QSettings>


//na potrzeby klasy settings
#define ORGANIZATION "m-xor"
#define DOMAIN  "https://github.com/m-xor"
#define APPLICATION "cServConf"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Class Settings needs it
    QCoreApplication::setOrganizationName(ORGANIZATION);
    QCoreApplication::setOrganizationDomain(DOMAIN);
    QCoreApplication::setApplicationName(APPLICATION);

    //sprawdźmy czy istnieje katalog do zapisu
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    if (path.isEmpty())
        qDebug() << "Ustawienia nie będą mogły być zapisane";
    //wielkość, położenie okna
    Config::readSettings(this);

    //Device groupbox manage
    devWidg = new DeviceWidg(
                ui->comboBox_3,
                ui->pushButton_6,
                ui->label_10,
                ui->label_11,
                ui->pushButton_7,
                ui->pushButton_13
                );


    //Initial scan of ports
    DeviceSec::populateDeviceList(devWidg->getListWidg());


    //for messageboxes' positioning
    Button::setParent(this);

    //map widgets button consists of
    int tmpInd = 0;
    buttons.append(  Button(
                         tmpInd++
                         ,ui->lineEdit_4
                         ,ui->lineEdit_6
                         ,ui->pushButton_12
                         ,ui->pushButton_11
                         ,ui->pushButton_8
                         ,ui->pushButton_9
                         ,ui->pushButton_10
                         )
                     );
    buttons.append(
                Button(
                    tmpInd++
                    ,ui->lineEdit_5
                    ,ui->lineEdit_7
                    ,ui->pushButton_17
                    ,ui->pushButton_16
                    ,ui->pushButton_18
                    ,ui->pushButton_14
                    ,ui->pushButton_15
                    )
                );
    buttons.append(
                Button(
                    tmpInd++
                    ,ui->lineEdit_8
                    ,ui->lineEdit_9
                    ,ui->pushButton_22
                    ,ui->pushButton_21
                    ,ui->pushButton_23
                    ,ui->pushButton_19
                    ,ui->pushButton_20
                    )
                );
    buttons.append(
                Button(
                    tmpInd++
                    ,ui->lineEdit_10
                    ,ui->lineEdit_11
                    ,ui->pushButton_27
                    ,ui->pushButton_26
                    ,ui->pushButton_28
                    ,ui->pushButton_24
                    ,ui->pushButton_25
                    )
                );
    buttons.append(
                Button(
                    tmpInd++
                    ,ui->lineEdit_12
                    ,ui->lineEdit_13
                    ,ui->pushButton_32
                    ,ui->pushButton_31
                    ,ui->pushButton_33
                    ,ui->pushButton_29
                    ,ui->pushButton_30
                    )
                );
    buttons.append(
                Button(
                    tmpInd++
                    ,ui->lineEdit_14
                    ,ui->lineEdit_15
                    ,ui->pushButton_37
                    ,ui->pushButton_36
                    ,ui->pushButton_38
                    ,ui->pushButton_34
                    ,ui->pushButton_35
                    )
                );
    buttons.append(
                Button(
                    tmpInd++
                    ,ui->lineEdit_16
                    ,ui->lineEdit_17
                    ,ui->pushButton_42
                    ,ui->pushButton_41
                    ,ui->pushButton_43
                    ,ui->pushButton_39
                    ,ui->pushButton_40
                    )
                );
    buttons.append(
                Button(
                    tmpInd++
                    ,ui->lineEdit_18
                    ,ui->lineEdit_19
                    ,ui->pushButton_47
                    ,ui->pushButton_46
                    ,ui->pushButton_48
                    ,ui->pushButton_44
                    ,ui->pushButton_45
                    )
                );
    buttons.append(
                Button(
                    tmpInd++
                    ,ui->lineEdit_20
                    ,ui->lineEdit_21
                    ,ui->pushButton_52
                    ,ui->pushButton_51
                    ,ui->pushButton_53
                    ,ui->pushButton_49
                    ,ui->pushButton_50
                    )
                );
    buttons.append(
                Button(
                    tmpInd++
                    ,ui->lineEdit_22
                    ,ui->lineEdit_23
                    ,ui->pushButton_57
                    ,ui->pushButton_56
                    ,ui->pushButton_58
                    ,ui->pushButton_54
                    ,ui->pushButton_55
                    )
                );

}

MainWindow::~MainWindow()
{
    Config::writeSettings(this);

    delete ui;
}


//Urządzenie/Odśwież
void MainWindow::on_pushButton_6_clicked()
{
    DeviceSec::populateDeviceList(devWidg->getListWidg());
}

//Urządzenie/Wybierz
void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    if(index >= 0) {
        DeviceSec::setDescriptors(index, devWidg->getMnfWidg(), devWidg->getSNWidg());
    }
    devWidg->conEnabled(index >= 1);
}

//Urządzenie/Połącz
void MainWindow::on_pushButton_7_clicked()
{
    if(DeviceSec::connectCurrentDevice()) {
        bool ok;
        QString text = QInputDialog::getText(this,
                                             DeviceSec::getDeviceName(),
                                             tr("Hasło:"),
                                             QLineEdit::Password,
                                             tr(""),
                                             &ok);
        if (ok && !text.isEmpty()) {
            if(Commands::password(text)) {
//                qDebug() << "connected" << endl;

                for(int i=0; i<NUMBER_OF_BUTTONS; i++) {
                    buttons[i].populateButton();
                }

                devWidg->conEnabled(false);
                devWidg->disconEnabled(true);
                devWidg->refrEnabled(false);
                devWidg->listEnabled(false);
            } else {
                DeviceSec::disconnectCurrentDevice();
                QMessageBox::warning(this,tr("Hasło"),tr("Nieprawidłowe hasło"));
            }
        } else {
            DeviceSec::disconnectCurrentDevice();
            qDebug() << "Connecting cancelled";
        }
    } else {
        qDebug() << "NOT connected: can't connect device";
        QMessageBox::critical(this,tr("Urządzenie"),tr("Nie można połączyć z urządzeniem"));
    }
}

//Urządzenie/Rozłącz
void MainWindow::on_pushButton_13_clicked()
{
    bool saved = true;
    foreach(const Button& bt, buttons) {
        if(!bt.isSaved()) {
            saved = false; //find at last one unsaved
            break;
        }
    }
    if(!saved) {
        if(QMessageBox::Ok != QMessageBox::warning(
                    this,
                    "Rozłącz",
                    "Istnieją niezapisane hasła.\n"
                    "Kliknięcie OK spowoduje utratę zmian",
                    QMessageBox::Ok,
                    QMessageBox::Cancel)) {
            return;
        }
    }
    Commands::quit();
    DeviceSec::disconnectCurrentDevice();

    devWidg->disconEnabled(false);
    devWidg->conEnabled(true);
    devWidg->refrEnabled(true);
    devWidg->listEnabled(true);

    for(int i=0; i<NUMBER_OF_BUTTONS; i++) {
        buttons[i].clearButton();
    }

    DeviceSec::populateDeviceList(devWidg->getListWidg());
}


/***************** Menu actions *********************/
void MainWindow::on_actionZako_cz_triggered()
{
    this->close();
}

void MainWindow::on_actionO_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_actionO_triggered()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("O programie");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText("Konfigurator Serwera Poświadczeń, ver. 0.9"
                   "<br><br>Copyright 2021 <a href='https://github.com/m-xor'>m-xor</a>. All rights reserved."
                   "<br><br>The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE."
                   );

    msgBox.exec();
}

void MainWindow::on_actionPomoc_triggered()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Pomoc");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(
                // "By przełączyć urządzenie w tryb konfiguracji "
                //"szybko wcisnąć dwa razy klawisz NumLock lub ScrollLock (Lenovo: Fn-K). "
                //"Diody czerwona i żółta powinny zacząć migać naprzemiennie. "
                "Kliknąć \"Odśwież\". Urządzenie powinno pojawić się na liście. "
                "Po wybraniu urządzenia kliknąć \"Połącz\" i podać hasło dostępu."
                );

    msgBox.exec();
}

void MainWindow::on_actionExtButton_triggered()
{
    this->close();
}

// ********** Button 1 Events ********************

//Button 1/Remove
void MainWindow::on_pushButton_8_clicked()
{
    buttons[0].remove();
}

//Button 1/Restore
void MainWindow::on_pushButton_9_clicked()
{
    buttons[0].restore();
}

//Button 1/Save
void MainWindow::on_pushButton_10_clicked()
{
    buttons[0].save();
}

//Button 1/Credential changed
void MainWindow::on_lineEdit_6_textEdited(const QString &arg1)
{
    (void)arg1;
    buttons[0].change();
}

//Button 1/new line
void MainWindow::on_pushButton_12_clicked()
{
    buttons[0].insert(QChar(NEWLINE));
}
//Button 1/tabulator
void MainWindow::on_pushButton_11_clicked()
{
    buttons[0].insert(QChar(TABULATOR));
}

void MainWindow::on_lineEdit_4_textEdited(const QString &arg1)
{
    buttons[0].label( arg1);
}

// ********** Button 2 Events ********************

void MainWindow::on_lineEdit_5_textEdited(const QString &arg1)
{
    buttons[1].label( arg1);
}

void MainWindow::on_lineEdit_7_textEdited(const QString &arg1)
{
    (void)arg1;
    buttons[1].change();
}

void MainWindow::on_pushButton_17_clicked()
{
    buttons[1].insert(QChar(NEWLINE));
}

void MainWindow::on_pushButton_16_clicked()
{
    buttons[1].insert(QChar(TABULATOR));
}

void MainWindow::on_pushButton_18_clicked()
{
    buttons[1].remove();
}

void MainWindow::on_pushButton_14_clicked()
{
    buttons[1].restore();
}

void MainWindow::on_pushButton_15_clicked()
{
    buttons[1].save();
}


/* ************* Button 3 *********************************/

void MainWindow::on_lineEdit_8_textEdited(const QString &arg1)
{
    buttons[2].label( arg1);
}

void MainWindow::on_lineEdit_9_textEdited(const QString &arg1)
{
    (void)arg1;
    buttons[2].change();
}

void MainWindow::on_pushButton_22_clicked()
{
    buttons[2].insert(QChar(NEWLINE));
}

void MainWindow::on_pushButton_21_clicked()
{
    buttons[2].insert(QChar(TABULATOR));
}

void MainWindow::on_pushButton_23_clicked()
{
    buttons[2].remove();
}

void MainWindow::on_pushButton_19_clicked()
{
    buttons[2].restore();
}

void MainWindow::on_pushButton_20_clicked()
{
    buttons[2].save();
}

/* **************** Button 4 ************************* */


void MainWindow::on_lineEdit_10_textEdited(const QString &arg1)
{
    buttons[3].label( arg1);
}

void MainWindow::on_lineEdit_11_textEdited(const QString &arg1)
{
    (void)arg1;
    buttons[3].change();
}

void MainWindow::on_pushButton_27_clicked()
{
    buttons[3].insert(QChar(NEWLINE));
}

void MainWindow::on_pushButton_26_clicked()
{
    buttons[3].insert(QChar(TABULATOR));
}

void MainWindow::on_pushButton_28_clicked()
{
    buttons[3].remove();
}

void MainWindow::on_pushButton_24_clicked()
{
    buttons[3].restore();
}

void MainWindow::on_pushButton_25_clicked()
{
    buttons[3].save();
}

/*************** Button 5 *************************/

void MainWindow::on_lineEdit_12_textEdited(const QString &arg1)
{
    buttons[4].label( arg1);
}

void MainWindow::on_lineEdit_13_textEdited(const QString &arg1)
{
    (void)arg1;
    buttons[4].change();
}

void MainWindow::on_pushButton_32_clicked()
{
    buttons[4].insert(QChar(NEWLINE));
}

void MainWindow::on_pushButton_31_clicked()
{
    buttons[4].insert(QChar(TABULATOR));
}

void MainWindow::on_pushButton_33_clicked()
{
    buttons[4].remove();
}

void MainWindow::on_pushButton_29_clicked()
{
    buttons[4].restore();
}

void MainWindow::on_pushButton_30_clicked()
{
    buttons[4].save();
}

/***************** Button 6 ***********************/


void MainWindow::on_lineEdit_14_textEdited(const QString &arg1)
{
    buttons[5].label( arg1);
}

void MainWindow::on_lineEdit_15_textEdited(const QString &arg1)
{
    (void)arg1;
    buttons[5].change();
}

void MainWindow::on_pushButton_37_clicked()
{
    buttons[5].insert(QChar(NEWLINE));
}

void MainWindow::on_pushButton_36_clicked()
{
    buttons[5].insert(QChar(TABULATOR));
}

void MainWindow::on_pushButton_38_clicked()
{
    buttons[5].remove();
}

void MainWindow::on_pushButton_34_clicked()
{
    buttons[5].restore();
}

void MainWindow::on_pushButton_35_clicked()
{
    buttons[5].save();
}

/********************************* Button 7 ****************/


void MainWindow::on_lineEdit_16_textEdited(const QString &arg1)
{
    buttons[6].label( arg1);
}

void MainWindow::on_lineEdit_17_textEdited(const QString &arg1)
{
    (void)arg1;
    buttons[6].change();
}

void MainWindow::on_pushButton_42_clicked()
{
    buttons[6].insert(QChar(NEWLINE));
}

void MainWindow::on_pushButton_41_clicked()
{
    buttons[6].insert(QChar(TABULATOR));
}

void MainWindow::on_pushButton_43_clicked()
{
    buttons[6].remove();
}

void MainWindow::on_pushButton_39_clicked()
{
    buttons[6].restore();
}

void MainWindow::on_pushButton_40_clicked()
{
    buttons[6].save();
}

/********************** Button 8 *****************/


void MainWindow::on_lineEdit_18_textEdited(const QString &arg1)
{
    buttons[7].label( arg1);
}

void MainWindow::on_lineEdit_19_textEdited(const QString &arg1)
{
    (void)arg1;
    buttons[7].change();
}

void MainWindow::on_pushButton_47_clicked()
{
    buttons[7].insert(QChar(NEWLINE));
}

void MainWindow::on_pushButton_46_clicked()
{
    buttons[7].insert(QChar(TABULATOR));
}

void MainWindow::on_pushButton_48_clicked()
{
    buttons[7].remove();
}

void MainWindow::on_pushButton_44_clicked()
{
    buttons[7].restore();
}

void MainWindow::on_pushButton_45_clicked()
{
    buttons[7].save();
}

/*************** Button 9 ****************/

void MainWindow::on_lineEdit_20_textEdited(const QString &arg1)
{
    buttons[8].label( arg1);
}

void MainWindow::on_lineEdit_21_textEdited(const QString &arg1)
{
    (void)arg1;
    buttons[8].change();
}

void MainWindow::on_pushButton_52_clicked()
{
    buttons[8].insert(QChar(NEWLINE));
}

void MainWindow::on_pushButton_51_clicked()
{
    buttons[8].insert(QChar(TABULATOR));
}

void MainWindow::on_pushButton_53_clicked()
{
    buttons[8].remove();
}

void MainWindow::on_pushButton_49_clicked()
{
    buttons[8].restore();
}

void MainWindow::on_pushButton_50_clicked()
{
    buttons[8].save();
}

/**************** button 10 **************/

void MainWindow::on_lineEdit_22_textEdited(const QString &arg1)
{
    buttons[9].label( arg1);
}

void MainWindow::on_lineEdit_23_textEdited(const QString &arg1)
{
    (void)arg1;
    buttons[9].change();
}



void MainWindow::on_pushButton_57_clicked()
{
    buttons[9].insert(QChar(NEWLINE));
}

void MainWindow::on_pushButton_56_clicked()
{
    buttons[9].insert(QChar(TABULATOR));
}

void MainWindow::on_pushButton_58_clicked()
{
    buttons[9].remove();
}

void MainWindow::on_pushButton_54_clicked()
{
    buttons[9].restore();
}

void MainWindow::on_pushButton_55_clicked()
{
    buttons[9].save();
}
