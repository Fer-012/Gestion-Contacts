#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure pour l'adresse
struct Adresse
{
    int numero;
    char nomRue[50];
    char codePostal[10];
    char ville[50];
    char pays[50];
};

// Structure pour un contact
struct Contact
{
    char nom[50];
    char prenom[50];
    int lienParente;
    char telDomicile[20];
    char telEntreprise[20];
    char gsm[20];
    char email[50];
    struct Adresse adresse;
    char dateInsertion[20];
    struct Contact *suivant; // Pour la liste chaînée
};

// Déclaration de la tête de la liste chaînée
struct Contact *listeContacts = NULL;
const char *relationshipChoices[] = {"Mere", "Pere", "Soeur", "Frere", "Cousin", "Parent", "Ami", "Relation personnelle", "Relation professionnelle", "Aucun"};

// Prototypes des fonctions
void ajouterContact();
void afficherContacts();
void afficherNombreContacts();
void consulterContact();
void modifierChamp(struct Contact *contact, int champ);
void modifierContact();
void supprimerContact();
void viderRepertoire();
void rechercherParNom();
void rechercheMulticritere();
void menu();

int main()
{
    int choix;

    do
    {
        menu();
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            ajouterContact();
            break;
        case 2:
            afficherContacts();
            break;
        case 3:
            afficherNombreContacts();
            break;
        case 4:
            consulterContact();
            break;
        case 5:
            modifierContact();
            break;
        case 6:
            supprimerContact();
            break;
        case 7:
            viderRepertoire();
            break;
        case 8:
            rechercherParNom();
            break;
        case 9:
            rechercheMulticritere();
            break;
        case 0:
            printf("Programme termine.\n");
            break;
        default:
            printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 0);

    return 0;
}

// Fonction pour ajouter un contact
void ajouterContact()
{
    struct Contact *nouveauContact = (struct Contact *)malloc(sizeof(struct Contact));
    if (nouveauContact == NULL)
    {
        printf("Erreur d'allocation memoire.\n");
        return;
    }

    printf("Nom : ");
    scanf(" %[^\n]", nouveauContact->nom);
    printf("Prenom : ");
    scanf(" %[^\n]", nouveauContact->prenom);
    // Define an array of relationship choices
    const char *relationshipChoices[] = {"Mere", "Pere", "Soeur", "Frere", "Cousin", "Parent", "Ami", "Relation personnelle", "Relation professionnelle", "Aucun"};

    // Display the list of relationship choices
    printf("Lien de parente:\n");
    for (int i = 0; i < 10; ++i)
    {
        printf("%d: %s\n", i, relationshipChoices[i]);
    }

    // Prompt user for input
    int userChoice;
    printf("Entrez le numero correspondant au lien de parente : ");
    scanf("%d", &userChoice);

    // Validate user input
    if (userChoice >= 0 && userChoice <= 9)
    {
        // Assign the selected relationship to nouveauContact->lienParente
        nouveauContact->lienParente = userChoice;
        printf("Vous avez choisi : %s\n", relationshipChoices[userChoice]);
    }
    else
    {
        printf("Choix invalide. Veuillez reessayer.\n");
        free(nouveauContact);
        return;
    }

    printf("Telephone domicile : ");
    scanf("%s", nouveauContact->telDomicile);
    printf("Telephone entreprise : ");
    scanf("%s", nouveauContact->telEntreprise);
    printf("GSM : ");
    scanf("%s", nouveauContact->gsm);
    printf("Email : ");
    scanf("%s", nouveauContact->email);
    printf("Adresse :\n");
    printf("Numero : ");
    scanf("%d", &nouveauContact->adresse.numero);
    printf("Nom de rue : ");
    scanf(" %[^\n]", nouveauContact->adresse.nomRue);
    printf("Code postal : ");
    scanf("%s", nouveauContact->adresse.codePostal);
    printf("Ville : ");
    scanf(" %[^\n]", nouveauContact->adresse.ville);
    printf("Pays : ");
    scanf(" %[^\n]", nouveauContact->adresse.pays);
    // printf("Date d'insertion : ");
    // scanf("%s", nouveauContact->dateInsertion);

    // Obtenir la date et l'heure actuelles
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(nouveauContact->dateInsertion, sizeof(nouveauContact->dateInsertion), "%Y-%m-%d %H:%M:%S", tm_info);

    nouveauContact->suivant = listeContacts;
    listeContacts = nouveauContact;

    printf("Contact ajoute avec succes.\n");
}

// Fonction pour afficher la liste des contacts triée par nom
void afficherContacts()
{
    if (listeContacts == NULL)
    {
        printf("Le repertoire est vide.\n");
        return;
    }

    // Copie de la liste pour ne pas la modifier
    struct Contact *copieListe = listeContacts;

    // Boucle pour chaque lien de parenté
    for (int parente = 0; parente <= 9; ++parente)
    {
        // Boucle pour chaque contact
        while (copieListe != NULL)
        {
            if (copieListe->lienParente == parente)
            {
                printf("%s %s \ntelephone domicile : %s \ntelephone Entreprise : %s \n",
                       copieListe->nom, copieListe->prenom, copieListe->telDomicile, copieListe->telEntreprise);
            }
            copieListe = copieListe->suivant;
        }
        // Réinitialiser la copie de la liste pour chaque lien de parente
        copieListe = listeContacts;
    }
}

// Fonction pour afficher le nombre de contacts
void afficherNombreContacts()
{
    int compteur = 0;
    struct Contact *temp = listeContacts;

    while (temp != NULL)
    {
        compteur++;
        temp = temp->suivant;
    }

    printf("Nombre de contacts : %d\n", compteur);
}

// Fonction pour consulter un contact
void consulterContact()
{
    char nomRecherche[50];
    printf("Entrez le nom du contact a consulter : ");
    scanf("%s", nomRecherche);

    struct Contact *temp = listeContacts;

    while (temp != NULL)
    {
        if (strcmp(temp->nom, nomRecherche) == 0)
        {
            // Afficher les détails du contact
            printf("Nom : %s\n", temp->nom);
            printf("Prenom : %s\n", temp->prenom);
            printf("Lien de parente : %s\n", relationshipChoices[temp->lienParente]);
            printf("Telephone domicile : %s\n", temp->telDomicile);
            printf("Telephone entreprise : %s\n", temp->telEntreprise);
            printf("GSM : %s\n", temp->gsm);
            printf("Email : %s\n", temp->email);
            printf("Adresse :\n");
            printf("Numero : %d\n", temp->adresse.numero);
            printf("Nom de rue : %s\n", temp->adresse.nomRue);
            printf("Code postal : %s\n", temp->adresse.codePostal);
            printf("Ville : %s\n", temp->adresse.ville);
            printf("Pays : %s\n", temp->adresse.pays);
            printf("Date d'insertion : %s\n", temp->dateInsertion);

            return;
        }
        temp = temp->suivant;
    }

    printf("Contact non trouve.\n");
}

// Fonction pour modifier un contact
void modifierContact()
{
    char nomRecherche[50];
    printf("Entrez le nom du contact a modifier : ");
    scanf("%s", nomRecherche);

    struct Contact *temp = listeContacts;

    while (temp != NULL)
    {
        if (strcmp(temp->nom, nomRecherche) == 0)
        {
            int champ;
            printf("Quel champ voulez-vous modifier ?\n");
            printf("1. Nom\n2. Prenom\n3. Lien de parente\n4. Telephone domicile\n5. Telephone entreprise\n6. GSM\n7. Email\n8. Adresse\n9. Date d'insertion\n");
            scanf("%d", &champ);

            // Appeler la fonction pour modifier le champ spécifié
            modifierChamp(temp, champ);

            printf("Contact modifie avec succes.\n");
            return;
        }
        temp = temp->suivant;
    }

    printf("Contact non trouve.\n");
}

// Fonction pour modifier un champ spécifique d'un contact
void modifierChamp(struct Contact *contact, int champ)
{
    switch (champ)
    {
    case 1:
        printf("Nouveau nom : ");
        scanf(" %[^\n]", contact->nom);
        break;
    case 2:
        printf("Nouveau prenom : ");
        scanf(" %[^\n]", contact->prenom);
        break;
    case 3:
        printf("Nouveau lien de parente (0: Mere, 1: Pere, ..., 9: Aucun) : ");
        scanf("%d", &contact->lienParente);
        break;
    case 4:
        printf("Nouveau telephone domicile : ");
        scanf("%s", contact->telDomicile);
        break;
    case 5:
        printf("Nouveau telephone entreprise : ");
        scanf("%s", contact->telEntreprise);
        break;
    case 6:
        printf("Nouveau GSM : ");
        scanf("%s", contact->gsm);
        break;
    case 7:
        printf("Nouvel email : ");
        scanf("%s", contact->email);
        break;
    case 8:
        printf("Nouvelle adresse :\n");
        printf("Numero : ");
        scanf("%d", &contact->adresse.numero);
        printf("Nom de rue : ");
        scanf(" %[^\n]", contact->adresse.nomRue);
        printf("Code postal : ");
        scanf("%s", contact->adresse.codePostal);
        printf("Ville : ");
        scanf(" %[^\n]", contact->adresse.ville);
        printf("Pays : ");
        scanf(" %[^\n]", contact->adresse.pays);
        break;
    case 9:
        // Vous pouvez ajouter la logique pour modifier la date d'insertion si nécessaire
        break;
    default:
        printf("Champ invalide.\n");
        break;
    }
}

// Fonction pour supprimer un contact
void supprimerContact()
{
    char nomRecherche[50];
    printf("Entrez le nom du contact a supprimer : ");
    scanf("%s", nomRecherche);

    struct Contact *courant = listeContacts;
    struct Contact *precedent = NULL;

    // Recherche du contact
    while (courant != NULL)
    {
        if (strcmp(courant->nom, nomRecherche) == 0)
        {
            // Le contact a été trouvé
            if (precedent == NULL)
            {
                // Supprimer le premier élément de la liste
                listeContacts = courant->suivant;
            }
            else
            {
                // Supprimer un élément au milieu ou à la fin de la liste
                precedent->suivant = courant->suivant;
            }

            free(courant); // Libérer la mémoire du contact supprimé
            printf("Contact supprime avec succes.\n");
            return;
        }

        precedent = courant;
        courant = courant->suivant;
    }

    printf("Contact non trouve.\n");
}

// Fonction pour vider le répertoire
void viderRepertoire()
{
    struct Contact *courant = listeContacts;
    struct Contact *suivant;

    while (courant != NULL)
    {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }

    listeContacts = NULL;
    printf("Repertoire vide avec succes.\n");
}

// Fonction pour rechercher un contact par nom
void rechercherParNom()
{
    char nomRecherche[50];
    printf("Entrez le nom du contact a rechercher : ");
    scanf("%s", nomRecherche);

    struct Contact *temp = listeContacts;

    while (temp != NULL)
    {
        if (strcmp(temp->nom, nomRecherche) == 0)
        {
            // Afficher les détails du contact
            printf("%s %s \ntelephone domicile : %s \ntelephone Entreprise : %s\n",
                   temp->nom, temp->prenom,temp->telDomicile,temp->telEntreprise);
            return;
        }
        temp = temp->suivant;
    }

    printf("Contact non trouve.\n");
}

// Fonction pour rechercher un contact par nom, prénom ou ville
void rechercheMulticritere()
{
    char critereRecherche[50];
    printf("Entrez le nom, prenom ou ville du contact a rechercher : ");
    scanf("%s", critereRecherche);

    struct Contact *temp = listeContacts;

    while (temp != NULL)
    {
        if (strcmp(temp->nom, critereRecherche) == 0 ||
            strcmp(temp->prenom, critereRecherche) == 0 ||
            strcmp(temp->adresse.ville, critereRecherche) == 0)
        {
            // Afficher les détails du contact
             printf("%s %s \ntelephone domicile : %s \ntelephone Entreprise : %s\n",
                   temp->nom, temp->prenom,temp->telDomicile,temp->telEntreprise);
            return;
        }
        temp = temp->suivant;
    }

    printf("Contact non trouve.\n");
}

// Fonction pour afficher le menu
void menu()
{
    printf("\n===== Menu =====\n");
    printf("1. Ajouter un contact\n");
    printf("2. Afficher la liste des contacts\n");
    printf("3. Afficher le nombre de contacts\n");
    printf("4. Consulter un contact\n");
    printf("5. Modifier un contact\n");
    printf("6. Supprimer un contact\n");
    printf("7. Vider le repertoire\n");
    printf("8. Rechercher par nom\n");
    printf("9. Recherche multicritere\n");
    printf("0. Quitter\n");
}