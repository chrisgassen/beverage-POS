#include "includes.h"
#include "headers.h"

/**\brief Setzt ein neues Passwort
 * \param Es wird der String eines neuen Passwords übergeben
 * \author Maximilian
 */
void System::setPassword(string nPassword) {
    if (nPassword.size() > 3) {
        password = nPassword;
    }
}

/**\brief Setzt den Kontostand des Systems und stellt sicher, dass es eine Positivkasse bleibt
 * \param Es wird die Zahl des neuen Kontostands übergeben
 * \author Maximilian
 */
void System::setvBalance(double nvBalance) {
    if (nvBalance >= 0) {
        vBalance = nvBalance;
    }
}

/**\brief Gibt das aktuelle Passwort zurück
 * \return Es wird der String des Passworts zurückgegeben
 * \author Maximilian
 */
string System::getPassword() {
    return password;
}

/**\brief Gibt den aktuellen Kontostand zurück
 * \return Es wird die Zahl des neuen Kontostands zurückgegeben
 * \author Maximilian
 */
double System::getvBalance() {
    return vBalance;
}
