#include "config.h"
#include <QSettings>
#include <QDebug>

Config::Config()
{

}

void Config::readSettings(QWidget* window)
{
    QSettings settings;
//    qDebug() << "settings read";
    settings.beginGroup(window->objectName());
    //Wielkość i położenie okna
    QVariant value = settings.value("position");
    if (!value.isNull())
    {
        window->move(value.toPoint());
//        qDebug() << "position not null";
    }

    value = settings.value("size");
    if (!value.isNull())
    {
        window->resize(value.toSize());
    }

    value = settings.value("fullScreen");
    if (!value.isNull() && value.toBool())
    {
        window->showFullScreen();
    }

    settings.endGroup();

}

void Config::writeSettings(QWidget* window)
{
    QSettings settings;
//    qDebug() << "settings write: window" << window->objectName() << "position" <<window->pos();
    settings.beginGroup(window->objectName());
    //położenie, wielkość okna
    settings.setValue("position", window->pos());
    settings.setValue("size", window->size());
    settings.setValue("fullScreen", window->isFullScreen());

    settings.endGroup();
}

void Config::readLabel(const QString& sn, int bt, QString& label)
{
    QString num = QString::number(bt);
    QSettings settings;

    settings.beginGroup(sn);
    label = settings.value(num).toString();
    settings.endGroup();
}

void Config::writeLabel(const QString& sn, int bt, const QString& label)
{
    QString num = QString::number(bt);
    QSettings settings;

    settings.beginGroup(sn);
    settings.setValue(num, label);
    settings.endGroup();
}
