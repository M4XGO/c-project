// Code du serveur en C avec gestion des commandes via Telnet
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024


void handle_telnet_commands(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;

    // Boucle pour recevoir les commandes telnet
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        // Ajoutez votre logique de traitement ici
        // Pour cet exemple, nous affichons simplement la commande
        buffer[bytes_received] = '\0';

        printf("Commande reçue : %s\n", buffer);

        // Vous pouvez ajouter la logique d'exécution des commandes ici
        // Exemple: system(buffer);

        // Réponse au client, si nécessaire
        const char *response = "Commande reçue avec succès.\n";
        send(client_socket, response, strlen(response), 0);
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
    handle_telnet_commands(client_socket);

    // Fermeture des sockets
    close(client_socket);
    close(server_socket);

    return 0;
}