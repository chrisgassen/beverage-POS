#include "userwindow.h"
#include "ui_userwindow.h"
#include <QSignalMapper>
#include <QProcess>
#include <QDateTime>
#include <QTimer>

/**\brief Konstruktor der UI
 * Erstellt die UI mit bestimmten Einstllungen.
 * Es wird zum Beispiel die Startseite, Schriftarten, der Text in Textfeldern und der Status von Buttons festgelegt.
 * Anschließend werden die Datenbanken gelesen und aus den daraus gewonnen Informationen noch die Buttons für die Nutzer- und Getränkeauswahl erzeugt.
 * \param QWidget (Widget-Zeug von Qt)
 * \author Chris
 */
userwindow::userwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userwindow)
{
    // globale GUI-Einstellungen
    adminLoggedIn = false;
    activeUserID = -1; //stellt sicher, dass kein tatsächlich existierender Nutzer aktiv gesetzt ist
    ui->setupUi(this);
    QFont courierFont("Courier", 11, QFont::Medium, false);
    ui->textBrowser_clOutput->setFont(courierFont);
    ui->stackedWidget->setCurrentIndex(0);
    ui->label_topNotificationBar->setText("ags Getränkekasse");
    ui->label_balance->setText("");
    updateMenuButtons(false);
    ui->lineEdit_cl->setEchoMode(QLineEdit::Password);

    // Digitaluhr
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &userwindow::showTime);
    timer->start(1000);
    showTime();

    // Datenbanken lesen und daraus Buttons erstellen
    users = readUsersFromDB();
    beverages = readBeveragesFromDB();
    system = readSystemFromDB();
    updateUserGrid(users);
    updateBeverageGrid(beverages);
}

userwindow::~userwindow()
{
    delete ui;
}

//
// GUI Methoden
//
/**\brief Wandelt aktuelle Uhrzeit in String und lässt den Doppelpunkt blinken
 * \https://doc.qt.io/qt-5/qtwidgets-widgets-digitalclock-example.html
 * \author Till
 */
void userwindow::showTime() {
    QTime time = QTime::currentTime();
    QString sTime = time.toString("hh:mm");
    if ((time.second() % 2) == 0) {
        sTime[2] = ' ';
    }
    ui->lcd_clock->display(sTime);
}

/**\brief User-Oberflaeche wird dynamisch erstellt.
 * Für jeden Nutzer im vector wird ein Button erstellt.
 * Zum Layout gehören z.b. folgende Eigenschaften: Textfeldgroesse, Schriftart- und -groesse, Icon, etc.
 * Zusätzlich wird jeder Button mit einem Signal-Mapper verbunden.
 * \author Nicolas
 */
bool userwindow::updateUserGrid(vector<User> fUsers) {
    QFont latoFont("Lato", 12, QFont::Medium, false);
    QSignalMapper* usrmapper = new QSignalMapper();
    for (int i=0; i < fUsers.size(); i++) {
        int row=i/4;
        int column=i%4;
        QPushButton *usrbtn = new QPushButton();
        usrbtn->setFixedSize(100,60);
        usrbtn->setFont(latoFont);
        usrbtn->setIcon(QIcon("../res/icons/man-user.png"));
        usrbtn->setIconSize(QSize(30, 30));
        usrbtn->setText(QString::fromStdString(fUsers[i].getName()));
        connect(usrbtn,SIGNAL(clicked(bool)),usrmapper,SLOT(map()));
        usrmapper->setMapping(usrbtn,i);
        ui->gridLayout_userselect->addWidget(usrbtn,row,column);
    }
    connect(usrmapper,SIGNAL(mapped(int)),this,SLOT(userButtonPressed(int)));
    return true;
}

/**\brief Getraenke-Oberflaeche wird dynamisch erstellt.
 * Für jedes Getränkeobjekt wird ein Button erstellt.
 * Zum Layout gehören z.b. folgende Eigenschaften: Textfeldgroesse, Schriftart- und -groesse, Icon, etc.
 * Bei niedrigem Getraenkestand (stock <= 5) wird Warnung ausgegeben; bei stock == 0 wird Button "deaktiviert".
 * Zusätzlich wird jeder Button mit einem Signal-Mapper verbunden.
 * \return Textfeld mit Warnung ueber niedrigen Getraenkestand
 * \author Nicolas
 */
bool userwindow::updateBeverageGrid(vector<Beverage> fBeverages) {
    QFont latoFont("Lato", 12, QFont::Medium, false);
    QSignalMapper* bvrmapper = new QSignalMapper();
    for (int i=0; i < fBeverages.size(); i++) {
        int row=i/3;
        int column=i%3;
        QPushButton *bvrbtn = new QPushButton();
        bvrbtn->setFixedSize(150,70);
        bvrbtn->setFont(latoFont);
        bvrbtn->setText(QString::fromStdString(fBeverages[i].getName()) + " [" + QString::number(fBeverages[i].getStock()) + "]");
        if (fBeverages[i].getStock() <= 5) {
            ui->label_infobox->setText("Es gibt niedrige Getränkestände!");
            if (fBeverages[i].getStock() == 0) {
                bvrbtn->setEnabled(false);
            }
        }
        connect(bvrbtn,SIGNAL(clicked(bool)),bvrmapper,SLOT(map()));
        bvrmapper->setMapping(bvrbtn,i);
        ui->gridLayout_beverageselect->addWidget(bvrbtn,row,column);
    }
    connect(bvrmapper,SIGNAL(mapped(int)),this,SLOT(beverageButtonPressed(int)));
    return true;
}
/**\brief rekursiv aufgerufenes Layout Setup, kann von Nutzerauswahl und von Getränkeauswahl aufgerufen werden
 * \return Widgets (Pushbutton)
 * \author Jan-Uwe
 */
bool userwindow::clearGrid(QLayout *layout)
{
    if (! layout) {
        return true;
    }
    while (auto item = layout->takeAt(0)) {
          delete item->widget();
          clearGrid(item->layout());
    }
}
/**\brief Schaltet den Zustand der Navigationsbuttons um
 * \Der Settingsbutton wird nur für den Betreiber/Admin aktiv gesetzt
 * \param bool status (true oder false)
 * \author Maximilian
 */
bool userwindow::updateMenuButtons(bool status)
{
    ui->pushButton_pageBack->setEnabled(status);
    ui->pushButton_history->setEnabled(status);
    ui->pushButton_addMoney->setEnabled(status);
    if (status == true && users[activeUserID].getRole() > 1) {
        ui->pushButton_settings->setEnabled(true);
    }
    else {
        ui->pushButton_settings->setEnabled(false);
    }
    return true;
}



//
// Backend Methoden
//

/**\brief Schreibt alle Nutzer mit ihren Attributen in eine Datei
 * (Serialisierung der Nutzer-Objekte)
 * Die Datei wird geöffnet und in jede Zeile wird jeweils ein Nutzer geschrieben.
 * Die verschiedenen Attribute eines jeden Nutzers werden durch Semikolons getrennt.
 * Wenn alle Objekte "abgeschrieben" wurden, wird die Datei geschlossen.
 * \param vector<User> fUser (der Methode wird der Vektor, der aus allen Nutzerobjekten besteht, übergeben)
 * \author Chris
 */
bool userwindow::writeUsersToDB(vector<User> fUser) {
    ofstream tmpUserDB;
    tmpUserDB.open("userDB.txt");
    if (tmpUserDB.is_open()) {
        for (int i=0; i < fUser.size(); i++) {
            tmpUserDB << fUser[i].getName() << ";" << fUser[i].getBalance() << ";" << fUser[i].getRole() << endl;
        }
    }
    else {
        return false;
    }
    tmpUserDB.close();
    return true;
}

/**\brief Schreibt alle Getränke mit ihren Attributen in eine Datei
 * (Serialisierung der Getränke-Objekte)
 * Die Datei wird geöffnet und in jede Zeile wird jeweils ein Getränk geschrieben.
 * Die verschiedenen Attribute eines jeden Getränks werden durch Semikolons getrennt.
 * Wenn alle Objekte "abgeschrieben" wurden, wird die Datei geschlossen.
 * \param vector<Beverage> fBeverage (der Methode wird der Vektor, der aus allen Getränkeobjekten besteht, übergeben)
 * \author Chris
 */
bool userwindow::writeBeveragesToDB(vector<Beverage> fBeverage) {
    ofstream tmpBeverageDB;
    tmpBeverageDB.open("beverageDB.txt");
    if (tmpBeverageDB.is_open()) {
        for (int i=0; i < fBeverage.size(); i++) {
            tmpBeverageDB << fBeverage[i].getName() << ";" << fBeverage[i].getPrice() << ";" << fBeverage[i].getBarcode() << ";" << fBeverage[i].getStock() << ";" << fBeverage[i].getLastOrder() << endl;
        }
    }
    else {
        return false;
    }
    tmpBeverageDB.close();
    return true;
}

/**\brief Schreibt die Systemeinstellungen in ein Textdokument
 * \param System
 * \author Maximilian
 */
bool userwindow::writeSystemToDB(System) {
    ofstream tmpSystemDB;
    tmpSystemDB.open("systemDB.txt");
    if (tmpSystemDB.is_open()) {
        tmpSystemDB << system.getPassword() << endl;
        tmpSystemDB << system.getvBalance() << endl;
    }
    else {
        exit(-1);
    }
    tmpSystemDB.close();
    return true;
}

/**\brief Liest alle Nutzer mit ihren Attributen aus einer Datei
 * (Deserialisierung der Nutzer-Objekte)
 * Die Datei wird geöffnet und jede Zeile einzeln gelesen.
 * Die jeweils ausgelesene Zeile wird anhand der Semikolons in kleinere Strings aufgetrennt.
 * Die jeweiligen Substrings werden je nach Attribut konvertiert und in einen temporären Nutzer geschrieben.
 * Der temporäre Nutzer wird anschließend in einem Vektor verstaut.
 * \return vector<User> fUser (gibt den Vektor, der alle Nutzerobjekte enthält, aus)
 * \author Chris
 */
vector<User> userwindow::readUsersFromDB() {
    vector<User> fUser;
    ifstream tmpUserDB;
    tmpUserDB.open("userDB.txt");
    if (tmpUserDB.is_open()) {
        while (tmpUserDB.good()) {
            User tmpUser;
            string sUOL; // sUOL = stringUserObjectLine
            size_t posFD, posSD; // FD=FirstDivider, SD=SecondDivider, a divider is the ";" symbol
            getline (tmpUserDB,sUOL);
            if (sUOL.empty()) {
                break;
            }
            else {
                posFD = sUOL.find(";");
                posSD = sUOL.find(";", posFD+1);
                string sName = sUOL.substr (0,posFD);
                string sBalance = sUOL.substr (posFD+1,posSD-1);
                string sRole = sUOL.substr (posSD+1);
                tmpUser.editName(sName);
                tmpUser.setBalance(-stod(sBalance));
                tmpUser.editRole(stoi(sRole));
                fUser.push_back(tmpUser);
            }
        }
    }
    tmpUserDB.close();
    return fUser;
}

/**\brief Liest alle Getränke mit ihren Attributen aus einer Datei
 * (Deserialisierung der Getränke-Objekte)
 * Die Datei wird geöffnet und jede Zeile einzeln gelesen.
 * Die jeweils ausgelesene Zeile wird anhand der Semikolons in kleinere Strings aufgetrennt.
 * Die jeweiligen Substrings werden je nach Attribut konvertiert und in ein temporäres Getränk geschrieben.
 * Das temporäre Getränk wird anschließend in einem Vektor verstaut.
 * \return vector<Beverage> fBeverage (gibt den Vektor, der alle Getränkeobjekte enthält, aus)
 * \author Nicolas
 */
vector<Beverage> userwindow::readBeveragesFromDB() {
    vector<Beverage> fBeverage;
    ifstream tmpBeverageDB;
    tmpBeverageDB.open("beverageDB.txt");
    if (tmpBeverageDB.is_open()) {
        while (tmpBeverageDB.good()) {
            Beverage tmpBeverage;
            string sBOL; // sUOL = stringBeverageObjectLine
            size_t pos1D, pos2D, pos3D, pos4D; // pos1D: position of first divider; a divider is the ";" symbol
            getline (tmpBeverageDB,sBOL);
            if (sBOL.empty()) {
                break;
            }
            else {
                pos1D = sBOL.find(";");
                pos2D = sBOL.find(";", pos1D+1);
                pos3D = sBOL.find(";", pos2D+1);
                pos4D = sBOL.find(";", pos3D+1);
                string sName = sBOL.substr (0,pos1D);
                string sPrice = sBOL.substr (pos1D+1,pos2D);
                string sBarcode = sBOL.substr (pos2D+1,pos3D);
                string sStock = sBOL.substr (pos3D+1,pos4D);
                string sLastOrder = sBOL.substr(pos4D+1);
                tmpBeverage.editName(sName);
                tmpBeverage.editPrice(stod(sPrice));
                tmpBeverage.editBarcode(stoi(sBarcode));
                tmpBeverage.setStock(stoi(sStock));
                tmpBeverage.setLastOrder(stoi(sLastOrder));
                fBeverage.push_back(tmpBeverage);
            }
        }
    }
    tmpBeverageDB.close();
    return fBeverage;
}

/**\brief Passwort und Guthaben des Systems werden aus der Datenbank(DB) ausgelesen
 * \return Objekt fSystem
 * \author Maximilian
 */
System userwindow::readSystemFromDB() {
    System fSystem;
    ifstream tmpSystemDB;
    tmpSystemDB.open("systemDB.txt");
    if (tmpSystemDB.is_open()) {
        string sPassword;
        string svBalance;
        getline (tmpSystemDB,sPassword);
        getline (tmpSystemDB,svBalance);
        if (svBalance.size() > 0) {
            fSystem.setPassword(sPassword);
            fSystem.setvBalance(stod(svBalance));
        }
    }
    tmpSystemDB.close();
    return fSystem;
}


//
// Slots
//

/**\brief Wenn der User-Button gedrueckt wurde, wird der aktive Nutzer gesetzt.
 * Zusätzlich werden Name und Kontostand ausgelesen und die GUI wird damit aktualisiert.
 * \param id ID des aktiven Users
 * \author Nicolas
 */
bool userwindow::userButtonPressed(int id)
{
    activeUserID = id; //set the active user
    QString usrname = QString::fromStdString(users[id].getName());
    QString usrbalance = QString::number(users[id].getBalance());
    ui->label_topNotificationBar->setText(usrname);
    ui->label_balance->setText(usrbalance + " €");
    updateMenuButtons(true);
    ui->stackedWidget->setCurrentIndex(1);
    return true;
}

/**\brief Kauft ein Getränk für den jeweiligen Nutzer
 *  Wird beim Klick auf einen Getränkeknopf aufgerufen und soll das jeweilige Getränk kaufen.
 *  Versucht das Geld vom Konto des Nutzers abzubuchen. Wenn das erolgreich war, wird das Getränk tatsächlich "überschrieben", d.h. tatsächlich der Bestand verringert.
 *  Anschließend werden noch die Änderungen in die Datenbanken geschrieben und das UI aktualisiert.
 * \return Textrückgabe (wenn nicht genug Guthaben)
 * \author Jan-Uwe
 */
bool userwindow::beverageButtonPressed(int id)
{
    double UserBalanceBeforePurchase = users[activeUserID].getBalance();
    users[activeUserID].setBalance(beverages[id].getPrice());
    if (UserBalanceBeforePurchase > users[activeUserID].getBalance() && beverages[id].getStock() > 0) {
        beverages[id].setStock(beverages[id].getStock()-1);
        writeUsersToDB(users);
        writeBeveragesToDB(beverages);
        ofstream transactionlog;
               transactionlog.open("transactionlog.txt", ios::out | ios::app);
               if (transactionlog.is_open()) {
                   QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd-hh:mm:ss");
                   transactionlog << timestamp.toStdString() << " | " << activeUserID << " | -" << beverages[id].getPrice() << "\t| " << users[activeUserID].getBalance() << "\t| " << beverages[id].getName() << endl;
               }
               else {
                   exit(-1);
               }
        transactionlog.close();
        clearGrid(ui->gridLayout_beverageselect);
        updateBeverageGrid(beverages);
        ui->label_topNotificationBar->setText("ags Getränkekasse");
        ui->label_balance->setText("");
        updateMenuButtons(false);
        ui->stackedWidget->setCurrentIndex(0);
        activeUserID = -1; // Nutzer wird ausgeloggt; -1 stellt sicher, dass kein tatsächlich existierender Nutzer mehr ausgewählt ist
    }
    else {
        ui->label_infobox->setText("Nicht mehr genug Geld vorhanden!");
        return false;
    }
    return true;
}

/**\brief Mit einem Klick auf diesen Button wird zur vorherigen Seite navigiert
 * \Je nach Ausgangsseite wird man auf eine andere Seite zurückgeleitet
 * \author Maximilian
 */
void userwindow::on_pushButton_pageBack_clicked()
{
    if (ui->stackedWidget->currentIndex() == 1) {
        ui->label_topNotificationBar->setText("ags Getränkekasse");
        ui->label_balance->setText("");
        ui->label_infobox->setText("");
        updateMenuButtons(false);
        ui->stackedWidget->setCurrentIndex(0);
    }
    else {
        ui->label_display->setText("");
        ui->label_error->setText("");
        ui->textBrowser_history->setText("");
        updateMenuButtons(true);
        ui->lineEdit_cl->setEchoMode(QLineEdit::Password);
        adminLoggedIn = false;
        ui->stackedWidget->setCurrentIndex(1);
    }
}

/**\brief Zeigt die Historie der Buchungen (gekauften Getränke)
 * Es wird in der Logdatei nach allen Buchungen des jeweils aktiven Nutzers gesucht und die jeweilige Buchung ausgegeben.
 * \author Chris
 */
void userwindow::on_pushButton_history_clicked()
{
    updateMenuButtons(false);
    ui->pushButton_pageBack->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(2);
    string usrID = to_string(activeUserID);
    size_t posUsrID = 20;
    ifstream transactionlog;
    transactionlog.open("transactionlog.txt");
    if (transactionlog.is_open()) {
        while (transactionlog.good()) {
            string transaction;
            getline (transactionlog,transaction);
            if (transaction.empty()) {
                break;
            }
            else {
                if (transaction.find(usrID, posUsrID) == posUsrID) {
                    ui->textBrowser_history->append(QString::fromStdString(transaction));
                }
            }
        }
    }
    transactionlog.close();
}
/**\brief Mit einem Klick auf diesen Button wird die Seite zum Aufladen des Guthaben angezeigt
 * \Zusätzlich wird eine TransaktionsID generiert
 * \author Maximilian
 */
void userwindow::on_pushButton_addMoney_clicked()
{
    updateMenuButtons(false);
    ui->pushButton_pageBack->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(3);
    QString ID;
    if (activeUserID < 10) { //Um die immer gleiche Länge von TransaktionsIDs zu gewährleisten wird die UserID notfalls um eine Null verlängert
        ID = "0" + QString::number(activeUserID);
    }
    else {
        ID = QString::number(activeUserID);
    }
    ui->label_transactionID->setText(ID + QDateTime::currentDateTime().toString("yyMMddhhmm"));
}
/**\brief Mit einem Klick auf den Button wird eine Null in das Label auf der Seite zum Aufladen des Guthabens hinzugefügt
 * \author Maximilian
 */
void userwindow::on_pushButton_0_clicked()
{
    QString newBalance = ui->label_display->text();
    ui->label_display->setText(newBalance + "0");
}
/**\brief Mit einem Klick auf den Button wird eine Eins in das Label auf der Seite zum Aufladen des Guthabens hinzugefügt
 * \author Maximilian
 */
void userwindow::on_pushButton_1_clicked()
{
    QString newBalance = ui->label_display->text();
    ui->label_display->setText(newBalance + "1");
}
/**\brief Mit einem Klick auf den Button wird eine Zwei in das Label auf der Seite zum Aufladen des Guthabens hinzugefügt
 * \author Maximilian
 */
void userwindow::on_pushButton_2_clicked()
{
    QString newBalance = ui->label_display->text();
    ui->label_display->setText(newBalance + "2");
}
/**\brief Mit einem Klick auf den Button wird eine Drei in das Label auf der Seite zum Aufladen des Guthabens hinzugefügt
 * \author Maximilian
 */
void userwindow::on_pushButton_3_clicked()
{
    QString newBalance = ui->label_display->text();
    ui->label_display->setText(newBalance + "3");
}
/**\brief Mit einem Klick auf den Button wird eine Vier in das Label auf der Seite zum Aufladen des Guthabens hinzugefügt
 * \author Maximilian
 */
void userwindow::on_pushButton_4_clicked()
{
    QString newBalance = ui->label_display->text();
    ui->label_display->setText(newBalance + "4");
}
/**\brief Mit einem Klick auf den Button wird eine Fünf in das Label auf der Seite zum Aufladen des Guthabens hinzugefügt
 * \author Maximilian
 */
void userwindow::on_pushButton_5_clicked()
{
    QString newBalance = ui->label_display->text();
    ui->label_display->setText(newBalance + "5");
}
/**\brief Mit einem Klick auf den Button wird eine Sechs in das Label auf der Seite zum Aufladen des Guthabens hinzugefügt
 * \author Maximilian
 */
void userwindow::on_pushButton_6_clicked()
{
    QString newBalance = ui->label_display->text();
    ui->label_display->setText(newBalance + "6");
}
/**\brief Mit einem Klick auf den Button wird eine Sieben in das Label auf der Seite zum Aufladen des Guthabens hinzugefügt
 * \author Maximilian
 */
void userwindow::on_pushButton_7_clicked()
{
    QString newBalance = ui->label_display->text();
    ui->label_display->setText(newBalance + "7");
}
/**\brief Mit einem Klick auf den Button wird eine Acht in das Label auf der Seite zum Aufladen des Guthabens hinzugefügt
 * \author Maximilian
 */
void userwindow::on_pushButton_8_clicked()
{
    QString newBalance = ui->label_display->text();
    ui->label_display->setText(newBalance + "8");
}
/**\brief Mit einem Klick auf den Button wird eine Neun in das Label auf der Seite zum Aufladen des Guthabens hinzugefügt
 * \author Maximilian
 */
void userwindow::on_pushButton_9_clicked()
{
    QString newBalance = ui->label_display->text();
    ui->label_display->setText(newBalance + "9");
}
/**\brief Mit einem Klick auf den Button wird ein Komma in das Label auf der Seite zum Aufladen des Guthabens hinzugefügt
 * \author Maximilian
 */
void userwindow::on_pushButton_colon_clicked()
{
    QString newBalance = ui->label_display->text();
    ui->label_display->setText(newBalance + ",");
}
/**\brief Mit einem Klick auf den Button wird die letzte Eingabe im Label geloescht
 * \author Maximilian
 */
void userwindow::on_pushButton_back_clicked()
{
    QString newBalance = ui->label_display->text();
    newBalance.chop(1);
    ui->label_display->setText(newBalance);
}
/**\brief Mit einem Klick auf den Button wird das Konto des Users mit dem eingegeben Geldbetrag aufgeladen
 * \Der gewünschte Geldbetrag wird ausgelesen, in einen Double konvertiert und dem Nutzer hinzugefügt
 * \Anschließend wird diese Transaktion in verschiedenen Logs niedergeschrieben und die veränderten Objekte werden in den jeweiligen Datenbanken gesichert
 * \author Maximilian
 */
void userwindow::on_pushButton_saveTransaction_clicked()
{
    QString sNewBalance = ui->label_display->text();
    QString sTransactionID = ui->label_transactionID->text();
    double dNewBalance;
    if (sNewBalance.contains(",")) {
        sNewBalance.replace(",",".");
        QString checkFormatting = sNewBalance.right(3);
        if (checkFormatting.contains(".")) {
            dNewBalance = sNewBalance.toDouble();
        }
        else {
            ui->label_error->setText("Fehler: Ungültiger Betrag!");
        }
    }
    else {
       dNewBalance = sNewBalance.toDouble();
    }
    users[activeUserID].setBalance(-dNewBalance);
    system.setvBalance(system.getvBalance()+dNewBalance);
    ofstream depositlog; //Transaktion in desositlog schreiben
    depositlog.open("depositlog.txt", ios::out | ios::app);
    if (depositlog.is_open()) {
        depositlog << sTransactionID.toStdString() << " | " << users[activeUserID].getName() << "\t| +" << dNewBalance << "\t| " << system.getvBalance() << endl;
    }
    else {
        exit(-1);
    }
    depositlog.close();
    ofstream transactionlog; //Transaktion in transactionlog schreiben
           transactionlog.open("transactionlog.txt", ios::out | ios::app);
           if (transactionlog.is_open()) {
               QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd-hh:mm:ss");
               transactionlog << timestamp.toStdString() << " | " << activeUserID << " | +" << dNewBalance << "\t| " << users[activeUserID].getBalance() << "\t| " << "AUFLADUNG" << endl;
           }
           else {
               exit(-1);
           }
    transactionlog.close();
    writeUsersToDB(users);
    writeSystemToDB(system);
    updateMenuButtons(true);
    ui->label_balance->setText(QString::number(users[activeUserID].getBalance()) + " €");
    ui->label_display->setText("");
    ui->label_error->setText("");
    ui->stackedWidget->setCurrentIndex(1);
}

/**\brief Zeigt das Einstellungs-Fenster
 * ... und setzt ein paar entsprechende Stati von Buttons und Textfeldern neu...
 * \author Chris
 */
void userwindow::on_pushButton_settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    updateMenuButtons(false);
    ui->pushButton_pageBack->setEnabled(true);
    ui->textBrowser_clOutput->setText("Bitte geben Sie unten das globale Passwort ein!");
}

/**\brief HYDRA (kümmert sich um die Erkennung der Kommandos)
 * Im Grunde wurde hier ein CLI in einem GUI verbrochen...
 * Das eingegebene Kommando wird in einen String geschrieben und dieser wird dann in eine Liste aus Strings unterteilt. In dieser Stringliste ist jedes eingegebene Wort ein einzelner String.
 * Im nächsten Schritt wird mit if-else Prüfungen bestimmt, welches Kommando gerade gewünscht ist. (Das erste Wort bestimmt jeweils das gewünschte Kommando)
 * (Es wurde if-else verwendet, da case-switch nur umständlich mit Strings klar kommt)
 * Im weiteren Verlauf werden entweder direkt die gewünschten Operationen ausgeführt und Ausgaben an die Oberfläche erfolgen...
 * ... oder die in den anderen Wörtern angegebenen Parameter werden noch überprüft, umgewandelt und der gewünschten Operation als Attribut(e) übergeben.
 * Mit diesem Wissen sollten die jeweiligen Blöcke ziemlich selbsterklärend sein.
 * Etwas speziell ist noch die Funktion zum Einloggen. Es kann zwar nur ein Admin auf die Einstellungen zugreifen, aber um ganz großen Unfug zu verhindern, sind die Einstellungen noch pro-forma durch ein Passwort geschützt. (Schließlich muss man sich zur besseren Usability als Nutzer ja nicht einloggen)
 * \author Chris
 */
void userwindow::on_lineEdit_cl_returnPressed()
{
    QString input = ui->lineEdit_cl->text();
    QStringList query = input.split(" ");
    if (adminLoggedIn) {
    // Start der Kommandos die nach dem Einloggen verfügbar sind
        if (query[0] != "setpw") {
            ui->textBrowser_clOutput->append("~$ " + input);
        }
        if (query[0] == "logout") {
            adminLoggedIn = false;
            ui->textBrowser_clOutput->append("Erfolgreich ausgeloggt.");
            ui->lineEdit_cl->setEchoMode(QLineEdit::Password);
            updateMenuButtons(true);
            ui->stackedWidget->setCurrentIndex(1);
        }
        else if (query[0] == "restart") {
            ui->textBrowser_clOutput->append("Programm wird neu gestartet...");
            writeUsersToDB(users); // sicherheitshalber noch alles abspeichern
            writeBeveragesToDB(beverages);
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }
        else if (query[0] == "shutdown") {
            ui->textBrowser_clOutput->append("Programm wird geschlossen...");
            writeUsersToDB(users); // sicherheitshalber noch alles abspeichern
            writeBeveragesToDB(beverages);
            qApp->quit();
        }
        else if (query[0] == "setpw") {
            ui->textBrowser_clOutput->append("~$ setpw *****");
            if (query.size() == 2) {
                string oldpw = system.getPassword();
                QString newpw = query[1];
                system.setPassword(newpw.toStdString());
                if (system.getPassword() == oldpw) {
                    ui->textBrowser_clOutput->append("Das Passwort wurde nicht geändert. War es lang genug?");
                }
                else {
                    ui->textBrowser_clOutput->append("Das Passwort wurde erfolgreich geändert!");
                    writeSystemToDB(system);
                }
            }
            else {
                ui->textBrowser_clOutput->append("Nicht genug oder zu viele Parameter für 'setpw'...");
            }
        }
        else if (query[0] == "help") {
            ui->textBrowser_clOutput->append("#### Hilfeseite des GK-Kommandozeilen-Tools ####");
            ui->textBrowser_clOutput->append("logout");
            ui->textBrowser_clOutput->append("   [Meldet Sie ab]");
            ui->textBrowser_clOutput->append("shutdown");
            ui->textBrowser_clOutput->append("   [Schließt das Programm]");
            ui->textBrowser_clOutput->append("restart");
            ui->textBrowser_clOutput->append("   [Startet das Programm neu]");
            ui->textBrowser_clOutput->append("setpw <neues Passwort>");
            ui->textBrowser_clOutput->append("   [Setzt ein neues globales Passwort]");
            ui->textBrowser_clOutput->append("   <neues Passwort>=(string)");
            ui->textBrowser_clOutput->append("help");
            ui->textBrowser_clOutput->append("   [Zeigt diese Hilfeseite an]");
            ui->textBrowser_clOutput->append("lsusr");
            ui->textBrowser_clOutput->append("   [Listet alle Nutzer auf]");
            ui->textBrowser_clOutput->append("addusr <Name> <Rolle>");
            ui->textBrowser_clOutput->append("   [Erstellt einen neuen Nutzer]");
            ui->textBrowser_clOutput->append("   <Name>=(string)");
            ui->textBrowser_clOutput->append("   <Rolle>=(int)");
            ui->textBrowser_clOutput->append("delusr <ID>");
            ui->textBrowser_clOutput->append("   [Löscht den Nutzer mit der angegebenen ID]");
            ui->textBrowser_clOutput->append("   <ID>=(int)");
            ui->textBrowser_clOutput->append("setrole <Nutzer-ID> <Rolle>");
            ui->textBrowser_clOutput->append("   [setzt die Rolle eines Nutzers neu]");
            ui->textBrowser_clOutput->append("   [0=deaktiviert, 1=nutzer, 2=admin]");
            ui->textBrowser_clOutput->append("   <ID>=(int)");
            ui->textBrowser_clOutput->append("   <Rolle>=(int)");
            ui->textBrowser_clOutput->append("lsbvr");
            ui->textBrowser_clOutput->append("   [Listet alle Getränke auf]");
            ui->textBrowser_clOutput->append("addbvr <Name> <Preis> <Barcode>");
            ui->textBrowser_clOutput->append("   [Erstellt ein neues Getränk]");
            ui->textBrowser_clOutput->append("   <Name>=(string)");
            ui->textBrowser_clOutput->append("   <Preis>=(double)");
            ui->textBrowser_clOutput->append("   <Barcode>=(int)");
            ui->textBrowser_clOutput->append("delbvr <ID>");
            ui->textBrowser_clOutput->append("   [Löscht das Getränk mit der angegeben ID]");
            ui->textBrowser_clOutput->append("   <ID>=(int)");
            ui->textBrowser_clOutput->append("setbvrprice <ID> <Preis>");
            ui->textBrowser_clOutput->append("   [Setzt den Preis eines Getränks neu]");
            ui->textBrowser_clOutput->append("   <ID>=(int)");
            ui->textBrowser_clOutput->append("   <Preis>=(double)");
            ui->textBrowser_clOutput->append("abvro <ID> <Anzahl>");
            ui->textBrowser_clOutput->append("   [Bucht eine gewünschte Anzahl an neuen");
            ui->textBrowser_clOutput->append("    Flaschen dem angegebenen Getränk hinzu]");
            ui->textBrowser_clOutput->append("   <ID>=(int)");
            ui->textBrowser_clOutput->append("   <Anzahl>=(int)");
            ui->textBrowser_clOutput->append("getconsumption");
            ui->textBrowser_clOutput->append("   [Zeigt die Änderung des Bestandes seit der");
            ui->textBrowser_clOutput->append("    letzten Getränkebestellung]");
            ui->textBrowser_clOutput->append("depositlog");
            ui->textBrowser_clOutput->append("   [Zeigt alle Einzahlungen aller Nutzer]");
            ui->textBrowser_clOutput->append("statement");
            ui->textBrowser_clOutput->append("   [Zeigt den aktuellen Kontostand der Kasse]");
            ui->textBrowser_clOutput->append("withdraw <Betrag>");
            ui->textBrowser_clOutput->append("   [Zieht virtuelles Guthaben von der Kasse ab,");
            ui->textBrowser_clOutput->append("    wenn das reale Geld für eine Bestellung");
            ui->textBrowser_clOutput->append("    verwendet wurde]");
            ui->textBrowser_clOutput->append("   <Betrag>=(double)");
            ui->textBrowser_clOutput->append("cleardeplog");
            ui->textBrowser_clOutput->append("   [Löscht sämtliche vorherige Einzahlungen.");
            ui->textBrowser_clOutput->append("    Sinvoll nach einem Kassensturz, damit beim");
            ui->textBrowser_clOutput->append("    nächsten Sturz nicht alte Einzahlungen");
            ui->textBrowser_clOutput->append("    überprüft werden.]");
            ui->textBrowser_clOutput->append("############## Ende der Hilfeseite #############");
        }
        else if (query[0] == "lsusr") {
            ui->textBrowser_clOutput->append("Liste aller Nutzer:");
            for (int i=0; i < users.size(); i++) {
                ui->textBrowser_clOutput->append("ID: " + QString::number(i) + " Name: " + QString::fromStdString(users[i].getName()));
            }
            ui->textBrowser_clOutput->append("Ende der Liste");
        }
        else if (query[0] == "lsbvr") {
            ui->textBrowser_clOutput->append("Liste aller Getränke:");
            for (int i=0; i < beverages.size(); i++) {
                ui->textBrowser_clOutput->append("ID: " + QString::number(i) + " | " + QString::fromStdString(beverages[i].getName()) + " | " + QString::number(beverages[i].getPrice()) + "€ | " + QString::number(beverages[i].getStock()) + " Flaschen");
            }
            ui->textBrowser_clOutput->append("Ende der Liste");
        }
        else if (query[0] == "setrole") {
            if (query.size() == 3) {
                int userid = query[1].toInt();
                int role = query[2].toInt();
                if (userid >= 0 && role >= 0) {
                    users[userid].editRole(role);
                    ui->textBrowser_clOutput->append("Nutzerrolle von " + QString::fromStdString(users[userid].getName()) + " erfolgreich geändert!");
                    writeUsersToDB(users);
                    ui->textBrowser_clOutput->append("Änderungen erfolgreich in der Datenbank gesichert.");
                }
                else {
                    ui->textBrowser_clOutput->append("Falsche Paramter für 'setrole'...");
                }
            }
            else {
                ui->textBrowser_clOutput->append("Nicht genug oder zu viele Parameter für 'setrole'...");
            }
        }
        else if (query[0] == "withdraw") {
            if (query.size() == 2) {
                double withdrawal = query[1].toDouble();
                double currentvBalance = system.getvBalance();
                if (withdrawal > 0 && currentvBalance >= withdrawal) {
                    system.setvBalance(currentvBalance-withdrawal);
                    ui->textBrowser_clOutput->append("Es wurden " + QString::number(withdrawal) + "€ abgebucht.");
                    ui->textBrowser_clOutput->append("Das Guthaben der Kasse beträgt jetzt: " + QString::number(system.getvBalance()) + "€");
                    writeSystemToDB(system);
                    ui->textBrowser_clOutput->append("Änderungen erfolgreich in der Datenbank gesichert.");
                    ui->textBrowser_clOutput->append("Wollen Sie die letzten Buchungen löschen?");
                    ui->textBrowser_clOutput->append("Nach einem Kassensturz ist dies zu empfehlen!");
                    ui->textBrowser_clOutput->append("Führen Sie dazu bitte 'cleardeplog' aus...");
                }
                else {
                    ui->textBrowser_clOutput->append("Nicht genug Geld in der Kasse...");

                }
            }
            else {
                ui->textBrowser_clOutput->append("Nicht genug oder zu viele Parameter für 'withdraw'...");
            }

        }
        else if (query[0] == "cleardeplog") {
            ofstream depositlog;
            QString sID = "00" + QDateTime::currentDateTime().toString("yyMMddhhmm");
            depositlog.open("depositlog.txt");
            if (depositlog.is_open()) {
                depositlog << sID.toStdString() << " | " << "Abbuchung durch Admin; neuer Kontostand [€]: " << system.getvBalance() << endl;
                depositlog << "---" << endl;
            }
            else {
                ui->textBrowser_clOutput->append("Probleme beim Öffnen der Datenbank...");
            }
            depositlog.close();
            ui->textBrowser_clOutput->append("Letzte Buchungen wurden gelöscht!");
        }
        else if (query[0] == "addusr") {
            if (query.size() == 3) {
                string name = query[1].toStdString();

                if (query[2] == "0" || query[2] == "1" || query[2] == "2") {
                    int role = query[2].toInt();
                    User newuser;
                    newuser.createUser(name,role);
                    users.push_back(newuser);
                    writeUsersToDB(users);
                    updateUserGrid(users);
                    ui->textBrowser_clOutput->append("Der neue Nutzer " + QString::fromStdString(name) + " wurde erstellt und der Nutzderdatenbank hinzugefügt.");
                }
                else {
                   ui->textBrowser_clOutput->append("Die eingegebene Rolle ist nicht gültig!");
                }
            }
            else {
                ui->textBrowser_clOutput->append("Nicht genug oder zu viele Parameter für 'adduser'...");
            }
        }
        else if (query[0] == "delusr") {
            if (query.size() == 2) {
                int id = query[1].toInt();
                users.erase(users.begin() + id);
                writeUsersToDB(users);
                clearGrid(ui->gridLayout_userselect);
                updateUserGrid(users);
                ui->textBrowser_clOutput->append("Nutzer wurde gelöscht und Datenbanken aktualisiert.");
            }
            else {
                ui->textBrowser_clOutput->append("Nicht genug oder zu viele Parameter für 'adduser'...");
            }
        }
        else if (query[0] == "abvro") {
            if (query.size() == 3) {
                int id = query[1].toInt();
                int order = query[2].toInt();
                if (id >= 0 && id < beverages.size() && order > 0) {
                    beverages[id].setLastOrder(beverages[id].getStock() + order);
                    beverages[id].setStock(beverages[id].getStock() + order);
                    writeBeveragesToDB(beverages);
                    clearGrid(ui->gridLayout_beverageselect);
                    updateBeverageGrid(beverages);
                    ui->textBrowser_clOutput->append("Neuer Bestand von " + QString::fromStdString(beverages[id].getName()) + ": " + QString::number(beverages[id].getStock()));
                }
                else {
                    ui->textBrowser_clOutput->append("Unbekanntes Getränk, oder die Anzahl der hinzuzufügenden Getränke ist kleiner/gleich 0");
                }
            }
            else {
                ui->textBrowser_clOutput->append("Nicht genug oder zu viele Parameter für 'abvro'...");
            }
        }
        else if (query[0] == "getstock") {
            if (query.size() == 2) {
                int id = query[1].toInt();
                if (id >= 0 && id < beverages.size()) {
                    ui->textBrowser_clOutput->append(QString::fromStdString(beverages[id].getName()) + ": " + QString::number(beverages[id].getStock()) + " Flaschen");
                }
                else {
                    ui->textBrowser_clOutput->append("Unbekanntes Getränk");
                }
            }
            else {
                ui->textBrowser_clOutput->append("Nicht genug oder zu viele Parameter für 'getstock'...");
            }
        }
        else if (query[0] == "addbvr") {
            if (query.size() == 4) {
                string name = query[1].toStdString();
                double price = query[2].toDouble();
                int barcode = query[3].toInt();
                Beverage newbeverage;
                newbeverage.createBeverage(name,price,barcode);
                beverages.push_back(newbeverage);
                writeBeveragesToDB(beverages);
                clearGrid(ui->gridLayout_beverageselect);
                updateBeverageGrid(beverages);
                ui->textBrowser_clOutput->append("Getränk wurde hinzugefügt und Datenbank aktualisiert.");
            }
            else {
                ui->textBrowser_clOutput->append("Nicht genug oder zu viele Parameter für 'addbvr'...");
            }
        }
        else if (query[0] == "delbvr") {
            if (query.size() == 2) {
                int id = query[1].toInt();
                beverages.erase(beverages.begin() + id);
                writeBeveragesToDB(beverages);
                clearGrid(ui->gridLayout_beverageselect);
                updateBeverageGrid(beverages);
                ui->textBrowser_clOutput->append("Getränk wurde gelöscht und Datenbanken aktualisiert.");
            }
            else {
                ui->textBrowser_clOutput->append("Nicht genug oder zu viele Parameter für 'delbvr'...");
            }
        }
        else if (query[0] == "setbvrprice") {
            if (query.size() == 3) {
                int id = query[1].toInt();
                double price = query[2].toDouble();
                beverages[id].editPrice(price);
                writeBeveragesToDB(beverages);
                clearGrid(ui->gridLayout_beverageselect);
                updateBeverageGrid(beverages);
                ui->textBrowser_clOutput->append("Neuer Getränkepreis wurde gespeichert.");
            }
            else {
                ui->textBrowser_clOutput->append("Nicht genug oder zu viele Parameter für 'setbvrprice'...");
            }
        }
        else if (query[0] == "getconsumption") {
            ui->textBrowser_clOutput->append("|=====Verbrauchsliste=====|");
            for (int i=0; i < beverages.size(); i++) {
                if (beverages[i].getLastOrder() > 0) {
                    double stock = beverages[i].getStock();
                    double lastOrder = beverages[i].getLastOrder();
                    double reference = 25 * (stock / lastOrder);
                    char cBar[26];
                    //ui->textBrowser_clOutput->append(QString::number(reference));
                    for (int i = 1; i <= 25; i++) {
                        if (i < reference) {
                            if (i+1 < reference || i == 24){
                                cBar[i-1] = '=';
                            }
                            else {
                                cBar[i-1] = '<';
                            }
                        }
                        else {
                            if (reference == 25) {
                                cBar[i-1] = '=';
                            }
                            else {
                                cBar[i-1] = ' ';
                            }
                        }
                    }
                    string sBar(cBar);
                    ui->textBrowser_clOutput->append("|" + QString::fromStdString(sBar) + "| " + QString::fromStdString(beverages[i].getName()) + " (" + QString::number(beverages[i].getStock()) + "/" + QString::number(beverages[i].getLastOrder()) + ")");
                }
                else {
                    ui->textBrowser_clOutput->append("Noch keine Bestellung von " + QString::fromStdString(beverages[i].getName()) + " vorhanden...");
                }

            }
            ui->textBrowser_clOutput->append("|===Ende Verbrauchsliste==|");
        }
        else if (query[0] == "statement"){
            ui->textBrowser_clOutput->append("allgemeines Guthaben der Getränkekasse: " + QString::number(system.getvBalance()) + "€");
        }
        else if (query[0] == "depositlog") {
            ui->textBrowser_clOutput->append("|===============Einzahlungsliste===============|");
            ifstream depositlog;
            depositlog.open("depositlog.txt");
            if (depositlog.is_open()) {
                while (depositlog.good()) {
                    string deposit;
                    getline (depositlog,deposit);
                    if (deposit.empty()) {
                        break;
                    }
                    else {
                        ui->textBrowser_clOutput->append(QString::fromStdString(deposit));

                    }
                }
            }
            depositlog.close();
            ui->textBrowser_clOutput->append("|==========Ende der Einzahlungsliste===========|");
        }
        else {
            ui->textBrowser_clOutput->append("Das Kommando wurde nicht erkannt.");
        }
    }
    // Ende der Kommandos
    else {
    // Login
        if (query[0] == QString::fromStdString(system.getPassword())) {
            ui->lineEdit_cl->setEchoMode(QLineEdit::Normal);
            adminLoggedIn = true;
            ui->textBrowser_clOutput->append("Erfolgreich eingeloggt.");
            ui->textBrowser_clOutput->append("Verfügbare Kommandos können mit 'help' aufgerufen werden.");
        }
        else {
            ui->textBrowser_clOutput->append("Falsches Passwort. Bitte versuchen Sie es erneut.");
        }
    }
    ui->lineEdit_cl->setText("");
}