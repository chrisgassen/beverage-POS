#include "includes.h"
#include "headers.h"

//
// set/edit-Methoden
//


/**\brief Methode zum Erstellen eines neuen Getraenks
 * \param nName, nPrice, nBarcode
 * Initialisiert ein Getraenk mit den Attributen Name, Price, Barcode
 * \warning Der Bestand ist erst einmal fest auf 0 gestellt
 * \author Till
 */
bool Beverage::createBeverage(string nName, double nPrice, int nBarcode) {
	editName(nName);
	editPrice(nPrice);
	editBarcode(nBarcode);
    stock = 0;
    return true;
}

/**\brief Setzt den Namen eines neuen Getraenks
 * \param nName (Name des neuen Getraenks)
 * Ueberprueft nur grob, ob die Eingaben ungefaehr passen, also der Name zumindest ein paar Zeichen umfasst
 * \author Till
 * \warning Vor Aufrufen dieser Funktion sollte geprueft werden, ob bereits ein Objekt mit dem neuen gewuenschten Getraenknamen exisitiert!
 */
void Beverage::editName(string nName) {
	if (nName != "") {
		name = nName;
	}
}

/**\brief Setzt den Preis eines neuen Getraenks
 * \param nPrice (Preis des neuen Getraenks)
 * Ueberprueft, ob der eingegebene Preis positiv und groeßer 0 ist.
 * \author Till
 */
void Beverage::editPrice(double price) {
    if (price >= 0) {
        this->price = price;
	}
}

/**\brief Setzt den Barcode eines neuen Getraenks
 * \param nBarcode (Barcode des neuen Getraenks)
 * Ueberprueft, ob der eingegebene Barcode positiv und groeßer 0 ist.
 * \author Till
 * \warning Vor Aufrufen dieser Funktion sollte geprueft werden, ob bereits ein Objekt mit dem neuen gewuenschten Barcode exisitiert!
 */
void Beverage::editBarcode(int nBarcode) {
	if (nBarcode >= 0) {
		barcode = nBarcode;
    }
}

/**\brief Setzt den aktuellen Bestand der Getraenke
 * \param nStock Bestand der Getraenke
 * \author Nicolas
 */
void Beverage::setStock(int nStock)
{
    stock = nStock;
}

/**\brief Setzt den Bestand, der durch die aktuelle Bestellung entstanden ist
 * \param nBottles Anzahl der Getränke der aktuellen Bestellung (+ aktuellen Bestand)
 * \author Jan-Uwe
 */
void Beverage::setLastOrder(int nBottles)
{
    lastOrder = nBottles;
}

//
// get-Methoden
//

/**\brief Gibt den Namen eines Getraenks zurueck
 * \return name (als string)
 * \author Till
 */
string Beverage::getName() {
	return name;
}

/**\brief Gibt den Preis eines Nutzers zurueck
 * \return price (als double)
 * \author Till
 */
double Beverage::getPrice() {
	return price;
}

/**\brief Gibt den Barcode eines Getraenks zurueck
 * \return barcode (als int)
 * \author Till
 */
int Beverage::getBarcode() {
    return barcode;
}

/**\brief Gibt den aktuellen Bestand der Getraenke zurueck
 * \return stock (als int)
 * \author Nicolas
 */
int Beverage::getStock()
{
    return stock;
}

/**\brief Gibt den Bestand, der durch die letzte Buchung entstanden ist, zurück
 * \return lastOrder (als int)
 * \author Jan-Uwe
 */
int Beverage::getLastOrder()
{
    return lastOrder;
}
