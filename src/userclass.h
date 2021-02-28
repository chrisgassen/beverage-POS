#include "includes.h"

/**\brief Klasse "Userclass" für das Speichern von Nutzern
 * In der GUI wird für jeden vorhandenen Nutzer ein Objekt dieser Klasse erzeugt.
 * Alle "Nutzer-Objekte" werden jedoch in einem Vektor während der Laufzeit gespeichert.
 * Für Persistenz werden die Objekte serialisiert und in eine Textdatei geschrieben.
 * Dementsprechend wird beim Programmstart zuerst die Textdatei ausgelesen.
 * Außerhalb des Vektors sollten nur temporär Objekte dieser Klasse aktiv sein, da auf die einzelnen Attribute meist über den Vektor zugegriffen wird.
 * Wird ein neues Objekt erstellt (also "neu neu" und nicht nur aus der Textdatei ausgelesen), so müssen die Attribute immer über die jeweiligen Methoden gesetzt werden.
 */
class User {
private:
    string name; // Name des Nutzers. Sollte einzigartig sein!
    double balance; // Kontostand des Nutzers. Darf nicht unter 0 sinken!
    int role; /**< Rolle soll nur die Werte 0(deaktiviert), 1(Nutzer) & 2(Admin) annehmen können!
                *  Deaktivierte Nutzer haben den Vorteil, dass sie weiterhin existieren, Notfalls wieder reaktivert werden können und somit der Kontostand immer noch da ist.
                *  Ein Nutzer besitzt die grundlegenden "Rechte" um mit der Software zu interagieren.
                *  Ein Admin besitzt höhere "Rechte" und kann die Kasse, Nutzer und die Software verwalten.
                */
public:
    User();
    string getName();
    double getBalance();
    int getRole();
    bool setBalance(double money);
    // the following methods should only be accessible to users with a role value > 1! (~admin)
    void createUser(string nName, int nRole);
    void editName(string nName);
    void editRole(int nRole);
};
