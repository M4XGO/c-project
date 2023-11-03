#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

struct Couloir {
    char badgeEntre[256];
    char badgeSortie[256];
};


struct Frigo {
    char badgeFrigo[256];
    char capteurTemp[256];
    char timer[256];
};

char line2[256];

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

void lectureScenario(int i ){
    //crétion des structures qui vont être utiliées
    struct Frigo frigoScenario;
    struct Couloir couloirScenario;

    //création de varibale pour pouvoir concaténer les noms des variables avec i 
    char badgeEntre[50];
    char badgeSortie[50];
    char badgeFrigo[50];
    char capteurTemp[50];
    char timer[50];

    //concaténation
    sprintf(badgeEntre, "badgeEntre%d", i);
    sprintf(badgeSortie, "badgeSortie%d", i);
    sprintf(badgeFrigo, "badgeFrigo%d", i);
    sprintf(capteurTemp, "capteurTemp%d", i);
    sprintf(timer, "timer%d", i);

    //recherche des variables dans le fichier via les variable concaténés
    // + ajout dans la strucutre en passant par la variable globale line2
    int badgeSas1 = lireFichier("./textFile/sas.txt", badgeEntre);
    strcpy(couloirScenario.badgeEntre, line2);
    int badgeSas2 = lireFichier("./textFile/sas.txt", badgeSortie);
    strcpy(couloirScenario.badgeSortie, line2);
    int badgeFrigo1 = lireFichier("./textFile/sas.txt", badgeFrigo);
    strcpy(frigoScenario.badgeFrigo, line2);
    int capteurTemp1 = lireFichier("./textFile/sas.txt", capteurTemp);
    strcpy(frigoScenario.capteurTemp, line2);
    int timer1 = lireFichier("./textFile/sas.txt", timer);
    strcpy(frigoScenario.timer, line2);
   
   //affichage des structures
    printf("\n");
    printf("struct %s\n%s\n%s\n%s\n%s\n",couloirScenario.badgeEntre,couloirScenario.badgeSortie,frigoScenario.badgeFrigo,frigoScenario.capteurTemp,frigoScenario.timer);    
    
}

int main() {
    //boucle qui va parcourir les i scénarios
    for (int i = 1; i < 4; i++){
        //fonction de parcours de scénarios
        lectureScenario(i);
    }
    
    return 0;
}
