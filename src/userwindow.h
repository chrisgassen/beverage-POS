#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "includes.h"
#include "headers.h"

/**\brief Klasse "Userwindow" für das Anzeigen und die Interaktion mit der GUI
 * Erstellt das GUI (zum Teil dynamisch) und verbindet Eingaben über Signals und Slots mit verschiedenen Ausgaben.
 * Greift auf die Klassen "beverageclass", "userclass" und "systemclass" zu und managed die Objekte dieser Klassen (zum Teil in Vektoren).
 * Kümmert sich um die Persistenz der Daten.
 */
namespace Ui {
class userwindow;
}

class userwindow : public QMainWindow
{
    Q_OBJECT

public:
    // GUI Konstruktor & Destruktor
    explicit userwindow(QWidget *parent = nullptr);
    ~userwindow();
    // GUI Methoden
    void showTime();
    bool updateUserGrid(vector<User> fUsers);
    bool updateBeverageGrid(vector<Beverage> fBeverages);
    bool clearGrid(QLayout* layout);
    bool updateMenuButtons(bool status);

    // Zugriff auf Objekte anderer Klassen etc.
    System system;
    // Verwendung eines Vektors um die user/beverage-Objekte abzuspeichern, da ein Array einen gravierenden Nachteil mit sich bringt: Die Größe geht bei der Übergabe an eine Funktion verloren. Es wären also noch weitere Attribute nötig.
    // Zudem bringt der Vektor einige weitere Vorteile beim Umgang mit den Objekten (dynamische Größe, mehr Funktionen um mit den Objekten zu interagieren...)
    vector<User> users;
    vector<Beverage> beverages;

    // Backend Methoden
    bool writeUsersToDB(vector<User>);
    bool writeBeveragesToDB(vector<Beverage>);
    bool writeSystemToDB(System);
    vector<User> readUsersFromDB();
    vector<Beverage> readBeveragesFromDB();
    System readSystemFromDB();
    string convertUserID(int id);

public slots:
    bool userButtonPressed(int id);
    bool beverageButtonPressed(int id);

private:
    Ui::userwindow *ui;
    bool adminLoggedIn; // für das Einstellungs-Fenster wichtig: setzt fest ob ein Admin eingeloggt ist und erlaubt somit die Eingabe von Kommandos
    int activeUserID; // die Methode userButtonPressed(int id) bekommt zwar einmal durch Signal-Mapping den aktiven Nutzer, aber sämtliche andere Methoden wüssten nicht, wer gerade aktiv ist, also wird es in diesen int geschrieben. Beim "Ausloggen" muss also zwingend int=-1 erfolgen!!

private slots:
    void on_pushButton_pageBack_clicked();
    void on_pushButton_history_clicked();
    void on_pushButton_addMoney_clicked();
    void on_pushButton_0_clicked();
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_colon_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_saveTransaction_clicked();
    void on_pushButton_settings_clicked();
    void on_lineEdit_cl_returnPressed();
};

#endif // USERWINDOW_H
