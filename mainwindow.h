#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "devicewidg.h"
#include "button.h"
#include <QList>

#define NUMBER_OF_BUTTONS 10

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_6_clicked();

    void on_comboBox_3_currentIndexChanged(int index);

    void on_pushButton_7_clicked();

    void on_pushButton_13_clicked();


    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_lineEdit_6_textEdited(const QString &arg1);

    void on_pushButton_12_clicked();

    void on_pushButton_11_clicked();

    void on_lineEdit_4_textEdited(const QString &arg1);


    void on_lineEdit_5_textEdited(const QString &arg1);

    void on_lineEdit_7_textEdited(const QString &arg1);

    void on_pushButton_17_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_actionZako_cz_triggered();

    void on_actionO_Qt_triggered();

    void on_actionO_triggered();

    void on_actionPomoc_triggered();

    void on_actionExtButton_triggered();


    void on_lineEdit_8_textEdited(const QString &arg1);

    void on_lineEdit_9_textEdited(const QString &arg1);

    void on_pushButton_22_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_lineEdit_10_textEdited(const QString &arg1);

    void on_lineEdit_11_textEdited(const QString &arg1);

    void on_pushButton_27_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_lineEdit_12_textEdited(const QString &arg1);

    void on_lineEdit_13_textEdited(const QString &arg1);

    void on_pushButton_32_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_lineEdit_14_textEdited(const QString &arg1);

    void on_lineEdit_15_textEdited(const QString &arg1);

    void on_pushButton_37_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_lineEdit_16_textEdited(const QString &arg1);

    void on_lineEdit_17_textEdited(const QString &arg1);

    void on_pushButton_42_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_40_clicked();

    void on_lineEdit_18_textEdited(const QString &arg1);

    void on_lineEdit_19_textEdited(const QString &arg1);

    void on_pushButton_47_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_45_clicked();

    void on_lineEdit_20_textEdited(const QString &arg1);

    void on_lineEdit_21_textEdited(const QString &arg1);

    void on_pushButton_52_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_53_clicked();

    void on_pushButton_49_clicked();

    void on_pushButton_50_clicked();

    void on_lineEdit_22_textEdited(const QString &arg1);

    void on_lineEdit_23_textEdited(const QString &arg1);

    void on_pushButton_57_clicked();

    void on_pushButton_56_clicked();

    void on_pushButton_58_clicked();

    void on_pushButton_54_clicked();

    void on_pushButton_55_clicked();

private:
    Ui::MainWindow *ui;

    DeviceWidg *devWidg;
    QList<Button> buttons;

};

#endif // MAINWINDOW_H
