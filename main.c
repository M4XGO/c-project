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
char chemin[50] = "./textFile/scenario.txt";
char chemin2[50] = "./textFile/logs.txt";


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
int verifScenario(int i){
    int allVerifPass = 0;
    //Creation d'une variable logs qui va etre envoyé dans la fonction writeInFunction
    char logs[265]; 
    //concaténation du numéro de scénario
    char numScenario[256];
    sprintf(numScenario,"###### Scenario %d #   ######\n", i);

    char phrasePlusTempFrigo[256];
    char phrasePlusTimeFrigo[256];

    strcat(logs, numScenario);
    //vérification des badges entré du SAS
    switch(verifBadgeEntre(couloirScenario.badgeEntre))
    {
        case 0 :
            strcat(logs, "La personne n'est pas rentré dans le sas\n");
            allVerifPass++;
            printf("%d", i);
        case 1 :
            strcat(logs, "La personne est bien entrée dans le sas\n");

    }//verif badge entré porte frigo
    switch(verifBadgeEntre(frigoScenario.badgeFrigoEntre))
    {
        case 0 :
            strcat(logs, "La personne n'est pas rentré dans un frigo\n");
            allVerifPass++;
            printf("%d", i);
        case 1 :
            strcat(logs, "La personne est bien entrée dans le frigo\n");

    }
    //verif badge sortie porte frigo
    switch(verifBadgeSortie(frigoScenario.badgeFrigoSortie))
    {
        case 0 :
            strcat(logs, "La personne n'est pas sortie dans un frigo\n");
            allVerifPass++;
            printf("%d", i);
        case 1 :
            strcat(logs, "La personne est bien sortie dans le frigo\n");

    }
    //verif badge sortie porte sas
    switch(verifBadgeSortie(couloirScenario.badgeSortie))
    {
        case 0 :
            strcat(logs, "La personne n'est pas sortie du sas\n");
            allVerifPass++;
            printf("%d", i);
        case 1 :
            strcat(logs, "La personne est bien sortie du sas\n");

    }
    //verif timer
    switch(verifTime(frigoScenario.timer))
    {
        case 0 :
            sprintf(phrasePlusTimeFrigo, "La personne est resté trop longtemps dans le frigo : %dsec\n", frigoScenario.timer);
            strcat(logs, phrasePlusTimeFrigo);
            allVerifPass++;
            printf("verif time good");
        case 1 :
            strcat(logs, "La personne n'est pas resté trop longtemps dans le frigo\n");

    }
    //verif température
    switch(verifTemps(frigoScenario.capteurTemp))
    {
        case 0 :
            sprintf(phrasePlusTempFrigo, "La température du frigo est trop haute : %d degre\n", frigoScenario.capteurTemp);
            strcat(logs, phrasePlusTempFrigo);
            allVerifPass++;
            printf("verif temps good");
        case 1 :
            strcat(logs, "La température du frigo est bonne\n");

    }

    
    if (allVerifPass == 0){
        //printf("Le scénario est bon\n");
        strcat(logs, "Le scénario est bon, tout s'est bien déroulé.\n");
        writeInFunction(logs);
        return 0;
    }
    writeInFunction(logs);
    return 1;
}

//fonction de lecture de scénario
void lectureScenario(int i ){
    
   

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
    verifScenario(i);
}



int main() {
    viderFichierLog();
    //boucle qui va parcourir les i scénarios
    for (int i = 1; i < 6; i++){
        //fonction de parcours de scénarios
        lectureScenario(i);
    }
    
    return 0;
}
