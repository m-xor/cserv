#ifndef COMMANDS_H
#define COMMANDS_H

#include <QString>

class Commands
{
public:
    Commands();

    static bool password(const QString& pwd);  //przyznanie dostępu
    static bool list(QList<QString>& lst); //lista zapisanych haseł
    static bool set(int bt, const QString& pwd=NULL); //ustawienie/kasowanie hasła
    static bool quit(); //wycofanie dostępu i zamknięcie urządzenia CDC

private:
    static QString filter(const QString& response);
    static QString clean(const QString& str);
};

#endif // COMMANDS_H
