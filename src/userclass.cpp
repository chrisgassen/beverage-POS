#include "includes.h"
#include "headers.h"

// TODO: return statements with success/erros

/**\brief Konstruktor fuer User Objekte
 * Initialisiert einen Nutzer ohne Guthaben. Das Geld muss immer manuell hinzugefuegt werden!
 * \author Chris
 */
User::User() {
    balance = 0;
}

/**\brief Gibt den Namen eines Nutzers zurueck
 * \return Name als string
 * \author Chris
 */
string User::getName() {
    return name;
}

/**\brief Gibt den Kontostand eines Nutzers zurueck
 * \return Kontostand als double
 * \author Chris
 */
double User::getBalance() {
    return balance;
}

/**\brief Gibt die Rolle eines Nutzers zurueck
 * \return Rolle als int
 * \author Chris
 */
int User::getRole() {
    return role;
}

/**\brief Setzt den Kontostand neu und stellt sicher, dass es eine Positivkasse bleibt
 * \param money Betrag, der hinzugefuegt oder abgezogen wird
 * \return bool (quittiert den (Nicht) Erfolg)
 * \author Chris
 * \warning Damit Einzahlungen und Auszahlungen moeglich sind und trotzdem die Kasse immer positiv bleibt, muss Geld, das hinzugefügt werden soll, als negativer Wert der Funktion Ÿbergene werden
 */
bool User::setBalance(double money) {
    if (money <= balance) {
        balance -= money;
        return true;
    }
    else {
        return false;
    }
}

/**\brief Setzt den Namen und die Rolle eines neuen Nutzers
 * \param nName Name des neuen Nutzers
 * \param nRole Rolle des neuen Nutzers
 * Ueberprueft nur grob, ob die Eingaben ungefaehr passen, also die Rollen in den benutzten Bereich passen und der Name zumindest ein paar Zeichen umfasst.
 * Neue Nutzer koennen per Definition nicht als deaktivierter Nutzer erstellt werden! Der Nutzer muss also entweder zum normalen Nutzer oder zum Admin gemacht werden.
 * \author Chris
 * \warning Vor Aufrufen dieser Funktion sollte geprueft werden, ob bereits ein Objekt mit dem neuen gewuenschten Nutzernamen exisitiert!
 */
void User::createUser(string nName, int nRole) {
    if ((nRole == 1 || nRole == 2) && nName.length() > 2) {
        name = nName;
        role = nRole;
    }
}

/**\brief Aendert den Namen eines bereits existierenden Nutzers
 * \param nName neuer Name des Nutzers
 * Ueberprueft nur grob, ob die Eingabe ungefaehr passt, also der Name zumindest ein paar Zeichen umfasst.
 * \author Chris
 * \warning Vor Aufrufen dieser Funktion sollte geprueft werden, ob bereits ein Objekt mit diesem Nutzernamen existiert!
 */
void User::editName(string nName) {
    if (nName.length() > 2) {
        name = nName;
    }
}

/**\brief Aendert die Rolle eines bereits existierenden Nutzers
 * \param nRole neue Rolle des Nutzers
 * \author Chris
 */
void User::editRole(int nRole) {
    if (0 <= nRole && nRole <= 2) {
        role = nRole;
    }
}
