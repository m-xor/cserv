#ifndef CREDENTIAL_H
#define CREDENTIAL_H

#include <QString>
#include <QLineEdit>
#include <QRegExp>
#include <QRegExpValidator>

#define NEWLINE 0x21B5
#define TABULATOR 0x21E5
//#define TABULATOR 0x21B9

#define MAXLEN 150

class Credential
{
public:
    Credential();

    static bool getCredential(int bt, QString& cred);
    static bool setCredential(int bt, const QString& cred);
    static bool clearCredential(int bt);
    static bool validateCredential(const QString& cred);

private:
    //translates to/from plain encoded text expected/provided by device
    static QString app2device(const QString& str);
    static QString device2app(const QString& str);

    static QRegExp rx;
    static QRegExpValidator validator;

};

#endif // CREDENTIAL_H
