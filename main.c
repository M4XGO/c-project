#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

struct Couloir {
    int badgeEntre;
    int badgeSortie;
};

struct Frigo {
    int badgeFrigoEntre;
    int badgeFrigoSortie;
    int capteurTemp;
    int timer;
};

//variable globale
//variable qui va contenir la ligne du fichier de scénario
char line2[256];
//structure qui va contenir les variables de scénario
struct Frigo frigoScenario;
//structure qui va contenir les variables de scénario
struct Couloir couloirScenario;

//chemin des fichiers à changer en fonction de l'architecture matériel
char chemin[100] = "C:/Users/theop/Desktop/ESGI/B2/C_avance/code/c-project/textFile/scenario.txt";
char chemin2[100] = "C:/Users/theop/Desktop/ESGI/B2/C_avance/code/c-project/Log/log.txt";

//fonction qui attends un certain nombre de secondes
void attendreSecondes(int secondes) {
    clock_t début = clock();
    clock_t maintenant;

    while (1) {
        maintenant = clock();
        double tempsPassé = (double)(maintenant - début) / CLOCKS_PER_SEC;

        if (tempsPassé >= secondes) {
            break;
        }
    }
}

//fonctions de vérification
int verifBadgeEntre(int badge) {
    if (badge == 1) {
        // printf("La personne est rentre\n");
        return 1;
    }
    else {
        // printf("La personne n'est pas rentre\n");
        return 0;
    }
}

int verifBadgeSortie(int badge) {
    if (badge == 1) {
        // printf("La personne est sorti\n");
        return 1;
    }
    else {
        // printf("ATTENTION : La personne n'est pas sorti\n");
        return 0;
    }
}

int verifTemps(int temp) {
    if (temp > -35) {
        // printf("ATTENTION : La température à remonté\n");
        return 0;
    }
    else {
        // printf("La température est bonne\n");
        return 1;
    }
}

int verifTime(int time) {
    attendreSecondes(time);
    if (time > 2) {
        // printf("ATTENTION : Le temps est dépassé, la personne à attendu %d secondes\n", time);
        return 0;
    }
    else {
        // printf("Le temps est bonla personne à attendu %d secondes\n", time);
        return 1;
    }
}

void ecrireScenario() {
    FILE *file = fopen(chemin, "w");

    if (file == NULL) {
        printf("Le fichier ne peut pas être ouvert\n");
        return;
    }

    srand(time(NULL));

    int badgeEntre = rand() % 2;
    int badgeSortie = rand() % 2;
    int badgeFrigoEntre = rand() % 2;
    int badgeFrigoSortie = rand() % 2;
    int capteurTemp = -5 - rand() % 36; // Valeur aléatoire entre -40 et -5
    int timer = 1 + rand() % 10; // Valeur aléatoire entre 1 et 10

    fprintf(file, "########Scénario#######\n badgeFrigoEntre: %d\n badgeFrigoSortie: %d\n capteurTemp: %d\n timer: %d\n badgeEntre: %d\n badgeSortie: %d\n",
             badgeFrigoEntre, badgeFrigoSortie, capteurTemp, timer, badgeEntre, badgeSortie);

    fclose(file);
}

//fonction de lecture de fichier
int lireFichier(const char *filename, const char *searchValue) {
    char line[256];  // Une ligne peut contenir jusqu'à 255 caractères, ajustez selon vos besoins
    int lineNumber = 1;
    int found = 0;

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Le fichier ne peut pas etre ouvert\n");
        return 1;
    }

    //recherche dans le fichier si la ligne contient la valeur recherchée
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, searchValue) != NULL) {
            found = 1;
            //copie de la ligne dans une variable globale
            strcpy(line2, line);
        }
        lineNumber++;
    }

    if (!found) {
        printf("Aucune ligne ne contient '%s'\n", searchValue);
    }

    fclose(file);

    return found; // Return whether the value was found or not
}

//fonction qui écrit dans le fichier log
int writeInFunction(char text[256]) {
    printf("texte : %s\n", text);
    char *filename = chemin2;

    // ouverture du fichier en mode "append" sinon le fichier est écrasé
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening the file %s", filename);
        return -1;
    }
    // écriture dans le fichier
    fprintf(fp, "%s\n", text);
    // fermeture du fichier
    fclose(fp);

    return 0;
}

//fonction qui retourne le/les derniers nombres d'une chaine de caractère en int
int retourneDernierNombre(char chaine[256]) {
    int resultat;
    sscanf(chaine + (strlen(chaine) - 1), "%d", &resultat);
    return resultat;
}

//fonction qui retourne la température en int
int retourneTemp(char chaine[256]) {
    int resultat;
    sscanf(chaine + (strlen(chaine) - 3), "%d", &resultat);
    return resultat;
}

//fonction qui retourne le temps en int + appelle la fonctiond d'attente
int retourneTime(char chaine[256]) {
    int resultat;
    sscanf(chaine + (strlen(chaine) - 1), "%d", &resultat);
    return resultat;
}

//fonction de vérification des scénarios
int verifScenario(int i) {
    int allVerifPass = 0;
    //Creation d'une variable logs qui va etre envoyé dans la fonction writeInFunction
    char logs[265];
    //concaténation du numéro de scénario
    char numScenario[256];
    sprintf(numScenario, "###### Scenario %d #######\n", i);

    char phrasePlusTempFrigo[256];
    char phrasePlusTimeFrigo[256];

    strcat(logs, numScenario);
    //vérification des badges entré
    if (verifBadgeEntre(couloirScenario.badgeEntre) == 0) {
        strcat(logs, "La personne n'est pas rentre dans le sas\n");
        allVerifPass++;
    }
    if (verifBadgeEntre(frigoScenario.badgeFrigoEntre) == 0) {
        strcat(logs, "La personne n'est pas rentre dans un frigo\n");
        allVerifPass++;
    }

    if (verifBadgeSortie(frigoScenario.badgeFrigoSortie) == 0) {
        strcat(logs, "La personne n'est pas sortie du frigo\n");
        allVerifPass++;
    }
    if (verifTime(frigoScenario.timer) == 0) {
        sprintf(phrasePlusTimeFrigo, "La personne est restee trop longtemps dans le frigo : %dsec\n", frigoScenario.timer);
        // printf("%s", phrasePlusTimeFrigo);
        strcat(logs, phrasePlusTimeFrigo);
        allVerifPass++;
    }
    if (verifTemps(frigoScenario.capteurTemp) == 0) {
        sprintf(phrasePlusTempFrigo, "La température du frigo est trop haute : %d degre\n", frigoScenario.capteurTemp);
        strcat(logs, phrasePlusTempFrigo);
        allVerifPass++;
    }
    if (verifBadgeSortie(couloirScenario.badgeSortie) == 0) {
        strcat(logs, "La personne n'est pas sorti du sas\n");
        allVerifPass++;
    }
    if (allVerifPass == 0) {
        //printf("Le scénario est bon\n");
        strcat(logs, "Le scénario est bon, tout s'est bien déroulé.\n");
        writeInFunction(logs);
        return 0;
    }
    writeInFunction(logs);
    return 1;
}

//fonction de lecture de scénario
void lectureScenario(int i) {
    //création de varibale pour pouvoir concaténer les noms des variables avec i 
    char badgeEntre[50];
    char badgeSortie[50];
    char badgeFrigoEntre[50];
    char badgeFrigoSortie[50];
    char capteurTemp[50];
    char timer[50];

    //concaténation
    sprintf(badgeEntre, "badgeEntre%d", i);
    sprintf(badgeSortie, "badgeSortie%d", i);
    sprintf(badgeFrigoEntre, "badgeFrigoEntre%d", i);
    sprintf(badgeFrigoSortie, "badgeFrigoSortie%d", i);
    sprintf(capteurTemp, "capteurTemp%d", i);
    sprintf(timer, "timer%d", i);

    //recherche des variables dans le fichier via les variable concaténés
    // + ajout dans la strucutre en passant par la variable globale line2
    int badgeSasEntreStruct = retourneDernierNombre(line2);
    couloirScenario.badgeEntre = badgeSasEntreStruct;

    int badgeSasSortieStruct = retourneDernierNombre(line2);
    couloirScenario.badgeSortie = badgeSasSortieStruct;

    int badgeFrigoEntreStruct1 = retourneDernierNombre(line2);
    frigoScenario.badgeFrigoEntre = badgeFrigoEntreStruct1;

    int badgeFrigoSortieStruct = retourneDernierNombre(line2);
    frigoScenario.badgeFrigoSortie = badgeFrigoSortieStruct;

    int capteurTempStruct = retourneTemp(line2);
    frigoScenario.capteurTemp = capteurTempStruct;

    int timerStruct = retourneTime(line2);
    frigoScenario.timer = timerStruct;

    //appel de la fonction de vérification
    verifScenario(i);
}

int main() {
    // Création du dossier "Log"
    mkdir("Log");

    // Génération du nom de fichier avec horodatage
    time_t rawtime;
    struct tm *timeinfo;
    char filename[100];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(filename, sizeof(filename), "Log/log_%Y-%m-%d_%H-%M-%S.txt", timeinfo);

    // Mise à jour du chemin du fichier log
    strcpy(chemin2, filename);

    //appel de la fonction d'écriture de scénario
    //ecrireScenario();
    //boucle qui va parcourir les i scénarios
    for (int i = 1; i < 2; i++) {
        //fonction de parcours de scénarios
        lectureScenario(i);
    }

    return 0;
}
