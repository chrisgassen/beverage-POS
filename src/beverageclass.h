#include "includes.h"

/**\brief Klasse "Beverageclass" für das Speichern von Getränken
 * In der GUI wird für jedes vorhandene Getränk ein Objekt dieser Klasse erzeugt.
 * Alle "Getränke-Objekte" werden jedoch in einem Vektor während der Laufzeit gespeichert.
 * Für Persistenz werden die Objekte serialisiert und in eine Textdatei geschrieben.
 * Dementsprechend wird beim Programmstart zuerst die Textdatei ausgelesen.
 * Außerhalb des Vektors sollten nur temporär Objekte dieser Klasse aktiv sein, da auf die einzelnen Attribute meist über den Vektor zugegriffen wird.
 * Wird ein neues Objekt erstellt (also "neu neu" und nicht nur aus der Textdatei ausgelesen), so müssen die Attribute immer über die jeweiligen Methoden gesetzt werden.
 */
class Beverage {
	private:
        string name; // Name des Getränks. Sollte einzigartig sein!
		double price;
        int barcode; // Barcode des Getraenks. Muss einzigartg sein!
        int stock;
        int lastOrder;
	public:
        bool createBeverage(string nName, double nPrice, int nBarcode);
        bool editName(string nName);
        bool editPrice(double nPrice);
        bool editBarcode(int nBarcode);
        void setStock(int nStock);
        void setLastOrder(int nBottles);
		string getName();
		double getPrice();
		int getBarcode();
        int getStock();
        int getLastOrder();
};


