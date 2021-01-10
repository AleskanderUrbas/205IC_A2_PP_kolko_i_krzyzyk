#include <stdio.h>
#include <stdlib.h>

int gra[3][3];
/* elementy macierzy:
 * 0 - pole puste
 * 1 - kolko
 * 2 - krzyzyk
 * znaczenie szczegolnych operacji:
 * iloczyn elementów kolumny, wiersza lub przekątnej:
 *      = 1 -> wygrywa kolko
 *      = 8 -> wygrywa krzyzyk */

short numer_ruchu;
/* numer_ruchu nieparzysty -> ruch O
 * numer_ruchu parzysty -> ruch X
 * numer_ruchu > 9 -> koniec gry */

char nr_pol;
/*gdy "t" na planszy wyswietlane sa nr pol*/

int inicjalizacja(int tablica[3][3]);
int wyswietlanie(int tablica[3][3], char nr_pol);
char konwersja(int tablica[3][3], int i, int j, char nr_pol);
int ruch(int tablica[3][3], int nr_ruchu);
int zwyciestwo(int tablica[3][3], int i, int j);


int main() {
    inicjalizacja(gra);
    printf("Czy wyswietlac na planszy nr pol (t)?");
    scanf("%c", &nr_pol);
    wyswietlanie(gra, nr_pol);
    for (numer_ruchu = 1; numer_ruchu < 10; numer_ruchu++)
    {
        ruch(gra, numer_ruchu);
        wyswietlanie(gra, nr_pol);
    }
    printf("Koniec gry - remis.");

    return 0;
}


int inicjalizacja(int tablica[3][3])
{
    int i, j;

    for (i=0; i<3; i++){
        for (j=0; j<3; j++){
            tablica[i][j] = 0;
        }
    }
    return 0;
}

int wyswietlanie(int tablica[3][3], char nr_pol)
{
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf(" %c", konwersja(tablica, i, j, nr_pol));
            if (j!=2)
                printf(" |");
            if ((j==2) && (i==0 || i==1)){
                printf("\n - - - - -\n");
            }
        }
    }
    printf("\n\n");
    return 0;
}

char konwersja(int tablica[3][3], int i, int j, char nr_pol)
{
    char znak;

    switch(tablica[i][j]) {
        case 0:
            if (nr_pol == 't')
                znak = 48 + 3 * i + j + 1;
            else
                znak = ' ';
            break;
        case 1:
            znak = 'O';
            break;
        case 2:
            znak = 'X';
            break;
        default:
            znak = ' ';
    }
   return znak;
}

int ruch(int tablica[3][3], int nr_ruchu)
{
    int pole, pole_zajete, wiersz, kolumna;
    /*pole_zajete=1 gdy w polu wybranym przez gracza jest X lub O
     * wiersz, kolumna okreslone na podstawie numeru pole*/

    pole_zajete = 1;

    while (pole_zajete == 1)
    {
        if (nr_ruchu % 2 == 1)
            printf("   O ->");
        else
            printf("   X ->");
        scanf("%i", &pole);
        wiersz = (pole-1)/3;
        kolumna = (pole-1) % 3;
        if (tablica[wiersz][kolumna] == 0)
            pole_zajete = 0;
    }
    if (nr_ruchu % 2 == 1)
        tablica[wiersz][kolumna] = 1;
    else
        tablica[wiersz][kolumna] = 2;
    if (zwyciestwo(tablica, wiersz, kolumna) == 1)
    {
        wyswietlanie(gra, nr_pol);
        printf("Koniec gry - zwyciestwo gracza -> ");
        if (nr_ruchu % 2 == 1)
            printf("O\n");
        else
            printf("X\n");
        exit(0);
    }
return 0;
}

int zwyciestwo(int tablica[3][3], int i, int j)
{
    int iloczyn;

    /*sprawdzenie kolumny*/
    iloczyn = tablica[0][j] * tablica[1][j] * tablica[2][j];
    if (iloczyn == 1 || iloczyn == 8)
        return 1;
    /*sprawdzenie wiersza*/
    iloczyn = tablica[i][0] * tablica[i][1] * tablica[i][2];
    if (iloczyn == 1 || iloczyn == 8)
        return 1;
    /*sprawdzanie przekatnych, obliczenia nadmiarowe,
     *do optymalizacji przez ograniczenie do przypadkow,
     *gdy wybrane pole jest na przekatnej*/
    iloczyn = tablica[0][0] * tablica[1][1] * tablica[2][2];
    if (iloczyn == 1 || iloczyn == 8)
        return 1;
    iloczyn = tablica[2][0] * tablica[1][1] * tablica[0][2];
    if (iloczyn == 1 || iloczyn == 8)
        return 1;
    return 0;
}