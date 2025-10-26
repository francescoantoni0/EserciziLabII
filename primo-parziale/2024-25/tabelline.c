#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Esercizio 1
Scrivere un programma tabelline che invocato scrivendo

tabelline n1 n2 n2 ....
per ogni intero N sulla linea di comando crea il file N.tab contenente la tabellina (i multipli da 1 a 10) del numero N. Ad esempio scrivendo

tabelline 4 20
deve essere creato il file 4.tab contenente la sequenza

4
8
12
16
20
24
28
32
36
40
ed il file 20.tab contenente la sequenza

20
40
60
80
100
120
140
160
180
200
I file di output devono chiamarsi esattamente come indicato, e contenere esattamente i valori richiesti con un valore su ogni riga.
Il programma deve accettare un qualsiasi numero di argomenti sulla linea di comando. Verificate con valgrind il corretto uso e deallocazione della memoria
 */

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s n...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]);
        const size_t len = strlen(argv[i]) + 5;
        char *filename = malloc(sizeof(char) * len);
        assert(filename != NULL);
        sprintf(filename, "%i.tab", num);
        FILE *output = fopen(filename, "w");
        assert(output != NULL);
        for (int j = 1; j <= 10; j++) {
            fprintf(output, "%i\n", j*num);
        }
        fclose(output);
        free(filename);
    }
}
