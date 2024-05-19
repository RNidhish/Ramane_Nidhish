#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define N 4
#define TAILLE (N * N)

typedef struct
{
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
    
} tCase1;

typedef tCase1 tGrille[TAILLE][TAILLE];

bool possible(tGrille g, int ligne, int colonne, int valeur);
void ajouterCandidat(tCase1 *laCase, int valeur);
void initialiserCandidats(tGrille g);
bool estCandidat(tCase1 laCase, int valeur);
int  nbCandidats(tCase1 laCase);
void retirerCandidat(tCase1 *laCase, int valeur);
void singleton_nu(tGrille g, bool *progression);
void singleton_cache(tGrille g, bool *progression);
bool backtracking(tGrille g, int numeroCase); 

void chargerGrille(tGrille g);
void afficherGrille(tGrille g);

clock_t  debut;
clock_t  fin;

int main()
{
    tGrille g;
    bool progression = true;

    chargerGrille(g);
    printf("Grille initiale  \n");
    afficherGrille(g);

    clock_t  debut = clock();

    initialiserCandidats(g);

    while (progression)
    {
        progression = false;
        singleton_nu(g, &progression);
        singleton_cache(g,&progression);
    }
    backtracking(g, 0);

    clock_t  fin = clock();

    printf("Grille finale  \n");
    afficherGrille(g);
    
    double Resolution = (fin - debut)*1.0 / CLOCKS_PER_SEC;
    printf( "Resolution de la grille en  %.6lf sec\n",Resolution);
    
}

void chargerGrille(tGrille g)
{
    char nomFichier[30];
    FILE *f;
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
                g[i][j].valeur = valeurLue;
            }
        }
    }
    fclose(f);
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
            if (g[i][j].valeur == 0)
            {
                printf(" . ");
            }
            else
            {
                if(g[i][j].valeur < 10)
                { 
                    printf(" %d ", g[i][j].valeur);
                }
                
                else
                {
                    printf("%d ", g[i][j].valeur);
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

bool backtracking(tGrille g, int numeroCase) 
{
   
    int ligne, colonne;
    bool resultat = false;
    
    if (numeroCase == TAILLE * TAILLE) 
    {
        //on a traité toutes les cases, la grille est résolue
        resultat = true;
    } 
    
    else 
    {
        // On récupère les "coordonnées" de la case
        ligne = numeroCase / TAILLE;
        colonne = numeroCase % TAILLE;
    

        if (g[ligne][colonne].valeur != 0) 
        {
            // Si la case n’est pas vide, on passe à la suivante
            // (appel récursif)
            resultat = backtracking(g, numeroCase + 1);
        }
        else 
        {
            for (int valeur = 0; valeur < g[ligne][colonne].nbCandidats ; valeur++) 
            {
                
                if (possible(g,ligne,colonne,g[ligne][colonne].candidats[valeur]))
                {
                    // Si la valeur est autorisée on l'inscrit
                    //dans la case...

                    g[ligne][colonne].valeur = g[ligne][colonne].candidats[valeur];             
                    // ... et on passe à la suivante : appel récursif
                    // pour voir si ce choix est bon par la suite

                    if  (backtracking(g, numeroCase + 1)) 
                    {       
                        resultat = true;
                    }
                    else 
                    {        
                        g[ligne][colonne].valeur = 0;
                    }
                }
            }
        }
    }
    return resultat;
}

bool possible(tGrille g, int ligne, int colonne, int valeur)
{
    int i, j;
    int blocLigne = (ligne ) / N;
    int blocColonne = (colonne) / N;

    bool possible = true;
    i = 0;
    while(i < TAILLE && possible)
    {
        if (g[ligne][i].valeur == valeur)
        {
            possible = false;
            
        }
        i++;
    }

    i = 0;
    while (i < TAILLE && possible)
    {
        if (g[i][colonne].valeur == valeur)
        {
            possible = false;
        }
        i++;
    }
    
    i = blocLigne * N;
    
    while (i < (blocLigne + 1) * N && possible)
    {
        j = blocColonne * N;
        while ( j < (blocColonne + 1) * N && possible)
        {
            if (g[i][j].valeur == valeur)
            {
                possible = false;
            }
            j++;
        }
        i++;
    }
    
    return possible;
}

void ajouterCandidat(tCase1 *laCase, int valeur)
{
    laCase->candidats[laCase->nbCandidats] = valeur;
    laCase->nbCandidats++;
}

int nbCandidats(tCase1 laCase)
{
    return laCase.nbCandidats;
}

bool estCandidat(tCase1 laCase, int valeur)
{
    int i = 0;
    while (i < laCase.nbCandidats && valeur != laCase.candidats[i])
    {
        i++;
    }
    return i < laCase.nbCandidats;
}

void initialiserCandidats(tGrille g)
{
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            g[i][j].nbCandidats = 0; 
            
            for (int valeur = 1; valeur <= TAILLE; valeur++)
            {
                if (possible(g, i, j, valeur))
                {
                    ajouterCandidat(&g[i][j], valeur);
                }
            }
        }
    }
}

void retirerCandidat(tCase1 *laCase, int valeur)
{
    int i = 0;
    while (i < laCase->nbCandidats && valeur != laCase->candidats[i])
    {
        i++;
    }

    if (i < laCase->nbCandidats)
    {
        while (i < laCase->nbCandidats - 1)
        {
            laCase->candidats[i] = laCase->candidats[i + 1];
            i++;
        }
    }
}

 void singleton_nu(tGrille g, bool *progression)
{
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            if (g[i][j].valeur == 0 && g[i][j].nbCandidats == 1)
            {
                g[i][j].valeur = g[i][j].candidats[0];
               // retirerCandidat(&g[i][j], g[i][j].valeur);
                *progression = true;
            }
        }
    }
    initialiserCandidats(g);
}    

void singleton_cache(tGrille g, bool *progression)
{
    int lig, col, val;
    int Ligtemp=0;
    int Coltemp=0;
    int candidat= 0;
    int compteur = 0;

    // Traitement des lignes
    for (lig = 0; lig < TAILLE; lig++)
    {
        for (val = 1; val <= TAILLE; val++)
        {
            Ligtemp=0;
            Coltemp=0;
            compteur = 0;
            col = 0; 

            while ( col < TAILLE && compteur < 2 )
            {
                if(g[lig][col].valeur == 0 )
                {
                    candidat=0;

                    while (candidat < g[lig][col].nbCandidats && compteur < 2)
                    {
                        if(g[lig][col].candidats[candidat] == val)
                        {
                            if (compteur == 1 && col!= Coltemp )
                            {
                                compteur++;
                            }
                            else if(compteur == 0)
                            {
                                
                                Ligtemp=lig;
                                Coltemp=col;
                                compteur ++;

                            }
                        }
                        candidat ++;
                    }
                }
            col++;
            }

            if (compteur == 1 && Coltemp <= TAILLE)
            {
                g[Ligtemp][Coltemp].valeur = val;
                *progression = true;
            }
        }
    }

    initialiserCandidats(g);

    // Traitement des colonnes
    for (col = 0; col < TAILLE; col++)
    {
        for (val = 1; val <= TAILLE; val++)
        {
            compteur = 0;
            Ligtemp = 0;
            Coltemp=0;
            lig=0;

            while (lig < TAILLE && compteur < 2)
            {
                if (g[lig][col].valeur == 0)
                {
                    candidat = 0;

                    while (candidat < g[lig][col].nbCandidats && compteur < 2)
                    {
                        if(g[lig][col].candidats[candidat] == val)
                        {
                            if (compteur == 1 && lig != Ligtemp)
                            {
                                compteur++;
                            }
                            else if (compteur == 0)
                            {
                                compteur++;
                                Ligtemp = lig;
                                Coltemp=col;
                            }
                        }
                        candidat++;
                    }
                }
                lig++;
            }

            if (compteur == 1 && Ligtemp <= TAILLE)
            {
                g[Ligtemp][col].valeur = val;
                *progression = true;
            }
        }
    } 

    initialiserCandidats(g);

    // Traitement des blocs
     for (int ligbloc = 0; ligbloc < TAILLE; ligbloc += N)
    {
        for (int colbloc = 0; colbloc < TAILLE; colbloc += N)
        {
            for (val = 1; val <= TAILLE; val++)
            {
                compteur = 0;
                Ligtemp = 0;
                Coltemp = 0;
                
                for (lig = ligbloc; lig < ligbloc + N; lig++)
                {
                    for (col = colbloc; col < colbloc + N; col++)
                    {
                        if (g[lig][col].valeur == 0)
                        {
                            candidat = 0;

                            while (candidat < g[lig][col].nbCandidats && compteur < 2)
                            {
                                if(g[lig][col].candidats[candidat] == val)
                                {
                                    if (compteur == 1 && (lig != Ligtemp || col != Coltemp))
                                    {
                                        compteur++;
                                    }
                                    else if (compteur == 0)
                                    {
                                        compteur++;
                                        Ligtemp = lig;
                                        Coltemp = col;
                                    }
                                }
                                
                                candidat++;
                            }
                        }
                    }
                }

                if (compteur == 1 && Ligtemp < ligbloc + N && Coltemp < colbloc + N)
                {
                    g[Ligtemp][Coltemp].valeur = val;
                    *progression = true;
                }
            }
        }
    } 
    initialiserCandidats(g);
}

