#include "credential.h"
#include "commands.h"
#include <QList>
#include <QDebug>

QRegExp Credential::rx("[!-~]{0,150}");
QRegExpValidator Credential::validator(rx);


Credential::Credential()
{

}

bool Credential::getCredential(int bt, QString& cred)
{
    QList<QString> lst;

    if(!Commands::list(lst)) {
        return false;
    }

    if(lst.at(bt)!="-") {
        cred = Credential::device2app(lst.at(bt));
        return true;
    }
    return false;
}

bool Credential::setCredential(int bt, const QString& cred)
{
    QString str(Credential::app2device(cred));

    int pos = 0;
    if(validator.validate(str,pos)==QRegExpValidator::Invalid) {
        qDebug() << str << " invalid" << endl;
        return false;
    }

    return Commands::set(bt, str);
}

bool Credential::clearCredential(int bt)
{
    return Commands::set(bt);
}



QString Credential::app2device(const QString& str)
{
    QString res(str);

    res.replace("\\","\\\\").
            replace(QChar(TABULATOR),"\\t").
            replace("\t","\\t").
            replace(QChar(NEWLINE),"\\n").
            replace("\n","\\n").
            replace(" ","\\s");
    return res;
}

QString Credential::device2app(const QString& str)
{
    QString res(str);

    res.replace("\\\\","\\").
            replace("\\t", QChar(TABULATOR)).
            replace("\\n", QChar(NEWLINE)).
            replace("\\s"," ");
    return res;
}

bool Credential::validateCredential(const QString& cred)
{
    QString str(Credential::app2device(cred));
    int pos = 0;
    return validator.validate(str,pos)!=QRegExpValidator::Invalid;
}
