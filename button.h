#ifndef BUTTON_H
#define BUTTON_H

#include <QLineEdit>
#include <QPushButton>



class Button
{
public:
    Button(
            int         btnId,
            QLineEdit   *lbl,
            QLineEdit   *credentials,
            QPushButton *newline,
            QPushButton *tabulator,
            QPushButton *rm,
            QPushButton *restor,
            QPushButton *sav
            );
    static void setParent(QWidget *parent);
    void populateButton();
    void clearButton();
    bool isSaved() const;

    void remove();
    void restore();
    void save();
    void change();
    void insert(QChar c);
    void label(const QString& lbl);

private:

    void changedCred();

    int btnId;
    QLineEdit *lbl;
    QLineEdit *credentials;
    QPushButton *newline;
    QPushButton *tabulator;
    QPushButton *rm;
    QPushButton *restor;
    QPushButton *sav;

    static QWidget  *parent;
};

#endif // BUTTON_H
