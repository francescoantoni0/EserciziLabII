#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int primo;
    int secondo;
} coppia;

void termina(char *messaggio) {
    perror(messaggio);
    exit(1);
}

// funzione per il merge di due array in un terzo array già allocato
// merge di a[0...n1-1] e c[0... n2-1] dentro b[]
// Soluzione proposta da co-pilot apparentemente corretta
void merge(int a[], int na, int c[], int nc, int b[]) {
    assert(a!=NULL);
    assert(c!=NULL);
    assert(b!=NULL);
    assert(na>0);
    assert(nc>0);

    int i = 0; // indice per a[]
    int j = 0; // indice per c[]
    int k = 0; // indice per b[]

    // scorro a[] e c[] e copio il minore in b[]
    while (i < na && j < nc) {
        if (a[i] < c[j]) {
            b[k] = a[i];
            i++;
        } else {
            b[k] = c[j];
            j++;
        }
        k++;
    }

    // copio il resto di a[] in b[]
    while (i < na) {
        b[k] = a[i];
        i++;
        k++;
    }

    // copio il resto di c[] in b[]
    while (j < nc) {
        b[k] = c[j];
        j++;
        k++;
    }
    // asserzioni aggiunte da GM perché non si sa mai
    assert(i==na);
    assert(j==nc);
    assert(k==na+nc);
}

// funzione per il merge di due array di stringhe in un terzo array già allocato
// merge di a[0...n1-1] e c[0... n2-1] dentro b[]
// ordina per lunghezza delle stringhe
void merge_stringhe(char *a[], int na, char *c[], int nc, char *b[]) {
    assert(a!=NULL);
    assert(c!=NULL);
    assert(b!=NULL);
    assert(na>0);
    assert(nc>0);

    int i = 0; // indice per a[]
    int j = 0; // indice per c[]
    int k = 0; // indice per b[]

    // scorro a[] e c[] e copio in b[] la stringa più corta
    while (i < na && j < nc) {
        if (strlen(a[i]) <= strlen(c[j])) {
            b[k] = a[i];
            i++;
        } else {
            b[k] = c[j];
            j++;
        }
        k++;
    }

    // copio il resto di a[] in b[]
    while (i < na) {
        b[k] = a[i];
        i++;
        k++;
    }

    // copio il resto di c[] in b[]
    while (j < nc) {
        b[k] = c[j];
        j++;
        k++;
    }
    // asserzioni aggiunte da GM perché non si sa mai
    assert(i==na);
    assert(j==nc);
    assert(k==na+nc);
}

// funzione mergesort ricorsiva per stringhe (ordina per lunghezza)
void mergesort_stringhe(char *a[], int n) {
    assert(a!=NULL);
    assert(n>0);

    // caso base
    if (n == 1) return;

    int n1 = n / 2; // dimensione prima parte
    int n2 = n - n1; // dimensione seconda parte
    assert(n1+n2==n); // verifico che sto considerando tutti gli elementi

    // ordino a[0...n1-1]
    mergesort_stringhe(a, n1);
    // ordino a[n1...n-1]
    mergesort_stringhe(&a[n1], n2);

    // ora ho le due metà ordinate devo fare il merge
    char **b = malloc(n * sizeof(*b));
    if (b == NULL) termina("malloc fallita nel merge");
    merge_stringhe(a, n1, &a[n1], n2, b);
    // copio il risultato da b[] ad a[]
    for (int i = 0; i < n; i++)
        a[i] = b[i];

    free(b); // dealloco array temporaneo b[]
}

void mergesort(int a[], int n) // al posto di a[] posso scrivere *a
{
    assert(a!=NULL);
    assert(n>0);

    // caso base
    if (n == 1) return;

    int n1 = n / 2; // dimensione prima parte
    int n2 = n - n1; // dimensione seconda parte
    assert(n1+n2==n); // verifico che sto considerando tutti gli elementi

    // ordino a[0...n1-1]
    mergesort(a, n1);
    // ordino a[n1...n-1]
    mergesort(&a[n1], n2); // &a[n1] potevo scriverlo a+n1

    // ora ho le due metà ordinate devo fare il merge
    int *b = malloc(n * sizeof(*b));
    if (b == NULL) termina("malloc fallita nel merge");
    merge(a, n1, &a[n1], n2, b);
    // copio il risultato da b[] ad a[]
    for (int i = 0; i < n; i++)
        a[i] = b[i];

    free(b); // dealloco array temporaneao b[]
}

// funzione per il merge di due array di coppie in un terzo array già allocato
// merge di a[0...n1-1] e c[0... n2-1] dentro b[]
// ordina per la prima componente della coppia, a parità per la seconda
void merge_coppie(coppia *a[], int na, coppia *c[], int nc, coppia *b[]) {
    assert(a!=NULL);
    assert(c!=NULL);
    assert(b!=NULL);
    assert(na>0);
    assert(nc>0);

    int i = 0; // indice per a[]
    int j = 0; // indice per c[]
    int k = 0; // indice per b[]

    // scorro a[] e c[] e copio in b[] la coppia con primo minore
    // a parità di primo, ordino per secondo
    while (i < na && j < nc) {
        if (a[i]->primo < c[j]->primo || 
            (a[i]->primo == c[j]->primo && a[i]->secondo < c[j]->secondo)) {
            b[k] = a[i];
            i++;
        } else {
            b[k] = c[j];
            j++;
        }
        k++;
    }

    // copio il resto di a[] in b[]
    while (i < na) {
        b[k] = a[i];
        i++;
        k++;
    }

    // copio il resto di c[] in b[]
    while (j < nc) {
        b[k] = c[j];
        j++;
        k++;
    }
    // asserzioni aggiunte da GM perché non si sa mai
    assert(i==na);
    assert(j==nc);
    assert(k==na+nc);
}

// funzione mergesort ricorsiva per coppie (ordina per prima componente)
void mergesort_coppie(coppia *a[], int n) {
    assert(a!=NULL);
    assert(n>0);

    // caso base
    if (n == 1) return;

    int n1 = n / 2; // dimensione prima parte
    int n2 = n - n1; // dimensione seconda parte
    assert(n1+n2==n); // verifico che sto considerando tutti gli elementi

    // ordino a[0...n1-1]
    mergesort_coppie(a, n1);
    // ordino a[n1...n-1]
    mergesort_coppie(&a[n1], n2);

    // ora ho le due metà ordinate devo fare il merge
    coppia **b = malloc(n * sizeof(*b));
    if (b == NULL) termina("malloc fallita nel merge");
    merge_coppie(a, n1, &a[n1], n2, b);
    // copio il risultato da b[] ad a[]
    for (int i = 0; i < n; i++)
        a[i] = b[i];

    free(b); // dealloco array temporaneo b[]
}

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <nomefile>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    assert(f != NULL);

    //prendo le parole da file

    char **parole = NULL, *line = NULL;

    int n;

    for (n = 0; fscanf(f, "%ms", &line) > 0; n++) {
        char **tmp = realloc(parole, sizeof(char *) * (n + 1));
        if (tmp == NULL) {
            perror("La realloc è fallita!");
            free(parole);
            fclose(f);
            return 1;
        }
        parole = tmp;
        parole[n] = line;
        line = NULL;
    }

    fclose(f);
    assert(parole != NULL);

    // Ordino array delle parole

    mergesort_stringhe(parole, n);

    // Stampo il primo file con le parole ordinate

    char *filename = malloc((strlen(argv[1]) + strlen(".ordinato") + 1) * sizeof(char));
    sprintf(filename, "%s.ordinato", argv[1]);
    if (filename == NULL) {
        perror("Errore allocazione nome file");
        free(parole);
        return 1;
    }

    FILE *f_out = fopen(filename, "w");
    if (f_out == NULL) {
        perror("Errore apertura file");
        free(filename);
        free(parole);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f_out, "%s\n", parole[i]);
    }

    fclose(f_out);
    free(filename);

    // Creo l'array delle coppie a partire dalle stringhe ordinate e lo stampo nel file .prima

    coppia **coppie = malloc(sizeof(coppia *) * n);
    if (coppie == NULL) {
        perror("L'allocazione delle coppie è fallita!");
        free(parole);
        return 1;
    }

    filename = malloc((strlen(argv[1]) + strlen(".prima") + 1) * sizeof(char));
    if (filename == NULL) {
        perror("Errore allocazione nome file");
        free(parole);
        free(coppie);
        return 1;
    }
    sprintf(filename, "%s.prima", argv[1]);
    f_out = fopen(filename, "w");
    if (f_out == NULL) {
        perror("Errore apertura file");
        free(filename);
        free(parole);
        free(coppie);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        coppie[i] = malloc(sizeof(coppia));
        if (coppie[i] == NULL) {
            fprintf(stderr, "Errore allocazione coppia %d\n", i);
            free(parole);
            free(coppie);
            return 1;
        }
        coppie[i]->primo = 0;
        coppie[i]->secondo = (int) strlen(parole[i]);
        for (int j = 0; j < coppie[i]->secondo; j++) {
            if (parole[i][j] == '#') {
                coppie[i]->primo++;
            }
        }
        fprintf(f_out, "%i %i\n", coppie[i]->primo, coppie[i]->secondo);
    }

    free(filename);
    fclose(f_out);

    // Ordino le coppie e stampo il file .dopo

    mergesort_coppie(coppie, n);

    filename = malloc((strlen(argv[1]) + strlen(".dopo") + 1) * sizeof(char));
    if (filename == NULL) {
        perror("Errore allocazione nome file");
        free(parole);
        free(coppie);
        return 1;
    }
    sprintf(filename, "%s.dopo", argv[1]);

    f_out = fopen(filename, "w");
    free(filename);

    if (f_out == NULL) {
        perror("Errore apertura file");
        free(filename);
        free(parole);
        free(coppie);
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        fprintf(f_out, "%i %i\n", coppie[i]->primo, coppie[i]->secondo);
    }

    for (int i = 0; i < n; ++i) {
        free(coppie[i]);
        free(parole[i]);
    }

    fclose(f_out);
    free(coppie);
    free(parole);
}
