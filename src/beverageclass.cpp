#include "includes.h"
#include "headers.h"

//
// set/edit-Methoden
//

/**\brief Methode zum Erstellen eines neuen Getraenks
 * \param nName, nPrice, nBarcode
 * Initialisiert ein Getraenk mit den Attributen Name, Price, Barcode
 * \return bool (true, wenn alle drei Methoden erfolgreich abgeschlossen wurden)
 * \warning Der Bestand ist erst einmal fest auf 0 gestellt
 * \author Till
 */
bool Beverage::createBeverage(string nName, double nPrice, int nBarcode) {
    bool name_ch,price_ch,barcode_ch;
    name_ch = editName(nName);
    price_ch = editPrice(nPrice);
    barcode_ch = editBarcode(nBarcode);
    stock = 0;
    if (name_ch && price_ch && barcode_ch) {
        return true;
    }
    else {
        return false;
    }
}

/**\brief Setzt den Namen eines neuen Getraenks
 * \param nName (Name des neuen Getraenks)
 * Ueberprueft nur grob, ob die Eingaben ungefaehr passen, also der Name zumindest ein paar Zeichen umfasst
 * \return bool (true, wenn Namensänderung erfolgreich)
 * \warning Vor Aufrufen dieser Funktion sollte geprueft werden, ob bereits ein Objekt mit dem neuen gewuenschten Getraenknamen exisitiert!
 * \author Till
 */
bool Beverage::editName(string nName) {
	if (nName != "") {
		name = nName;
        return true;
    }
    else {
        return false;
    }
}

/**\brief Setzt den Preis eines neuen Getraenks
 * \param nPrice (Preis des neuen Getraenks)
 * Ueberprueft, ob der eingegebene Preis positiv und groeßer 0 ist.
 * \return bool (true, wenn Preisänderung erfolgreich)
 * \author Till
 */
bool Beverage::editPrice(double price) {
    if (price >= 0) {
        this->price = price;
        return true;
    }
    else {
        return false;
    }
}

/**\brief Setzt den Barcode eines neuen Getraenks
 * \param nBarcode (Barcode des neuen Getraenks)
 * Ueberprueft, ob der eingegebene Barcode positiv und groeßer 0 ist.
 * \return bool (true, wenn Barcodeänderung erfolgreich)
 * \warning Vor Aufrufen dieser Funktion sollte geprueft werden, ob bereits ein Objekt mit dem neuen gewuenschten Barcode exisitiert!
 * \author Till
 */
bool Beverage::editBarcode(int nBarcode) {
	if (nBarcode >= 0) {
		barcode = nBarcode;
        return true;
    }
    else {
        return false;
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
