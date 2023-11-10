#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 

struct Couloir {
    // char badgeEntre[256];
    // char badgeSortie[256];
    int badgeEntre;
    int badgeSortie;
};


struct Frigo {
    // char badgeFrigoEntre[256];
    // char badgeFrigoSortie[256];
    // char capteurTemp[256];
    // char timer[256];
    int badgeFrigoEntre;
    int badgeFrigoSortie;
    int capteurTemp;
    int timer;
};

char line2[256];
struct Frigo frigoScenario;
struct Couloir couloirScenario;
char chemin[50] = "./textFile/scenario.txt";
char chemin2[50] = "./textFile/logs.txt";

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

void viderFichierLog(){
    FILE *fp = fopen(chemin2, "w");
    fclose(fp);
}

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
int retourneTemp (char chaine[256]){
    int resultat;
    sscanf(chaine + (strlen(chaine) - 4), "%d", &resultat);
    return resultat;
}

int retourneTime (char chaine[256]){
    int resultat;
    // printf("chaine : %s\n", chaine);
    sscanf(chaine + (strlen(chaine) - 2), "%d", &resultat);
    // printf("resultat : %d\n", resultat);
    return resultat;
}

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
    //vérification des badges entré
    if (verifBadgeEntre(couloirScenario.badgeEntre) == 0){
        strcat(logs, "La personne n'est pas rentré dans le sas\n");
        allVerifPass++;
    }
    if (verifBadgeEntre(frigoScenario.badgeFrigoEntre) == 0){
        strcat(logs, "La personne n'est pas rentré dans un frigo\n");
        allVerifPass++;
    }
    
    if (verifBadgeSortie(frigoScenario.badgeFrigoSortie) == 0){
        strcat(logs, "La personne n'est pas sorti du frigo\n");
        allVerifPass++;
    }
    if (verifTime(frigoScenario.timer) == 0){
        sprintf(phrasePlusTimeFrigo, "La personne est resté trop longtemps dans le frigo : %dsec\n", frigoScenario.timer);
        // printf("%s", phrasePlusTimeFrigo);
        strcat(logs, phrasePlusTimeFrigo);
        allVerifPass++;
    }
    if (verifTemps(frigoScenario.capteurTemp) == 0){
        sprintf(phrasePlusTempFrigo, "La température du frigo est trop haute : %d degre\n", frigoScenario.capteurTemp);
        strcat(logs, phrasePlusTempFrigo);
        allVerifPass++;
    }
    if (verifBadgeSortie(couloirScenario.badgeSortie) == 0){
        strcat(logs, "La personne n'est pas sorti du sas\n");
        allVerifPass++;
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


void lectureScenario(int i ){
    //crétion des structures qui vont être utiliées
   

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

   //affichage des structures
    // printf("\n");
    // printf("badge entre %d\n badge sortie %d\n badge frigo entre %d\n badge frigo sortie %d\n temp %d\n timer %d\n", couloirScenario.badgeEntre, couloirScenario.badgeSortie, frigoScenario.badgeFrigoEntre, frigoScenario.badgeFrigoSortie, frigoScenario.capteurTemp, frigoScenario.timer);
    verifScenario(i);
}

int main() {
    viderFichierLog();
    //boucle qui va parcourir les i scénarios
    for (int i = 1; i < 6; i++){
        // printf("\n######## Scenario %d ########", i);
        //fonction de parcours de scénarios
        lectureScenario(i);
    }
    
    return 0;
}
