#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define N 4
#define TAILLE (N * N)

typedef int tGrille[TAILLE][TAILLE];

bool absentSurLigne(int valeur, tGrille grille, int ligne);
bool absentSurColonne(int valeur, tGrille grille, int colonne);
bool absentSurBloc(int valeur, tGrille grille, int ligne, int colonne);
bool backtracking(tGrille grille, int numeroCase);

int chargerGrille(tGrille g);
void afficherGrille(tGrille g);

clock_t debut;
clock_t fin;

int main()
{
    tGrille g;
    int numercase = 0;

    chargerGrille(g);
    printf("Grille initiale  \n");
    afficherGrille(g);

    clock_t debut = clock();

    backtracking(g, numercase);
    clock_t fin = clock();

    printf("Grille finale  \n");
    afficherGrille(g);

    double Resolution = (fin - debut) * 1.0 / CLOCKS_PER_SEC;
    printf("Resolution de la grille en  %.6f sec\n", Resolution);
}

int chargerGrille(tGrille g)
{
    char nomFichier[30];
    FILE *f;
    int compteur = 0;
    int valeurLue;

    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);

    f = fopen(nomFichier, "rb");
    if (f == NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    }
    else
    {
        for (int i = 0; i < TAILLE; i++)
        {
            for (int j = 0; j < TAILLE; j++)
            {
                fread(&valeurLue, sizeof(int), 1, f);
                g[i][j] = valeurLue;
                if (valeurLue == 0)
                {
                    compteur = compteur + 1;
                }
            }
        }
    }
    return compteur;
}

void afficherGrille(tGrille g)
{
    int i, j;

    for (i = 0; i < TAILLE; i++)
    {
        if (i % N == 0)
        {
            printf("\t +------------+------------+------------+------------+\n");
        }

        printf("\t |");

        for (j = 0; j < TAILLE; j++)
        {
            if (g[i][j] == 0)
            {
                printf(" . ");
            }
            else
            {
                if (g[i][j] < 10)
                {
                    printf(" %d ", g[i][j]);
                }

                else
                {
                    printf("%d ", g[i][j]);
                }
            }

            if ((j + 1) % N == 0)
            {
                printf("|");
            }
        }

        printf("\n");
    }

    printf("\t +------------+------------+------------+------------+\n");
}

bool backtracking(tGrille grille, int numeroCase)
{

    int ligne, colonne;
    bool resultat = false;

    if (numeroCase == TAILLE * TAILLE)
    {
        // on a traité toutes les cases, la grille est résolue
        resultat = true;
    }

    else
    {
        // On récupère les "coordonnées" de la case
        ligne = numeroCase / TAILLE;
        colonne = numeroCase % TAILLE;

        if (grille[ligne][colonne] != 0)
        {
            // Si la case n’est pas vide, on passe à la suivante
            // (appel récursif)
            resultat = backtracking(grille, numeroCase + 1);
        }
        else
        {
            for (int valeur = 1; valeur < TAILLE + 1; valeur++)
            {
                if (absentSurLigne(valeur, grille, ligne) && absentSurColonne(valeur, grille, colonne) && absentSurBloc(valeur, grille, ligne, colonne))
                {
                    // Si la valeur est autorisée on l'inscrit
                    // dans la case...

                    grille[ligne][colonne] = valeur;

                    // ... et on passe à la suivante : appel récursif
                    // pour voir si ce choix est bon par la suite

                    if (backtracking(grille, numeroCase + 1))
                    {

                        resultat = true;
                    }
                    else
                    {

                        grille[ligne][colonne] = 0;
                    }
                }
            }
        }
    }
    return resultat;
}

bool absentSurLigne(int valeur, tGrille grille, int ligne)
{
    for (int i = 0; i < TAILLE; i++)
    {
        if (grille[ligne][i] == valeur)
        {
            return false;
        }
    }
    return true;
}

bool absentSurColonne(int valeur, tGrille grille, int colonne)
{
    for (int i = 0; i < TAILLE; i++)
    {
        if (grille[i][colonne] == valeur)
        {
            return false;
        }
    }
    return true;
}

bool absentSurBloc(int valeur, tGrille grille, int ligne, int colonne)
{
    int blocLigne = (ligne) / N;
    int blocColonne = (colonne) / N;

    for (int i = blocLigne * N; i < (blocLigne + 1) * N; i++)
    {
        for (int j = blocColonne * N; j < (blocColonne + 1) * N; j++)
        {
            if (grille[i][j] == valeur)
            {
                return false;
            }
        }
    }
    return true;
}
