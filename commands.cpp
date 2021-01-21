#include "commands.h"
#include <QList>
#include <QDebug>
#include <QString>
#include "devicesec.h"
#include <QRegularExpression>
#include <QInputDialog>

#define ENDOFRESPONSE "\\n_: "
#define PASS_EXPECTED_RESPONSE "Dostęp przyznany"
#define SET_EXPECTED_RESPONSE "Czekaj...Ok"
#define QUIT_EXPECTED_RESPONSE "Wyjście z konfiguratora"
#define AUTH_REVOKED "Brak uprawnień"

//clean echo and prompt off from the answer
static QRegularExpression filterRX("^[^\\n]+\\n+(?<payload>.+)\\n_: $",
                                   QRegularExpression::MultilineOption|
                                   QRegularExpression::DotMatchesEverythingOption|
                                   QRegularExpression::UseUnicodePropertiesOption);

//clean list style type off from one line of credentials' list
static QRegularExpression cleanRX("^[ [:digit:]][[:digit:]]\\. (?<payload>.+)*$",
                                  QRegularExpression::MultilineOption|
                                  QRegularExpression::DotMatchesEverythingOption);
static QList<QString> credList;
static bool dirty = true;


Commands::Commands()
{

}

bool Commands::password(const QString& pwd)
{
    QString command("PASS");
    command += (pwd=="") ? "" : " " + pwd;
    command += "\r";

    QString response(Commands::filter(DeviceSec::exchangeData(command)));

    return response == PASS_EXPECTED_RESPONSE;
}

bool Commands::list(QList<QString>& lst)
{
    if(dirty) {
        QString command("LST\r");
        QString response;

        response = Commands::filter(DeviceSec::exchangeData(command));
        for(int i=3;response==AUTH_REVOKED && i; --i) { //in case of auth has been revoked due to timeout
            bool ok;
            QString text = QInputDialog::getText(NULL,
                                                 DeviceSec::getDeviceName(),
                                                 "Upłynał czas. Ponownie wpisz hasło:",
                                                 QLineEdit::Password,
                                                 "",
                                                 &ok);
            if (!ok || text.isEmpty()) { //cancelled by user
                break;
            }
            if(Commands::password(text)) {
                response = Commands::filter(DeviceSec::exchangeData(command));
                qDebug() << "auth revoked:" << i << "LST payload:" << response << endl;
            }
        }
        if(response==AUTH_REVOKED) {
            return false;
        }

        QStringList payload = response.split(QLatin1Char('\n'));

        credList.clear();
        foreach(const QString& str, payload) {
            credList.append(Commands::clean(str));
        }

        dirty = false;
    }

    lst = credList;

    return true;
}

bool Commands::set(int bt, const QString& pwd)
{
    dirty = true;

    QString command("SET " + QString::number(bt));
    command += (pwd==NULL || pwd=="") ? "" : " " + pwd;
    command += "\r";
    QString response(Commands::filter(DeviceSec::exchangeData(command)));

    for(int i=3;response==AUTH_REVOKED && i; --i) { //in case of auth has been revoked due to timeout
        bool ok;
        QString text = QInputDialog::getText(NULL,
                                             DeviceSec::getDeviceName(),
                                             "Upłynał czas. Ponownie wpisz hasło:",
                                             QLineEdit::Password,
                                             "",
                                             &ok);
        if (!ok || text.isEmpty()) { //cancelled by user
            break;
        }
        if(Commands::password(text)) {
            response = Commands::filter(DeviceSec::exchangeData(command));
            qDebug() << "auth revoked:" << i << "SET answer:" << response << endl;
        }
    }

    return response == SET_EXPECTED_RESPONSE;
}

bool Commands::quit()
{
    QString command("QUIT\r");

    QString response(Commands::filter(DeviceSec::exchangeData(command)));

    return response == QUIT_EXPECTED_RESPONSE;
}

QString Commands::filter(const QString& response)
{
    QRegularExpressionMatch match = filterRX.match(response);
    QString ret(response);

    if(match.hasMatch()) {
        ret = match.captured("payload");
    }
    return ret;
}

QString Commands::clean(const QString& str)
{
    QRegularExpressionMatch match = cleanRX.match(str);
    QString ret(str);

    if(match.hasMatch()) {
        ret = match.captured("payload");
    }
    return ret;
}
