#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 

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
char chemin2[100] = "C:/Users/theop/Desktop/ESGI/B2/C_avance/code/c-project/output/Log/log.txt";

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
    int timer = 1 + rand() % 5; // Valeur aléatoire entre 1 et 10

    fprintf(file, "########Scénario#######\n badgeFrigoEntre: %d\n badgeFrigoSortie: %d\n capteurTemp: %d\n timer: %d\n badgeEntre: %d\n badgeSortie: %d\n",
             badgeFrigoEntre, badgeFrigoSortie, capteurTemp, timer, badgeEntre, badgeSortie);

    fclose(file);
}

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

//fonction qui vide le fichier log au début du programme
void viderFichierLog(){
    FILE *fp = fopen(chemin2, "w");
    fclose(fp);
}

//fonctions de vérification
int verifBadgeEntre(int badge){
    if (badge == 1){
        // printf("La personne est rentré\n");
        return 1;
    }
    else{
        // printf("La personne n'est pas rentré\n");
        return 0;
    }
}

int verifBadgeSortie(int badge){
    if (badge == 1){
        // printf("La personne est sorti\n");
        return 1;
    }
    else{
        // printf("ATTENTION : La personne n'est pas sorti\n");
        return 0;
    }
}

int verifTemps(int temp){
    if (temp > -35){
        // printf("ATTENTIN : La température à remonté\n");
        return 0;    
    }else{
        // printf("La température est bonne\n");
        return 1;
    }
}

int verifTime(int time){
    

    attendreSecondes(time);
    if (time >2){
        // printf("ATTENTION : Le temps est dépassé, la personne à attendu %d secondes\n", time);
        return 0;
    }else
    {

        // printf("Le temps est bonla personne à attendu %d secondes\n", time);
        return 1;
    }
}

//fonction de lecture de fichier
int lireFichier(const char *filename, const char *searchValue) {
    char line[256];  // Une ligne peut contenir jusqu'à 255 caractères, ajustez selon vos besoins
    int lineNumber = 1;
    int found = 0;
  
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Le fichier ne peut pas être ouvert\n");
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

    return 0;
}


//fonction qui écrit dans le fichier log
int writeInFunction(char text[256])
{   printf("texte : %s\n", text);
    char *filename = chemin2;

    // ouverture du fichier en mode "append" sinon le fichier est écrasé
    FILE *fp = fopen(filename, "a");
    if (fp == NULL)
    {
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
int retourneDenierNombre (char chaine[256]){
    int resultat;
    sscanf(chaine + (strlen(chaine) - 2), "%d", &resultat);
    return resultat;
}

//fonction qui retourne la température en int
int retourneTemp (char chaine[256]){
    int resultat;
    sscanf(chaine + (strlen(chaine) - 4), "%d", &resultat);
    return resultat;
}


//fonction qui retourne le temps en int + appelle la fonctiond d'attente
int retourneTime (char chaine[256]){
    int resultat;
    // printf("chaine : %s\n", chaine);
    sscanf(chaine + (strlen(chaine) - 2), "%d", &resultat);
    // printf("resultat : %d\n", resultat);
    return resultat;
}

//fonction de vérification des scénarios
int verifScenario(){
    int allVerifPass = 0;
    //Creation d'une variable logs qui va etre envoyé dans la fonction writeInFunction
    char logs[265]; 
    //concaténation du numéro de scénario
    char numScenario[256];
    sprintf(numScenario,"###### Scenario #######\n");

    char phrasePlusTempFrigo[256];
    char phrasePlusTimeFrigo[256];

    strcat(logs, numScenario);
    //vérification des badges entré
    if (verifBadgeEntre(couloirScenario.badgeEntre) == 0){
        strcat(logs, "La personne n'est pas rentree dans le sas\n");
        allVerifPass++;
    }
    if (verifBadgeEntre(frigoScenario.badgeFrigoEntre) == 0){
        strcat(logs, "La personne n'est pas rentree dans un frigo\n");
        allVerifPass++;
    }
    
    if (verifBadgeSortie(frigoScenario.badgeFrigoSortie) == 0){
        strcat(logs, "La personne n'est pas sortie du frigo\n");
        allVerifPass++;
    }
    if (verifTime(frigoScenario.timer) == 0){
        sprintf(phrasePlusTimeFrigo, "La personne est restee trop longtemps dans le frigo : %dsec\n", frigoScenario.timer);
        // printf("%s", phrasePlusTimeFrigo);
        strcat(logs, phrasePlusTimeFrigo);
        allVerifPass++;
    }
    if (verifTemps(frigoScenario.capteurTemp) == 0){
        sprintf(phrasePlusTempFrigo, "La temperature du frigo est trop haute : %d degre\n", frigoScenario.capteurTemp);
        strcat(logs, phrasePlusTempFrigo);
        allVerifPass++;
    }
    if (verifBadgeSortie(couloirScenario.badgeSortie) == 0){
        strcat(logs, "La personne n'est pas sortie du sas\n");
        allVerifPass++;
    }
    if (allVerifPass == 0){
        //printf("Le scénario est bon\n");
        strcat(logs, "Le scenario est bon, tout s'est bien deroule.\n");
        writeInFunction(logs);
        return 0;
    }
    writeInFunction(logs);
    return 1;
}

//fonction de lecture de scénario
void lectureScenario(){
    
   

    //création de varibale pour pouvoir concaténer les noms des variables avec i 
    char badgeEntre[50];
    char badgeSortie[50];
    char badgeFrigoEntre[50];
    char badgeFrigoSortie[50];
    char capteurTemp[50];
    char timer[50];
    

    //concaténation
    sprintf(badgeEntre, "badgeEntre");
    sprintf(badgeSortie, "badgeSortie");
    sprintf(badgeFrigoEntre, "badgeFrigoEntre");
    sprintf(badgeFrigoSortie, "badgeFrigoSortie");
    sprintf(capteurTemp, "capteurTemp");
    sprintf(timer, "timer");

    //recherche des variables dans le fichier via les variable concaténés
    // + ajout dans la strucutre en passant par la variable globale line2
    int badgeSas1 = lireFichier(chemin, badgeEntre);
    int badgeSasEntreStruct = retourneDenierNombre(line2);
    couloirScenario.badgeEntre = badgeSasEntreStruct;


    int badgeSas2 = lireFichier(chemin, badgeSortie);
    int badgeSasSortieStruct = retourneDenierNombre(line2);
    couloirScenario.badgeSortie = badgeSasSortieStruct;

    int badgeFrigo1 = lireFichier(chemin, badgeFrigoEntre);
    int badgeFrigoEntreStruct1 = retourneDenierNombre(line2);
    frigoScenario.badgeFrigoEntre = badgeFrigoEntreStruct1;

    int badgeFrigo2 = lireFichier(chemin, badgeFrigoSortie);
    int badgeFrigoSortieStruct = retourneDenierNombre(line2);
    frigoScenario.badgeFrigoSortie = badgeFrigoSortieStruct;

    int capteurTemp1 = lireFichier(chemin, capteurTemp);
    int capteurTempStruct = retourneTemp(line2);
    frigoScenario.capteurTemp = capteurTempStruct;
    
    int timer1 = lireFichier(chemin, timer);
    int timerStruct = retourneTime(line2);
    frigoScenario.timer = timerStruct;

    //appel de la fonction de vérification
    verifScenario();
}



// Fonction pour créer un nouveau fichier log avec un horodatage
void creerNouveauFichierLog() {
    time_t rawtime;
    struct tm *timeinfo;
    char timestamp[20];
    char cheminLog[100] = "C:/Users/theop/Desktop/ESGI/B2/C_avance/code/c-project/output/Log/";

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", timeinfo);

    strcat(cheminLog, "log_");
    strcat(cheminLog, timestamp);
    strcat(cheminLog, ".txt");

    FILE *fp = fopen(cheminLog, "w");
    if (fp == NULL) {
        printf("Erreur lors de la création du fichier log\n");
        return;
    }
    fclose(fp);
}

int main() {
    creerNouveauFichierLog();
    viderFichierLog();
    ecrireScenario();
    lectureScenario();

    return 0;
}
