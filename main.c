#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

struct Couloir {
    int badgeSas1;
    int badgeSas2;
};


struct Frigo {
    int badgeFrigo;
    int capteurTemp;
    int timer;
};


int putInStruct(char *line) {
    printf("Ligne : %s", line);
    return 0;
}

// Driver code
int readFile(const char *filename, const char *searchValue) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Le fichier ne peut pas être ouvert\n");
        return 1;
    }

    char line[256];  // Une ligne peut contenir jusqu'à 255 caractères, ajustez selon vos besoins
    int lineNumber = 1;
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, searchValue) != NULL) {
            found = 1;
            putInStruct(line);
            
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

    int sasCouloir1 = readFile("./textFile/sas.txt", "sas1");

    int sasCouloir2 = readFile("./textFile/sas.txt", "sas2");


    
    return 0;
}
