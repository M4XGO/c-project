#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

struct Couloir {
    int badgeSas1;
    int badgeSas2;
};


struct Frigo {
    char badgeFrigo[256];
    char capteurTemp[256];
    char timer[256];
};
char line2[256];

int putInStructFrigo(char *line) {

    struct Frigo frigoScenario1;


    printf("Ligne : %s", line);
    return 0;
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


    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, searchValue) != NULL) {
            found = 1;
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



int main() {

    struct Frigo frigoScenario1;

    int badgeFrigo1 = lireFichier("./textFile/sas.txt", "badgeFrigo1");
    printf("%s", line2);
    strcpy(frigoScenario1.badgeFrigo, line2);
    printf("struct %s\n",frigoScenario1.badgeFrigo);
    printf("\n");

    int capteurTemp1 = lireFichier("./textFile/sas.txt", "capteurTemp1");
    printf("%s", line2);
    strcpy(frigoScenario1.capteurTemp, line2);
    printf("struct %s\n",frigoScenario1.capteurTemp);
    printf("\n");

    int timer1 = lireFichier("./textFile/sas.txt", "timer1");
    strcpy(frigoScenario1.timer, line2);
    printf("%s", line2);
    printf("struct %s\n",frigoScenario1.timer);
    printf("\n");

   
    
    return 0;
}
