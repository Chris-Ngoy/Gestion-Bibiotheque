#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Définition des structures de données
typedef struct {
    int id;
    char titre[100];
    char auteur[100];
    int annee;
    int disponible; // 1 si disponible, 0 sinon
} Livre;

typedef struct {
    int id;
    char nom[100];
} Emprunteur;

typedef struct {
    int idLivre;
    int idEmprunteur;
    char dateEmprunt[11];
    char dateRetour[11];
} Emprunt;

// Définition des constantes
#define MAX_LIVRES 100
#define MAX_EMPRUNTS 100
#define MAX_EMPRUNTEURS 100

// Déclaration des variables globales
Livre livres[MAX_LIVRES];
int nbLivres = 0;
Emprunt emprunts[MAX_EMPRUNTS];
int nbEmprunts = 0;
Emprunteur emprunteurs[MAX_EMPRUNTEURS];
int nbEmprunteurs = 0;


void ajouterLivre(int id, const char* titre, const char* auteur, int annee) {
    if (nbLivres >= MAX_LIVRES) {
        printf("Capacite maximale atteinte!\n");
        return;
    }
    livres[nbLivres].id = id;
    strcpy(livres[nbLivres].titre, titre);
    strcpy(livres[nbLivres].auteur, auteur);
    livres[nbLivres].annee = annee;
    livres[nbLivres].disponible = 1;
    nbLivres++;
    sauvegarderLivres("livres.txt");
}

void afficherLivres() {
    for (int i = 0; i < nbLivres; i++) {
        printf("ID: %d, Titre: %s, Auteur: %s, Annee: %d, Disponible: %d\n",
               livres[i].id, livres[i].titre, livres[i].auteur, livres[i].annee, livres[i].disponible);
    }
}

Livre* rechercherLivreParTitre(const char* titre) {
    for (int i = 0; i < nbLivres; i++) {
        if (strcmp(livres[i].titre, titre) == 0) {
            return &livres[i];
        }
    }
    return NULL;
}


void emprunterLivre(int idLivre, int idEmprunteur, const char* dateEmprunt, const char* dateRetour) {
    if (nbEmprunts >= MAX_EMPRUNTS) {
        printf("Capacite maximale atteinte!\n");
        return;
    }
    for (int i = 0; i < nbLivres; i++) {
        if (livres[i].id == idLivre && livres[i].disponible) {
            emprunts[nbEmprunts].idLivre = idLivre;
            emprunts[nbEmprunts].idEmprunteur = idEmprunteur;
            strcpy(emprunts[nbEmprunts].dateEmprunt, dateEmprunt);
            strcpy(emprunts[nbEmprunts].dateRetour, dateRetour);
            livres[i].disponible = 0;
            nbEmprunts++;
            sauvegarderLivres("livres.txt");
            sauvegarderEmprunts("emprunts.txt");
            return;
        }
    }
    printf("Livre non disponible!\n");
}

void retournerLivre(int idLivre) {
    for (int i = 0; i < nbEmprunts; i++) {
        if (emprunts[i].idLivre == idLivre) {
            for (int j = 0; j < nbLivres; j++) {
                if (livres[j].id == idLivre) {
                    livres[j].disponible = 1;
                    break;
                }
            }
            // Suppression de l'emprunt (simple version, ne gère pas les trous dans le tableau)
            for (int k = i; k < nbEmprunts - 1; k++) {
                emprunts[k] = emprunts[k + 1];
            }
            nbEmprunts--;
            sauvegarderLivres("livres.txt");
            sauvegarderEmprunts("emprunts.txt");
            return;
        }
    }
    printf("Emprunt non trouve!\n");
}


void ajouterEmprunteur(int id, const char* nom) {
    if (nbEmprunteurs >= MAX_EMPRUNTEURS) {
        printf("Capacite maximale atteinte!\n");
        return;
    }
    emprunteurs[nbEmprunteurs].id = id;
    strcpy(emprunteurs[nbEmprunteurs].nom, nom);
    nbEmprunteurs++;
    sauvegarderEmprunteurs("emprunteurs.txt");
}

Emprunteur* rechercherEmprunteurParNom(const char* nom) {
    for (int i = 0; i < nbEmprunteurs; i++) {
        if (strcmp(emprunteurs[i].nom, nom) == 0) {
            return &emprunteurs[i];
        }
    }
    return NULL;
}


void genererRapport() {
    printf("Rapport des livres empruntes:\n");
    for (int i = 0; i < nbEmprunts; i++) {
        printf("ID Livre: %d, ID Emprunteur: %d, Date Emprunt: %s, Date Retour: %s\n",
               emprunts[i].idLivre, emprunts[i].idEmprunteur, emprunts[i].dateEmprunt, emprunts[i].dateRetour);
    }
}


void sauvegarderLivres(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    for (int i = 0; i < nbLivres; i++) {
        fprintf(fichier, "%d,%s,%s,%d,%d\n", livres[i].id, livres[i].titre, livres[i].auteur, livres[i].annee, livres[i].disponible);
    }
    fclose(fichier);
}

void chargerLivres(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    while (fscanf(fichier, "%d,%[^,],%[^,],%d,%d\n", &livres[nbLivres].id, livres[nbLivres].titre, livres[nbLivres].auteur, &livres[nbLivres].annee, &livres[nbLivres].disponible) != EOF) {
        nbLivres++;
    }
    fclose(fichier);
}

void sauvegarderEmprunts(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    for (int i = 0; i < nbEmprunts; i++) {
        fprintf(fichier, "%d,%d,%s,%s\n", emprunts[i].idLivre, emprunts[i].idEmprunteur, emprunts[i].dateEmprunt, emprunts[i].dateRetour);
    }
    fclose(fichier);
}

void chargerEmprunts(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    while (fscanf(fichier, "%d,%d,%[^,],%[^\n]\n", &emprunts[nbEmprunts].idLivre, &emprunts[nbEmprunts].idEmprunteur, emprunts[nbEmprunts].dateEmprunt, emprunts[nbEmprunts].dateRetour) != EOF) {
        nbEmprunts++;
    }
    fclose(fichier);
}

void sauvegarderEmprunteurs(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    for (int i = 0; i < nbEmprunteurs; i++) {
        fprintf(fichier, "%d,%s\n", emprunteurs[i].id, emprunteurs[i].nom);
    }
    fclose(fichier);
}

void chargerEmprunteurs(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    while (fscanf(fichier, "%d,%[^\n]\n", &emprunteurs[nbEmprunteurs].id, emprunteurs[nbEmprunteurs].nom) != EOF) {
        nbEmprunteurs++;
    }
    fclose(fichier);
}


void centrerTexte(const char* texte) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    // Get console size
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // Calculate starting position
    int position = (columns - strlen(texte)) / 2;

    // Print spaces to center text
    for (int i = 0; i < position; i++) {
        printf(" ");
    }
    printf("%s\n", texte);
}

void colorerTexte(int couleur) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), couleur);
}


void afficherMenu() {
    colorerTexte(10); // Vert clair
    printf("Systeme de Gestion de Bibliotheque\n");
    printf("===================================\n");
    colorerTexte(7); // Blanc (par défaut)
    printf("1. Ajouter un livre\n");
    printf("2. Rechercher un livre\n");
    printf("3. Afficher tous les livres\n");
    printf("4. Emprunter un livre\n");
    printf("5. Retourner un livre\n");
    printf("6. Ajouter un emprunteur\n");
    printf("7. Generer un rapport\n");
    printf("8. Quitter\n");
}


int main() {
    // Charger les livres et les emprunts à partir des fichiers
    chargerLivres("livres.txt");
    chargerEmprunts("emprunts.txt");
    chargerEmprunteurs("emprunteurs.txt");

    int choix;
    do {
        afficherMenu();
        printf("Choix: ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                // Ajouter un livre
                {
                    int id, annee;
                    char titre[100], auteur[100];
                    system("cls");
                    printf("Ajout de livre\n");
                    printf("==============\n");
                    printf("ID: ");
                    scanf("%d", &id);
                    printf("Titre: ");
                    scanf("%s", titre);
                    printf("Auteur: ");
                    scanf("%s", auteur);
                    printf("Annee: ");
                    scanf("%d", &annee);
                    ajouterLivre(id, titre, auteur, annee);
                }
                break;
            case 2:
                // Rechercher un livre
                {
                    char titre[100];
                    printf("Titre: ");
                    scanf("%s", titre);
                    Livre* livre = rechercherLivreParTitre(titre);
                    if (livre) {
                        printf("Livre trouvé: ID: %d, Titre: %s, Auteur: %s, Annee: %d, Disponible: %d\n",
                               livre->id, livre->titre, livre->auteur, livre->annee, livre->disponible);
                    } else {
                        printf("Livre non trouvé\n");
                    }
                }
                break;
            case 3:
                afficherLivres();
                break;
            case 4:
                // Emprunter un livre
                {
                    int idLivre, idEmprunteur;
                    char dateEmprunt[11], dateRetour[11];
                    printf("ID Livre: ");
                    scanf("%d", &idLivre);
                    printf("ID Emprunteur: ");
                    scanf("%d", &idEmprunteur);
                    printf("Date Emprunt (dd/mm/yyyy): ");
                    scanf("%s", dateEmprunt);
                    printf("Date Retour (dd/mm/yyyy): ");
                    scanf("%s", dateRetour);
                    emprunterLivre(idLivre, idEmprunteur, dateEmprunt, dateRetour);
                }
                break;
            case 5:
                // Retourner un livre
                {
                    int idLivre;
                    printf("ID Livre: ");
                    scanf("%d", &idLivre);
                    retournerLivre(idLivre);
                }
                break;
            case 6:
                // Ajouter un emprunteur
                {
                    int id;
                    char nom[100];
                    printf("ID: ");
                    scanf("%d", &id);
                    printf("Nom: ");
                    scanf("%s", nom);
                    ajouterEmprunteur(id, nom);
                }
                break;
            case 7:
                genererRapport();
                break;
            case 8:
                // Sauvegarder les livres et les emprunts avant de quitter
                sauvegarderLivres("livres.txt");
                sauvegarderEmprunts("emprunts.txt");
                sauvegarderEmprunteurs("emprunteurs.txt");
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide!\n");
                break;
        }
    } while (choix != 8);
    return 0;
}
