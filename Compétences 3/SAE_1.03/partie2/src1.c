/**
* 
* Ce programme permet de jouer une partie de sudoku directement
* dans le terminal à partir de grilles prédéfinies.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 3 /** La grille de sudoku est divisée en N² blocs de N² cases */
#define TAILLE N*N /** La grille de sudoku est divisée en N² blocs de N² cases */

typedef int tGrille[TAILLE][TAILLE];

int difficulté; /** Entier représentant les 3 difficultés. 1 : Facile, 2 : Intermédiaire, 2 : Difficile */

typedef struct {
    char pseudo[10]; /** Pseudo d'un·e joueur·euse */
        char date [8] ; /** Date du résultat */
    int score ; /** Score réalisé lors de cette partie */
    int classement; /** Son classement */
}   str_resultat; /** Structure d'un résultat */

bool terminal; /** Booléen permettant de décider si l'affichage se fait dans le terminal ou dans l'interface graphique */

void afficherGrille(tGrille g, bool);
typedef struct
{
    char pseudo[10]; /** Pseudo d'un·e joueur·euse */
        int age; /** Son age */
        int classement; /** Son meilleur classement classement */
        int record; /** Son record de points */
} str_utilisateur; /** Structure d'un·e jour */
void chargerGrille(tGrille);

/**
* \brief Programme principal.
*
* \detail Le programme principal initialise tout d'abord une grille de type tGrille,
* elle sera ensuite remplie grâce à la fonction chargerGrille() puis le programme
* affichera cette grille et début la partie
* \return int Code de sortie du programme (0 : sortie normale)
*
*/
int main()
{
    tGrille grille1;
    bool recur;
    recur = false;
    chargerGrille(grille1);
    afficherGrille(grille1,recur);
    return EXIT_SUCCESS; /* Fin du jeu */
}

/**
*
* \brief Affiche la grille
*
* \detail Cette fonction affiche la grille de sudoku qui lui est passée en paramètre.
* Elle affiche d'abord les numérotations autour de la grille.
* Deux boucles for imbriquées permettent de se balader le long du tableau
* et d'afficher les valeurs et les bordures grâce à des modulos N
*
* \param tGrille  grille Grille à afficher
* \param bool recur Booléen décidant si l'affichage se fera par récursivité ou non
*/
void afficherGrille(tGrille grille, bool recur)
{
    printf("     1  2  3   4  5  6   7  8  9\n");
    for (int i = 0; i < TAILLE; i++)
    {
        if (i%3 == 0)
        {
            printf("   +---------+---------+---------+\n");
        }

        for (int j = 0; j < TAILLE; j++)
        {
            if(j == 0)
            {
                printf("%d  ",i+1);
            }

            if (j%3 == 0)
            {
                printf("|");
            }

            if (grille[i][j] == 0)
            {
                printf(" . ");
            }
            else
            {
                printf(" %d ",grille[i][j]);
            }
        }
        printf("|");
        printf("\n");
    }
    printf("   +---------+---------+---------+\n");
}/**
*
* \brief Procédure permettant de charger une grille depuis un fichier.
*
* \detail Elle permet de charger en mémoire une grille de sudoku existante à
* partir d’un fichier dont le nom est lu au clavier
*
* \param tGrille g Grille à charger
*
*/


void   chargerGrille ( tGrille  g )  {
    char nomFichier[30];
    FILE * f;

    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);

    f = fopen(nomFichier, "rb");

    if (f==NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    }
    else
    {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
    }
    fclose(f);
}
