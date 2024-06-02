    #include <iostream>
    #include <chrono>
    #include <vector>
    #include <algorithm>
    #include <string>
    #include <ctime>
    #include <iomanip>
    #include <sstream>
    #include <conio.h>

    using namespace std;
    class Vol;
    class Avion;

    class Passager {
    public:
        int identifiant;
        string nom, prenom, telephone, adresse;
        int age;

        Passager(int id, string n, string p, int a, string tel, string adr)
            : identifiant(id), nom(n), prenom(p), age(a), telephone(tel), adresse(adr) {}

        void afficher() const {
            cout << "Passager " << identifiant << ": " << nom << " " << prenom << ", " << age << " ans, Tel: " << telephone << ", Adresse: " << adresse << endl;
        }

        static void creerPassagerSansVol() {
            int identifiant;
            string nom, prenom, telephone, adresse;
            int age;

            cout << "Enter Passenger Details:" << endl;
            cout << "ID: ";
            cin >> identifiant;
            cout << "First Name: ";
            cin >> nom;
            cout << "Last Name: ";
            cin >> prenom;
            cout << "Age: ";
            cin >> age;
            cout << "Telephone: ";
            cin >> telephone;
            cout << "Address: ";
            cin >> adresse;

            Passager passager(identifiant, nom, prenom, age, telephone, adresse);
            tableauPassagers.push_back(passager);

            cout << "Passenger created successfully!" << endl;
        }

        static void afficherPassagers() {
            cout << "Liste des passagers:" << endl;
            for (const auto& passager : tableauPassagers) {
                passager.afficher();
            }
        }
        

    private:
        static vector<Passager> tableauPassagers;

        friend class Vol;

    };

    vector<Passager> Passager::tableauPassagers;

    class Avion {
    public:
        string code, pilote, modele, date_fabrication;
        int capacite, nb_vols;

        Avion(string c, string pil, string mod, int cap, string date, int nb)
            : code(c), pilote(pil), modele(mod), capacite(cap), date_fabrication(date), nb_vols(nb) {}

        void afficher() const {
            cout << "Avion " << code << ": Pilote: " << pilote << ", Modèle: " << modele << ", Capacité: " << capacite << ", Fabriqué le " << date_fabrication << ", " << nb_vols << " vols effectués" << endl;
        }

        static void afficherAvions() {
            cout << "Liste des avions:" << endl;
            for (const auto& avion : tableauAvions) {
                avion.afficher();
            }
        }
        static void ajouterAvion() {
        string code, pilote, modele, date_fabrication;
        int capacite, nb_vols;

        cout << "Enter Aircraft Details:" << endl;
        cout << "Code: ";
        cin >> code;
        cout << "Pilot: ";
        cin >> pilote;
        cout << "Model: ";
        cin >> modele;
        cout << "Capacity: ";
        cin >> capacite;
        cout << "Manufacture Date: ";
        cin >> date_fabrication;
        cout << "Number of Flights: ";
        cin >> nb_vols;

        Avion avion(code, pilote, modele, capacite, date_fabrication, nb_vols);

        Avion::tableauAvions.push_back(avion);

        cout << "Aircraft added successfully!" << endl;
    }

        static vector<Avion> tableauAvions;
    };

    vector<Avion> Avion::tableauAvions;

    class Vol {
    public:
        Avion avion;
        vector<Passager> passagers;
        tm date_depart, date_arrivee;

        Vol(Avion a, vector<Passager> p, tm depart, tm arrivee)
            : avion(a), passagers(p), date_depart(depart), date_arrivee(arrivee) {}

        void afficher() const {
            cout << "Flight Information:" << endl;
            avion.afficher();
            cout << "Departure Date: " << formatDate(date_depart) << ", Arrival Date: " << formatDate(date_arrivee) << endl;
            cout << "Passenger List:" << endl;
            for (const auto& passager : passagers) {
                passager.afficher();
            }
            cout << "----------------------" << endl;
        }

        static void ajouterVol() {
            while (true) {
                string code, pilote, modele, date_fabrication, date_depart_str, date_arrivee_str;
                int capacite, nb_vols;

                cout << "Enter Flight Details:" << endl;
                cout << "Code: ";
                cin >> code;
                cout << "Pilot: ";
                cin >> pilote;
                cout << "Model: ";
                cin >> modele;
                cout << "Capacity: ";
                cin >> capacite;
                cout << "Manufacture Date: ";
                cin >> date_fabrication;
                cout << "Number of Flights: ";
                cin >> nb_vols;
                cout << "Departure Date (yyyy/mm/dd): ";
                cin >> date_depart_str;
                cout << "Arrival Date (yyyy/mm/dd): ";
                cin >> date_arrivee_str;

                Avion avion(code, pilote, modele, capacite, date_fabrication, nb_vols);
                Vol vol(avion, vector<Passager>(), parseDate(date_depart_str), parseDate(date_arrivee_str));

                char addPassenger;
                cout << "Add passengers to the flight? (y/n): ";
                cin >> addPassenger;

                if (addPassenger == 'y' || addPassenger == 'Y') {
                    ajouterPassager(vol);
                }

                tableauVols.push_back(vol);

                cout << "Flight added successfully!" << endl;

                char choix;
                cout << "Do you want to add another flight? (y/n): ";
                cin >> choix;

                if (choix != 'y' && choix != 'Y') {
                    break;  // Exit the loop if the user doesn't want to add another flight
                }
            }
        }

    static void ajouterPassager(Vol& vol) {
        int identifiant;
        string nom, prenom, telephone, adresse;
        int age;

        cout << "Enter Passenger Details:" << endl;
        cout << "ID: ";
        cin >> identifiant;
        cout << "First Name: ";
        cin >> nom;
        cout << "Last Name: ";
        cin >> prenom;
        cout << "Age: ";
        cin >> age;
        cout << "Telephone: ";
        cin >> telephone;
        cout << "Address: ";
        cin >> adresse;

        Passager passager(identifiant, nom, prenom, age, telephone, adresse);
        vol.passagers.push_back(passager);

        cout << "Passenger added to the flight successfully!" << endl;
    }

    static void modifierPassager() {
        string dateDepart;
        cout << "Enter Departure Date for Flight Modification (yyyy/mm/dd): ";
        cin >> dateDepart;

        for (auto& vol : tableauVols) {
            if (formatDate(vol.date_depart) == dateDepart) {
                cout << "Passengers in the flight with Departure Date " << dateDepart << ":" << endl;
                for (const auto& passager : vol.passagers) {
                    passager.afficher();
                }

                int idToModify;
                cout << "Enter the ID of the passenger you want to modify: ";
                cin >> idToModify;

                for (auto& passager : vol.passagers) {
                    if (passager.identifiant == idToModify) {
                        // Ask for modifications
                        cout << "Enter modified details for passenger " << idToModify << ":" << endl;
                        cout << "First Name: ";
                        cin >> passager.nom;
                        cout << "Last Name: ";
                        cin >> passager.prenom;
                        cout << "Age: ";
                        cin >> passager.age;
                        cout << "Telephone: ";
                        cin >> passager.telephone;
                        cout << "Address: ";
                        cin >> passager.adresse;

                        cout << "Passenger details modified successfully!" << endl;
                        return;
                    }
                }

                cout << "Passenger with ID " << idToModify << " not found in the flight." << endl;
                return;
            }
        }

        cout << "Flight with Departure Date " << dateDepart << " not found." << endl;
    }


        static void afficherVols() {
            cout << "Liste des vols:" << endl;
            for (const auto& vol : tableauVols) {
                vol.afficher();
            }
        }

        static string formatDate(const tm& date) {
            stringstream ss;
            ss << put_time(&date, "%Y/%m/%d");
            return ss.str();
        }

        static tm parseDate(const string& dateStr) {
            tm date = {};
            stringstream ss(dateStr);
            ss >> get_time(&date, "%Y/%m/%d");
            return date;
        }
        static void modifierDates() {
        string dateDepart;
        cout << "Enter Departure Date to modify (yyyy/mm/dd): ";
        cin >> dateDepart;

        for (auto& vol : tableauVols) {
            if (formatDate(vol.date_depart) == dateDepart) {
                cout << "Flight found with Departure Date " << dateDepart << ":" << endl;
                vol.afficher();

                string newDateDepart;
                cout << "Enter the new Departure Date (yyyy/mm/dd): ";
                cin >> newDateDepart;

                // Convert tm structures to time_t for comparison
                struct tm newDepartStruct = parseDate(newDateDepart);
                time_t newDepartTime = mktime(&newDepartStruct);

                // Check if the new departure date is later than the existing one
                if (newDepartTime > mktime(&vol.date_depart)) {
                    vol.date_depart = newDepartStruct;

                    cout << "Departure Date modified successfully!" << endl;
                    vol.afficher(); // Display the updated flight information
                    return;
                } else {
                    cout << "Error: The new Departure Date must be later than the existing one." << endl;
                    return;
                }
            }
        }

        cout << "Flight with Departure Date " << dateDepart << " not found." << endl;
    }
            static void ajouterOuSupprimerVolVecV() {
            cout << "1. Ajouter un vol dans VecV" << endl;
            cout << "2. Supprimer un vol de VecV" << endl;
            cout << "Choisissez une option: ";

            int choix;
            cin >> choix;

            string dateDepart;
            cout << "Entrez la date de départ du vol (yyyy/mm/dd): ";
            cin >> dateDepart;

            switch (choix) {
                case 1:
                    ajouterVolDansVecV(dateDepart);
                    break;

                case 2:
                    supprimerVolDeVecV(dateDepart);
                    break;

                default:
                    cout << "Option invalide." << endl;
                    break;
            }
        }

        static void ajouterVolDansVecV(const string& dateDepart) {
            auto it = find_if(tableauVols.begin(), tableauVols.end(), [dateDepart](const Vol& vol) {
                return formatDate(vol.date_depart) == dateDepart;
            });

            if (it != tableauVols.end()) {
                VecV.push_back(&(*it));
                cout << "Vol ajouté à VecV avec succès!" << endl;
            } else {
                cout << "Aucun vol trouvé avec la date de départ spécifiée." << endl;
            }
        }

        static void supprimerVolDeVecV(const string& dateDepart) {
            auto it = remove_if(VecV.begin(), VecV.end(), [dateDepart](Vol* vol) {
                return formatDate(vol->date_depart) == dateDepart;
            });

            VecV.erase(it, VecV.end());

            cout << "Vol supprimé de VecV avec succès!" << endl;
        }
        static void afficherVecV() {
        cout << "Vols dans VecV:" << endl;
        for (const auto& vol : VecV) {
            vol->afficher();
        }
        cout << "----------------------" << endl;
    }
    // Add this method inside the Vol class definition
static void ajouterPassagerExistant() {
    string dateDepart;
    cout << "Enter Departure Date for Flight (yyyy/mm/dd): ";
    cin >> dateDepart;

    auto it = find_if(tableauVols.begin(), tableauVols.end(), [dateDepart](const Vol& vol) {
        return formatDate(vol.date_depart) == dateDepart;
    });

    if (it != tableauVols.end()) {
        // Flight found, display passenger list
        cout << "Passengers in the flight with Departure Date " << dateDepart << ":" << endl;
        for (const auto& passager : it->passagers) {
            passager.afficher();
        }

        // Ask for passenger ID to add
        int idToAdd;
        cout << "Enter the ID of the existing passenger you want to add to the flight: ";
        cin >> idToAdd;

        // Find the passenger in the main list
        auto passagerIt = find_if(Passager::tableauPassagers.begin(), Passager::tableauPassagers.end(), [idToAdd](const Passager& passager) {
            return passager.identifiant == idToAdd;
        });

        if (passagerIt != Passager::tableauPassagers.end()) {
            // Passenger found, add to the flight
            it->passagers.push_back(*passagerIt);
            cout << "Passenger added to the flight successfully!" << endl;
        } else {
            cout << "Passenger with ID " << idToAdd << " not found in the main passenger list." << endl;
        }
    } else {
        cout << "Flight with Departure Date " << dateDepart << " not found." << endl;
    }
}
static void AffichePassVol() {
        int passagerId;
        cout << "Enter Passager ID to check for a flight: ";
        cin >> passagerId;

        for (const auto& vol : tableauVols) {
            auto it = find_if(vol.passagers.begin(), vol.passagers.end(), [passagerId](const Passager& passager) {
                return passager.identifiant == passagerId;
            });

            if (it != vol.passagers.end()) {
                // Passenger found in the flight, display flight information
                cout << "Passager with ID " << passagerId << " is in the following flight:" << endl;
                vol.afficher();
                return;
            }
        }

        cout << "Passager with ID " << passagerId << " is not in any flight." << endl;
    }
    static void moins10ans() {
        cout << "Passengers under 10 years old and their flight information (if any):" << endl;

        for (const auto& vol : tableauVols) {
            for (const auto& passager : vol.passagers) {
                if (passager.age < 10) {
                    // Display passenger details
                    cout << "Passenger " << passager.identifiant << " (Age: " << passager.age << "): ";
                    passager.afficher();
                    cout << "Flight Information:" << endl;
                    vol.afficher();
                    cout << "----------------------" << endl;
                }
            }
        }

        for (const auto& passager : Passager::tableauPassagers) {
            if (passager.age < 10) {
                // Display passenger details
                cout << "Passenger " << passager.identifiant << " (Age: " << passager.age << "): ";
                passager.afficher();
                cout << "----------------------" << endl;
            }
        }
    }
    static void showNextDayFlights() {
        cout << "Flights with Departure Date on the next day:" << endl;

        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        tm nextDay = *localtime(&now);
        nextDay.tm_mday += 1;  // Adding 1 day

        cout << "Next Day: " << formatDate(nextDay) << endl;

        // Display flights from tableauVols
        for (const auto& vol : tableauVols) {
            if (vol.date_depart.tm_year == nextDay.tm_year &&
                vol.date_depart.tm_mon == nextDay.tm_mon &&
                vol.date_depart.tm_mday == nextDay.tm_mday) {
                cout << "Flight Information:" << endl;
                vol.afficher();
                cout << "----------------------" << endl;
            }
        }

        // Display flights from VecV
        for (const auto* vol : VecV) {
            if (vol->date_depart.tm_year == nextDay.tm_year &&
                vol->date_depart.tm_mon == nextDay.tm_mon &&
                vol->date_depart.tm_mday == nextDay.tm_mday) {
                cout << "Flight Information (from VecV):" << endl;
                vol->afficher();
                cout << "----------------------" << endl;
            }
        }
    }



        static vector<Vol*> VecV;
        static vector<Vol> tableauVols;
    };

    vector<Vol> Vol::tableauVols;
    vector<Vol*> Vol::VecV;

    int main() {
        int choix;

        while (true) {
            system("cls");
            cout << "\nMenu:" << endl;
            cout << "1. Ajouter un passager" << endl;
            cout << "2. Ajouter un vol" << endl;
            cout << "3. Ajouter une avion" << endl;
            cout << "4. Afficher tous les passagers, avions, et vols" << endl;
            cout << "5. Modifier un passager dans un vol" << endl;
            cout << "6. Modifier date dans un vol" << endl;
            cout << "7. Ajouter/delete un vol à un tableau donne" << endl;
            cout << "8. affiche un vol à un tableau donne" << endl;
            cout << "9. Ajouter un passager existant à un vol" << endl;
            cout << "10. affiche les vol du passager" << endl;
            cout << "11. Afficher les passagers ayant moins de 10 ans" << endl;
            cout << "12.afficher les vol du du lendemain " << endl;
            cout << "0. Quitter" << endl;

            cout << "Choisissez une option: ";
            cin >> choix;

            switch (choix) {
                case 1:
                    Passager::creerPassagerSansVol();
                    break;

                case 2:
                    Vol::ajouterVol();
                    break;

                case 3:
                    Avion::ajouterAvion();
                    break;

                case 4:
                    Passager::afficherPassagers();
                    Avion::afficherAvions();
                    Vol::afficherVols();
                    break;

                case 5:
                    Vol::modifierPassager();
                    break;
                case 6:
                    Vol::modifierDates();
                    break;
                case 7:
                    Vol::ajouterOuSupprimerVolVecV();
                    break;
                case 8:
                    Vol::afficherVecV();
                    break; 
                case 9:
                    Vol::ajouterPassagerExistant();
                    break; 
                case 10:
                    Vol::AffichePassVol();
                    break; 
                case 11:
                    Vol::moins10ans();
                    break;
                case 12:
                    Vol::showNextDayFlights();
                    break;
                case 0:
                    // Quit the program
                    return 0;

                default:
                    cout << "Option invalide. Veuillez choisir une option valide." << endl;
            }
            if (choix != 0) {
                 cout << "Appuyez sur une touche pour revenir au menu principal...";
                 _getch();
            }
        }

        return 0;
    }