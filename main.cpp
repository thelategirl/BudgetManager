#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream>

using namespace std;

class Transaction {
private:
	string type;
	double montant;
	string description;
	string categorie;

public:
	Transaction(const string &t, double m, const string& d, const string& c):
		type(t), montant(m), description(d), categorie(c) {}

	void afficher() const {
		cout << "\nTransaction: " << categorie << " - " << type << " - " << montant << " - " << description << "." << endl;
	}

	string getType() const {
		return type;
	}

	double getMontant() const {
		cout << montant << " euros." << endl;
		return montant;
	}
	
	string getCategorie() const {
		return categorie;
	}
};

class BudgetManager {
private:
	vector<Transaction> transactions;
public:
	void ajouterTransaction(const Transaction& transaction) {
		transactions.push_back(transaction);
	}

	void afficherTransactions() const {
		if (transactions.empty()) {
			cout << "Aucune transaction enregistrée." << endl;
			return;
		}
		cout << "\n--- Liste des transactions ---" << endl;
		for(const Transaction& transaction: transactions) {
			transaction.afficher();
		}
	}

	double calculerSolde() const {
		double solde = 0.0;
		for (const Transaction& transaction : transactions) {
			if (transaction.getType() == "revenu") {
				solde += transaction.getMontant();
			}
			else if (transaction.getType() == "depense") {
				solde -= transaction.getMontant();
			}
		}
		cout << "Nouveau solde: ";
		return solde;
	}
};

string lireTexte(const string& message) {
	string valeur;
	cout << message;
	getline(cin, valeur);
	return valeur;
}

double lireMontant(const string& message) {
	double montant;
	cout << message;

	while(!(cin >> montant) || montant < 0) {
		cout << "Montant invalide. Recommencez : ";
		cin.clear();
		//ignorer les charcatères autres que les chiffres.
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return montant;
}

Transaction creerTransaction() {
	string type;
	do {
		type = lireTexte("Type (revenu/depense) : ");
	} while (type!= "revenu" && type != "depense");

	double montant = lireMontant("Montant: ");
	string description = lireTexte("Description: ");
	string categorie = lireTexte("Catégorie: ");
	Transaction x(type,montant,description,categorie);
	x.afficher();
	return x;
}

int main() {
	BudgetManager budget;
	int choix;

	do {
		cout << "\n ======GESTIONNAIRE DE BUDGET ======" << endl;
		cout << "1. Ajouter une transaction" << endl;
		cout << "2. Afficher les transactions " << endl;
		cout << "3. Afficher le solde "<< endl;
		cout << "0. Quitter "<< endl;
		cout << "Votre choix"<< endl;
		while (!(cin >> choix)) {
			cout << "Choix invalide. Recommencez :";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (choix) {
		case 1:
			budget.ajouterTransaction(creerTransaction());
			break;
		case 2:
			budget.afficherTransactions();
			break;
		case 3:
			cout << "Solde actuel : " << budget.calculerSolde() << endl;
			break;
		case 0:
			cout << "Fin du programme." << endl;
			cout << "Sauvegarde des données." << endl;
			std::ofstream fichier("budget.txt");
			if (fichier.is_open()){
			    fichier << budget.afficherTransactions(); 
			    fichier << calculerSolde(); 
			    fichier.close();
			cout << "Sauvegarde terminée." << endl;
			} else {
			    std::cerr << "Erreur d'ecriture dans le fichier." << endl; 
			}

			break;
		default:
			cout << "Choix invalide." << endl;
		}
	} while (choix!= 0);
	return 0;
}
