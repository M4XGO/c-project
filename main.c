#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

struct Couloir {
    char badgeEntre[256];
    char badgeSortie[256];
};


struct Frigo {
    char badgeFrigoEntre[256];
    char badgeFrigoSortie[256];
    char capteurTemp[256];
    char timer[256];
};

char line2[256];

int verifBadgeEntre(int badge){
    if (badge == 1){
        printf("La personne est rentré\n");
        return 1;
    }
    else{
        printf("La personne n'est pas rentré\n");
        return 0;
    }
}

int verifBadgeSortie(int badge){
    if (badge == 1){
        printf("ATTENTION : La personne n'est pas sorti\n");
        return 1;
    }
    else{
        printf("La personne est sorti\n");
        return 0;
    }
}

// Driver code
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



int writeInFunction()
{
    char *filename = "./textFile/sas.txt";

    // open the file for writing
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening the file %s", filename);
        return -1;
    }
    // write to the text file
    for (int i = 0; i < 10; i++)
        fprintf(fp, "This is the line #%d\n", i + 1);

    // close the file
    fclose(fp);

    return 0;
}

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
    sscanf(chaine + (strlen(chaine) - 5), "%d", &resultat);
    return resultat;
}


void lectureScenario(int i ){
    //crétion des structures qui vont être utiliées
    struct Frigo frigoScenario;
    struct Couloir couloirScenario;

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
    int badgeSas1 = lireFichier("./textFile/sas.txt", badgeEntre);
    strcpy(couloirScenario.badgeEntre, line2);
    int badgeSas2 = lireFichier("./textFile/sas.txt", badgeSortie);
    strcpy(couloirScenario.badgeSortie, line2);
    int badgeFrigo1 = lireFichier("./textFile/sas.txt", badgeFrigoEntre);
    strcpy(frigoScenario.badgeFrigoEntre, line2);
    int badgeFrigo2 = lireFichier("./textFile/sas.txt", badgeFrigoSortie);
    strcpy(frigoScenario.badgeFrigoSortie, line2);
    int capteurTemp1 = lireFichier("./textFile/sas.txt", capteurTemp);
    strcpy(frigoScenario.capteurTemp, line2);
    int timer1 = lireFichier("./textFile/sas.txt", timer);
    strcpy(frigoScenario.timer, line2);
   
   //affichage des structures
    printf("\n");
    printf("badge entre %d\n badge sortie %d\n badge frigo entre %d\n badge frigo sortie %d\n temp %d\n timer %d\n",retourneDenierNombre(couloirScenario.badgeEntre),retourneDenierNombre(couloirScenario.badgeSortie),retourneDenierNombre(frigoScenario.badgeFrigoEntre),retourneDenierNombre(frigoScenario.badgeFrigoSortie),retourneTemp(frigoScenario.capteurTemp),retourneTime(frigoScenario.timer));    
    
}

int main() {
    //boucle qui va parcourir les i scénarios
    for (int i = 1; i < 6; i++){
        //fonction de parcours de scénarios
        lectureScenario(i);
    }
    
    return 0;
}
