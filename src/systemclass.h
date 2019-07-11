#include "includes.h"

/**\brief Klasse "Systemclass" für das Speichern von Systemweiten Attributen.
 * Die GUI erstellt genau ein Objekt dieser Klasse beim Programmstart.
 * Die Inhalte der Attribute werden in einer Textdatei gesichert und dementsprechend beim Programmstart aus dieser auch gelesen.
 * \author Maximilian
 */
class System {
private:
    string password;
    double vBalance;  //entspricht dem Geld, dass durch das Einzahlen von Nutzergeld bar in der Kasse liegen sollte
public:
    void setPassword(string);
    void setvBalance(double);
    string getPassword();
    double getvBalance();
};

