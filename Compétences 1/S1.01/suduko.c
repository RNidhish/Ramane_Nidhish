/**
*
* \brief Programme de résolution de Sudoku.
*
* \author Ramane Nidhish
*
* \version 1.0
*
* \date 02 décembre 2023
*
* Ce programme permet à l'utilisateur de jouer au Sudoku en saisissant des valeurs
* dans une grille et vérifie si la grille est résolue. La grille initiale est chargée
* à partir d'un fichier, et les valeurs sont insérées en respectant les règles du Sudoku.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
*
* \def NB_LIGNES
* \brief Nombre de lignes dans la grille Sudoku.
*
* Définit le nombre de lignes dans la grille Sudoku.
*
*/
#define NB_LIGNES 9
/**
*
* \def NB_COLONNES
* \brief Nombre de colonnes dans la grille Sudoku.
*
* Définit le nombre de colonnes dans la grille Sudoku.
*
*/
#define NB_COLONNES 9

/**
 * \typedef tGrille
 * \brief Type représentant la grille Sudoku.
 *
 * Cette structure de données représente la grille Sudoku avec un nombre
 * fixe de lignes (NB_LIGNES) et de colonnes (NB_COLONNES), où chaque élément
 * est de type entier (int).
 */
typedef int tGrille [NB_LIGNES] [NB_COLONNES];

/**
 * \var int N
 * 
 * \brief Taille de chaque sous-grille (par exemple, 3x3 dans un Sudoku classique).
 *
 * Cette constante représente la taille de chaque sous-grille dans la grille Sudoku.
 * Elle est utilisée pour déterminer la taille des blocs lors de la vérification des règles du Sudoku.
 */

const int N=3;

/**
 * \var int TAILLE
 * 
 * \brief Taille totale de la grille Sudoku.
 *
 * Cette constante représente la taille totale de la grille Sudoku, en termes de nombre total de cellules.
 */
const int TAILLE= 9;


/**
 * \fn  chargerGrille(tGrille g)
 * 
 * \brief Charge la grille Sudoku depuis un fichier.
 *
 * \param g : La grille Sudoku à charger.
 */
void chargerGrille(tGrille g);

/**
 * \fn  afficherGrille(tGrille g)
 * 
 * \brief Affiche la grille Sudoku.
 *
 * \param g : La grille Sudoku à afficher.
 */
void afficherGrille(tGrille g);

/**
 * \fn saisir(int *S)
 * 
 * \brief Saisit un entier avec validation.
 *
 * \param S : Pointeur vers l'entier à saisir.
 */
void saisir(int *S);

/**
 * \fn bool possible(tGrille g, int ligne, int colonne, int valeur)
 * 
 * \brief Vérifie si une valeur peut être insérée dans une cellule.
 *
 * \param g : La grille Sudoku.
 * \param ligne : Indice de ligne.
 * \param colonne : Indice de colonne.
 * \param valeur : Valeur à vérifier.
 * 
 * \return True si la valeur peut être insérée, false sinon.
 * 
 * Cette fonction vérifie la validité de l'insertion d'une valeur dans une cellule
 * spécifique du Sudoku. Elle examine la ligne, la colonne et le bloc (carré 3x3)
 * correspondants pour garantir l'absence de doublons avant d'autoriser l'insertion.
 */
bool possible(tGrille g, int ligne, int colonne, int valeur);

/**
 * \fn bool testgrille(tGrille g)
 * 
 * \brief Vérifie si la grille Sudoku est résolue.
 *
 * \param g : La grille Sudoku.
 * 
 * \return True si la grille est résolue, false sinon.
 * 
 * Cette fonction garantit que la grille est complète (sans zéros) et que
 * chaque ligne, colonne et sous-grille (carré 3x3) ne contient pas de doublons.
 */
bool testgrille(tGrille g);


/*****************************************************
            * PROGRAMME PRINCIPAL *
*****************************************************/

/**
 * \fn int main()
 * 
 * \brief Fonction principale pour le jeu Sudoku.
 *
 * \return EXIT_SUCCESS si le programme s'exécute avec succès.
 */
int main ()
{
    /**
     * \var tGrille grille
     * 
     * \brief Représente la grille Sudoku.
     * 
     * La variable grille stocke l'état actuel de la grille Sudoku.
     */
    tGrille grille;

    /**
     * \var int numLigne
     * 
     * \brief Indice de ligne pour l'interaction utilisateur.
     * 
     * La variable numLigne stocke l'indice de ligne pour les saisies de l'utilisateur.
     */
    /**
     * \var int numColonne
     * 
     * \brief Indice de colonne pour l'interaction utilisateur.
     * 
     * La variable numColonne stocke l'indice de colonne pour les saisies de l'utilisateur.
     */

    /**
     * \var int valeur
     * 
     * \brief Valeur à insérer dans la grille Sudoku.
     * 
     * La variable valeur stocke la valeur à insérer dans la grille Sudoku lors des interactions avec l'utilisateur.
     */

    int numLigne,numColonne,valeur;

    
    chargerGrille(grille); /** Charger la grille Sudoku initiale depuis un fichier */
    
    while (testgrille(grille)!=false)/** Continuer le jeu tant que la grille n'est pas résolue*/
    {
        
        afficherGrille (grille);/** Afficher l'état actuel de la grille*/
        printf("Indices de la case ? ");
        saisir( &numLigne);
        saisir( &numColonne);
        if (grille [numLigne-1][numColonne-1]!=0)    /** Afficher l'état actuel de la grille*/
        {

            printf("IMPOSSIBLE, la case n'est pas libre.\n");

        }
        else
        {
            printf("Valeur à insérer ?");
            saisir( &valeur);
            if (possible(grille,numLigne,numColonne,valeur)!=false)/** Vérifier s'il est possible d'insérer la valeur dans la cellule sélectionné*/
            {
                grille[numLigne-1][numColonne-1]=valeur;
            }
        
        }

    }
    afficherGrille (grille);
    printf("Grille pleine, fin de partie");
    return EXIT_SUCCESS;

}




void chargerGrille (tGrille g)

{
    /**
     * \var char nomFichier[30]
     * 
     * \brief Nom du fichier pour charger la grille Sudoku.
     * 
     * La variable nomFichier stocke le nom du fichier à partir duquel la grille Sudoku est chargée.
     */
    char nomFichier[30];

    /**
     * \var FILE *f
     * 
     * \brief Pointeur de fichier pour la manipulation de fichiers.
     * 
     * La variable f est un pointeur de fichier utilisé pour la lecture et l'écriture de fichiers
     * lors de l'opération de chargement de la grille Sudoku.
     */
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
        fread(g, sizeof(int), NB_LIGNES*NB_COLONNES, f);
        fclose(f);
    }


}


void afficherGrille(tGrille g)
{

    /**
     * \var int i
     * 
     * \brief Variable de boucle pour les lignes de la grille Sudoku.
     * 
     */

    /**
     * \var int j
     * 
     * \brief Variable de boucle pour les colonnes de la grille Sudoku.
     * 
     */
    int i, j, k;

    /**
     * \var int k
     * 
     * \brief Variable de comptage pour les cellules de la grille Sudoku.
     * 
     * La variable k est utilisée comme compteur pour identifier chaque cellule de la grille Sudoku lors de l'affichage.
     */
    k = 1;

    printf("\t    1 2 3   4 5 6   7 8 9\n");
    for (i = 0; i < NB_LIGNES; i++) 
    {    
        if (i % 3 == 0) 
        {
            
            printf("\t  +-------+-------+-------+\n");
        }

        printf("\t%d | ", k);
        k++;
        for (j = 0; j < NB_COLONNES; j++) {
            if (g[i][j] == 0)
                printf(". ");
            else
                printf("%d ", g[i][j]);

            if ((j + 1) % 3 == 0)
             
                printf("| ");
        }

        printf("\n");
    }
    printf("\t  +-------+-------+-------+\n");
}


void saisir(int *S) 
{
    /**
     * \var char ch[20]
     * 
     * \brief Tableau de caractères pour la saisie utilisateur.
     * 
     * La variable ch est un tableau de caractères utilisé pour stocker la saisie utilisateur.
     */

    char ch[20];

    /**
     * \var int x
     * 
     * \brief Entier résultant de la conversion de la saisie utilisateur.
     * 
     * La variable x est un entier résultant de la conversion de la saisie utilisateur à partir du tableau de caractères ch.
     */
    int x;
    scanf("%s", ch);
    if (sscanf(ch, "%d", &x) !=0)
     {
            if( x < TAILLE || x > 0)
            {

                *S = x;
            }
            else 
            {
                printf("La valeur que vous savez saisir n'est pas compris entre 1 à 9 \n");
                printf(" Nouveau valeur \n");
                saisir( &*S);  
            }

     } 
     else 
     {
        printf("La valeur que vous savez saisir est vide ou n'est pas Entier\n ");
        printf(" Nouveau valeur \n");
        saisir(&*S);      
     }

} 


bool possible(tGrille g, int ligne, int colonne, int valeur)// Fonction pour vérifier si une valeur peut être insérée dans une cellule
{
    /**
     * \var int i
     * 
     * \brief Variable de boucle pour les itérations dans la grille Sudoku.
     * 
     */

    /**
     * \var int j
     * 
     * \brief Variable de boucle pour les itérations dans la grille Sudoku.
     * 
     */

    /**
     * \var bool trouve
     * 
     * \brief Indicateur de présence de doublons.
     * 
     */

    /**
     * \var int blocLigne
     * 
     * \brief Indice de bloc de ligne dans la grille Sudoku.
     * 
     */

    /**
     * \var int blocColonne
     * 
     * \brief Indice de bloc de colonne dans la grille Sudoku.
     * 
     */
        
    int i,j;
    bool trouve;
    int blocLigne = (ligne - 1) / N;
    int blocColonne = (colonne - 1) / N;
    trouve = true;

    for(i=0; i<NB_LIGNES;i++)
    {
        if (g[ligne -1][i] == valeur)
        {
            printf("La valeur existe déjà dans la ligne.\n");
            trouve=false;
        }
        
    }

    for(i=0; i<NB_COLONNES;i++)
    {
        if (g[i][colonne - 1] == valeur) 
        {
            printf("La valeur existe déjà dans la colonne.\n");
            trouve= false;
        }


    }

    for (i = blocLigne * N; i < (blocLigne + 1) * N; i++) 
    {
        for (j = blocColonne * N; j < (blocColonne + 1) * N; j++) 
        {
            if (g[i][j] == valeur) 
            {
                printf("La valeur existe déjà dans le bloc.\n");
                trouve= false;
            }
        }
    }

    return trouve;

}


bool testgrille(tGrille g) 
{
    /**
     * \var int i
     * 
     * \brief Variable de boucle pour les itérations dans la grille Sudoku.
     * 
     */

    /**
     * \var int j
     * 
     * \brief Variable de boucle pour les itérations dans la grille Sudoku.
     * 
     */

    /**
     * \var int trouve
     * 
     * \brief Indicateur de présence de doublons.
     * 
     */
    int i, j;
    int trouve;
    trouve=false;
    for (i = 0; i < NB_LIGNES; i++)
    {
        for (j = 0; j < NB_COLONNES; j++)
        {
            if (g[i][j] == 0)
            {
                trouve= true; 
            }
        }
    }
    return trouve; 
}
