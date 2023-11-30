#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define TAILLE_MAX 1000

// Fonction de lecture de fichier
char* lireFichier() {
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX] = "";

    fichier = fopen("test.txt", "r");

    if (fichier != NULL) {
        fgets(chaine, TAILLE_MAX, fichier);
        printf("%s", chaine);
        fclose(fichier);

        // Allouer de la mémoire pour la chaîne lue
        char *response = strdup(chaine);

        // Vérifier si l'allocation de mémoire a réussi
        if (response == NULL) {
            perror("Erreur d'allocation mémoire");
            exit(EXIT_FAILURE);
        }

        return response;
    }

    return NULL; // Retourner NULL en cas d'erreur d'ouverture du fichier
}

void sendToClient(int client_socket) {
    char *buffer2 = lireFichier();

    if (buffer2 != NULL) {
        send(client_socket, buffer2, strlen(buffer2), 0);
        free(buffer2); // Libérer la mémoire allouée dynamiquement
    } else {
        const char *error_response = "Erreur lors de la lecture du fichier.\n";
        send(client_socket, error_response, strlen(error_response), 0);
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);

    // Création du socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configuration de l'adresse du serveur
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Liaison du socket
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Écoute de connexions
    listen(server_socket, 5);

    // Acceptation d'une connexion
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);

    // Traitement des commandes Telnet
    sendToClient(client_socket);

    // Fermeture des sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
