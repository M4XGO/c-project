# Utiliser une image Ubuntu comme base
FROM ubuntu:latest

# Installer les outils de compilation C
RUN apt-get update && apt-get install -y gcc

# Définir le répertoire de travail
WORKDIR /app

# Copier les fichiers source de votre application C dans le conteneur
COPY main.c /app
COPY textFile/scenario.txt /app/textFile/scenario.txt
COPY textFile/logs.txt /app/textFile/logs.txt

# Compiler votre application C
RUN gcc -o application_c main.c

# Exposer un point d'entrée pour lancer votre application
CMD ["./application_c", "cat /textFile/logs.txt"]
