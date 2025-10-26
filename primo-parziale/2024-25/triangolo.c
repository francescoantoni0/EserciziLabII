#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Esercizio 2
Scrivere un programma triangolo che invocato scrivendo:

triangolo nomefile
legge da nomefile le stringhe contenute in esso e le salva in un array. Successivamente crea un file nomefile.triangolo
contenente nella riga i-esima le parole dalla i-esima alla prima in ordine inverso. Ad esempio, se il file di input si
chiama moria e contiene le parole dite amici ed entrate il file di output deve chiamarsi moria.triangolo e contentere le 4 righe:

dite
amici dite
ed amici dite
entrate ed amici dite
L'esercizio verrà considerato corretto solamente se la memoria verrà gestita in maniera dinamica e correttamente
deallocata (verrà utilizzato valgrind per la verifica).
*/

int main(const int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nomefile>\n", argv[0]);
        return 1;
    }

    char **parole = NULL;

    FILE *f = fopen(argv[1], "r");
    assert(f != NULL);

    int n;
    
    for (n = 0; !feof(f); n++) {
        char **tmp = realloc(parole, sizeof(char *) * (n + 1));
        if (tmp == NULL) {
            perror("La realloc è fallita!\n");
            free(parole);
            fclose(f);
            return 1;
        }
        parole = tmp;
        fscanf(f, "%ms", &parole[n]);
    }

    fclose(f);

    assert(parole != NULL);

    const size_t s = strlen(argv[1]) + strlen(".triangolo") + 1;
    char *filename = malloc(sizeof(char) * s);
    assert(filename != NULL);
    sprintf(filename, "%s.triangolo", argv[1]);
    f = fopen(filename, "w");

    for (int i = 0; i < n; i++) {
        for (int j = i; j >= 0; j--) {
            fprintf(f, "%s ", parole[j]);
        }
        fprintf(f, "\n");
    }

    for (int i = 0; i < n; ++i) {
        free(parole[i]);
    }
    free(parole);
    free(filename);
    fclose(f);
}