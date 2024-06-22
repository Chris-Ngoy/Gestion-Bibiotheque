1.	void afficherMenu() {
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
REPONSES :
La fonction afficherMenu() affiche le menu principal du système de gestion de bibliothèque avec des options pour différentes opérations. Voici une explication détaillée de ce que fait cette fonction:
Fonction afficherMenu()
 







 




  


2 . int main() {
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
REPONSES :
Ce code constitue le point d'entrée (main()) pour une application de gestion de bibliothèque. Il permet à un utilisateur d'interagir avec un système de gestion de livres, d'emprunteurs et d'emprunts via un menu textuel. Voici une explication détaillée de ce que fait chaque partie du code:
Fonction main()
1.	Chargement des données à partir des fichiers:
 


  

Description des cas individuels dans le switch:
•	Ajouter un livre:
 •  L'utilisateur entre les détails du livre, qui est ensuite ajouté via la fonction ajouterLivre().
•  Rechercher un livre:
       33 




3 .void centrerTexte(const char* texte) {
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
REPONSES :
    Résumé
La fonction centrerTexte :
1.	Obtient la taille de la fenêtre de la console.
2.	Calcule le point de départ horizontal pour centrer le texte.
3.	Imprime des espaces pour aligner le texte au centre.
4.	Affiche le texte.
Cette fonction est utile pour améliorer l'affichage des informations dans la console en rendant le texte visuellement plus agréable et structuré

