#ifndef CONFIG_H
#define CONFIG_H

#include <QWidget>
#include <QString>

class Config
{
public:
    Config();

    static void readSettings(QWidget* window);
    static void writeSettings(QWidget* window);
    static void readLabel(const QString& sn, int bt, QString& label);
    static void writeLabel(const QString& sn, int bt, const QString& label);
};

#endif // CONFIG_H
