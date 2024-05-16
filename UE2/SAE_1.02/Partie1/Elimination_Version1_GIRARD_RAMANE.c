#include <stdio.h>
#include <stdbool.h>

#define N 3
#define TAILLE (N * N)

typedef struct
{
    int valeur;
    int candidats[TAILLE];
    int nbCandidats;
} tCase1;

typedef tCase1 tGrille[TAILLE][TAILLE];
void ajouterCandidat(tCase1 *laCase, int valeur);
void retirerCandidat(tCase1 *laCase, int valeur, int nbCandidatsElimines);
bool estCandidat(tCase1 laCase, int valeur);
int nbCandidats(tCase1 laCase);
bool possible(tGrille g, int ligne, int colonne, int valeur);
void initialiserCandidats(tGrille g, int *nbCasesRemplies, int *nbCasesVidesInitial, int *nbCandidatsInitial);
void afficherGrille(tGrille g);
void singleton_nu(tGrille g);
void singleton_cache(tGrille g);
void paire_nue(tGrille g);
void paire_cachee(tGrille g);
void afficherstats(tGrille g, int nbCasesVides, int nbCasesRemplies, int nbCasesVidesInitial, int nbCandidatsElimines, int nbCandidatsInitial);
int chargerGrille(tGrille g);

int main()
{
    tGrille g;
    int nbCasesRemplies = 0;
    int nbCasesVidesInitial = 0;
    int nbCandidatsElimines = 0;
    int nbCandidatsInitial = 0;
    int nbCasesVides = chargerGrille(g);
    printf("Grille de départ : \n");
    afficherGrille(g);

    // Initialisation des candidats
    initialiserCandidats(g, &nbCasesRemplies, &nbCasesVidesInitial, &nbCandidatsInitial);

    // afficherGrille(g);

    bool progression = true;

    while(nbCasesVides != 0 && progression)
    {
        progression = false;

        singleton_nu(g);
        singleton_cache(g);
        paire_nue(g);
        paire_cachee(g);

        for (int i = 0; i < TAILLE; i++)
        {
            for (int j = 0; j < TAILLE; j++)
            {
                if (g[i][j].valeur == 0 && nbCandidats(g[i][j]) == 1)
                {
                    g[i][j].valeur = g[i][j].candidats[0];
                    nbCasesVides--;

                    for (int k = 0; k < TAILLE; k++)
                    {
                        singleton_nu(g);
                        singleton_cache(g);
                        paire_nue(g);
                        paire_cachee(g);
                    }
                        progression = true;
                }
            }
        }
    }

    // Afficher la grille après la résolution
    printf("Grille complétée : \n");
    afficherGrille(g);

    // Affichage des statistiques

    afficherstats(g, nbCasesVides, nbCasesRemplies, nbCasesVidesInitial, nbCandidatsElimines, nbCandidatsInitial);

    return 0;
}

void ajouterCandidat(tCase1 *laCase, int valeur)
{
    laCase->candidats[laCase->nbCandidats] = valeur;
    laCase->nbCandidats++;
}

void retirerCandidat(tCase1 *laCase, int valeur, int nbCandidatsElimines)
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
        laCase->nbCandidats--;
        nbCandidatsElimines++;
    }
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

int nbCandidats(tCase1 laCase)
{
    return laCase.nbCandidats;
}

bool possible(tGrille g, int ligne, int colonne, int valeur)
{
    int i, j;
    int blocLigne = (ligne - 1) / N;
    int blocColonne = (colonne - 1) / N;

    for (i = 0; i < TAILLE; i++)
    {
        if (g[ligne][i].valeur == valeur)
        {
            // printf("La valeur existe déjà dans la ligne.\n");
            return false;
        }
    }

    for (i = 0; i < TAILLE; i++)
    {
        if (g[i][colonne].valeur == valeur)
        {
            // printf("La valeur existe déjà dans la colonne.\n");
            return false;
        }
    }

    for (i = blocLigne * N; i < (blocLigne + 1) * N; i++)
    {
        for (j = blocColonne * N; j < (blocColonne + 1) * N; j++)
        {
            if (g[i][j].valeur == valeur)
            {
                // printf("La valeur existe déjà dans le bloc.\n");
                return false;
            }
        }
    }

    return true;
}

void initialiserCandidats(tGrille g, int *nbCasesRemplies, int *nbCasesVidesInitial, int *nbCandidatsInitial)
{
    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            if (g[i][j].valeur != 0)
            {
                (*nbCasesRemplies)++;
            }
            else
            {
                (*nbCasesVidesInitial)++;
            }

            g[i][j].nbCandidats = 0; // Réinitialiser le nombre de candidats à zéro ici

            for (int valeur = 1; valeur <= TAILLE; valeur++)
            {
                if (possible(g, i, j, valeur))
                {
                    ajouterCandidat(&g[i][j], valeur);
                    (*nbCandidatsInitial)++;
                }
            }
        }
    }
}

void afficherGrille(tGrille g)
{

    int i, j, k;
    k = 1;

    printf("\t    1 2 3   4 5 6   7 8 9\n");
    for (i = 0; i < TAILLE; i++)
    {
        if (i % 3 == 0)
        {

            printf("\t  +-------+-------+-------+\n");
        }

        printf("\t%d | ", k);
        k++;
        for (j = 0; j < TAILLE; j++)
        {
            if (g[i][j].valeur == 0)
                printf(". ");
            else
                printf("%d ", g[i][j].valeur);

            if ((j + 1) % 3 == 0)

                printf("| ");
        }

        printf("\n");
    }
    printf("\t  +-------+-------+-------+\n");
}

void afficherstats(tGrille g, int nbCasesVides, int nbCasesRemplies, int nbCasesVidesInitial, int nbCandidatsElimines, int nbCandidatsInitial)
{
    float tauxRemplissage = 0.0;
    float pourcentageElimination = 0.0;

    if (nbCasesVidesInitial != 0)
    {
        tauxRemplissage = (nbCasesRemplies / (nbCasesVidesInitial * 1.0)) * 100.0;
    }

    if (nbCandidatsInitial != 0)
    {
        pourcentageElimination = (nbCandidatsElimines / (nbCandidatsInitial * 1.0)) * 100.0;
    }
    printf("*****   Résultat pour  GrilleG.sud   ******** \n");
    printf("Nombre de cases remplies : %d sur %d\n", nbCasesRemplies, nbCasesVides);
    printf("Taux de remplissage : %.2f%%\n", tauxRemplissage);
    printf("Nombre de candidats éliminés : %d\n", nbCandidatsElimines);
    printf("Pourcentage d'élimination des candidats : %.2f%%\n", pourcentageElimination);
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
                g[i][j].valeur = valeurLue;
                if (valeurLue == 0)
                {
                    compteur = compteur + 1;
                }
            }
        }
    }
    return compteur;
}

// fonction singleton nue ...(tGrille g)

// ... (Les parties du programme précédentes restent inchangées)

// Fonction pour trouver et remplir les singletons nus dans une ligne, colonne ou bloc

// Fonction pour trouver et remplir les singletons nus dans une ligne, colonne ou bloc
void singleton_nu(tGrille g)
{
    int i, j, k;

    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            if (g[i][j].valeur == 0)
            {
                // Vérifie les candidats dans la ligne
                for (k = 0; k < TAILLE; k++)
                {
                    if (k != j && g[i][k].valeur == 0)
                    {
                        for (int l = 0; l < g[i][j].nbCandidats; l++)
                        {
                            retirerCandidat(&g[i][k], g[i][j].candidats[l], 0);
                        }
                    }
                }

                // Vérifie les candidats dans la colonne
                for (k = 0; k < TAILLE; k++)
                {
                    if (k != i && g[k][j].valeur == 0)
                    {
                        for (int l = 0; l < g[i][j].nbCandidats; l++)
                        {
                            retirerCandidat(&g[k][j], g[i][j].candidats[l], 0);
                        }
                    }
                }

                // Vérifie les candidats dans le bloc
                int blocLigne = i / N;
                int blocColonne = j / N;

                for (k = blocLigne * N; k < (blocLigne + 1) * N; k++)
                {
                    for (int l = blocColonne * N; l < (blocColonne + 1) * N; l++)
                    {
                        if (k != i && l != j && g[k][l].valeur == 0)
                        {
                            for (int m = 0; m < g[i][j].nbCandidats; m++)
                            {
                                retirerCandidat(&g[k][l], g[i][j].candidats[m], 0);
                            }
                        }
                    }
                }

                // Si un seul candidat reste, le placer dans la case
                if (nbCandidats(g[i][j]) == 1)
                {
                    g[i][j].valeur = g[i][j].candidats[0];
                    retirerCandidat(&g[i][j], g[i][j].valeur, 0);
                }
            }
        }
    }
}

// Fonction pour détecter le singleton caché dans un bloc, une ligne ou une colonne
void singleton_cache(tGrille g)
{
    int i, j, k, l, m;

    // Parcours des blocs
    for (i = 0; i < TAILLE; i += N)
    {
        for (j = 0; j < TAILLE; j += N)
        {
            // Parcours des valeurs possibles
            for (k = 1; k <= TAILLE; k++)
            {
                int count = 0; // Compteur de candidats pour la valeur k

                int candidat_ligne = -1;
                int candidat_col = -1;

                // Parcours des cellules dans le bloc
                for (l = i; l < i + N; l++)
                {
                    for (m = j; m < j + N; m++)
                    {
                        if (g[l][m].valeur == 0 && estCandidat(g[l][m], k))
                        {
                            count++;
                            candidat_ligne = l;
                            candidat_col = m;
                        }
                    }
                }

                // Si une seule occurrence de la valeur k est trouvée, la placer dans la case correspondante
                if (count == 1)
                {
                    g[candidat_ligne][candidat_col].valeur = k;
                    retirerCandidat(&g[candidat_ligne][candidat_col], k, 0);
                }
            }
        }
    }

    // Parcours des lignes
    for (i = 0; i < TAILLE; i++)
    {
        for (k = 1; k <= TAILLE; k++)
        {
            int count = 0; // Compteur de candidats pour la valeur k

            int candidate_col = -1;

            // Parcours des cellules dans la ligne
            for (j = 0; j < TAILLE; j++)
            {
                if (g[i][j].valeur == 0 && estCandidat(g[i][j], k))
                {
                    count++;
                    candidate_col = j;
                }
            }

            // Si une seule occurrence de la valeur k est trouvée, la placer dans la case correspondante
            if (count == 1)
            {
                g[i][candidate_col].valeur = k;
                retirerCandidat(&g[i][candidate_col], k, 0);
            }
        }
    }

    // Parcours des colonnes
    for (j = 0; j < TAILLE; j++)
    {
        for (k = 1; k <= TAILLE; k++)
        {
            int count = 0; // Compteur de candidats pour la valeur k

            int candidate_row = -1;

            // Parcours des cellules dans la colonne
            for (i = 0; i < TAILLE; i++)
            {
                if (g[i][j].valeur == 0 && estCandidat(g[i][j], k))
                {
                    count++;
                    candidate_row = i;
                }
            }

            // Si une seule occurrence de la valeur k est trouvée, la placer dans la case correspondante
            if (count == 1)
            {
                g[candidate_row][j].valeur = k;
                retirerCandidat(&g[candidate_row][j], k, 0);
            }
        }
    }
}

// Fonction pour détecter la paire nue dans un bloc
void paire_nue(tGrille g)
{
    int i, j, k, l, m;

    // Parcours des blocs
    for (i = 0; i < TAILLE; i += N)
    {
        for (j = 0; j < TAILLE; j += N)
        {
            // Parcours des paires de valeurs possibles
            for (k = 1; k <= TAILLE - 1; k++)
            {
                for (l = k + 1; l <= TAILLE; l++)
                {
                    int count = 0; // Compteur de paires nues

                    int ligne_paire1 = -1, colonne_paire1 = -1;
                    int ligne_paire2 = -1, colonne_paire2 = -1;

                    // Parcours des cellules dans le bloc
                    for (m = 0; m < N * N; m++)
                    {
                        int ligne = i + m / N;
                        int colonne = j + m % N;

                        if (g[ligne][colonne].valeur == 0 && nbCandidats(g[ligne][colonne]) == 2 &&
                            (estCandidat(g[ligne][colonne], k) && estCandidat(g[ligne][colonne], l)))
                        {
                            count++;
                            if (count == 1)
                            {
                                ligne_paire1 = ligne;
                                colonne_paire1 = colonne;
                            }
                            else if (count == 2)
                            {
                                ligne_paire2 = ligne;
                                colonne_paire2 = colonne;
                            }
                        }
                    }

                    // Si une paire nue est trouvée, éliminer les candidats de toutes les autres cases du bloc
                    if (count == 2)
                    {
                        for (m = 0; m < N * N; m++)
                        {
                            int ligne = i + m / N;
                            int colonne = j + m % N;

                            if ((ligne != ligne_paire1 || colonne != colonne_paire1) &&
                                (ligne != ligne_paire2 || colonne != colonne_paire2))
                            {
                                retirerCandidat(&g[ligne][colonne], k, 0);
                                retirerCandidat(&g[ligne][colonne], l, 0);
                            }
                        }
                    }
                }
            }
        }
    }
}

// Fonction pour détecter la paire cachée dans un bloc, une ligne ou une colonne
void paire_cachee(tGrille g)
{
    int i, j, k, l, m;

    // Parcours des blocs
    for (i = 0; i < TAILLE; i += N)
    {
        for (j = 0; j < TAILLE; j += N)
        {
            // Parcours des paires de valeurs possibles
            for (k = 1; k <= TAILLE - 1; k++)
            {
                for (l = k + 1; l <= TAILLE; l++)
                {
                    int compteur = 0; // Compteur de paires cachées

                    int lignePaire1 = -1, colonnePaire1 = -1;
                    int lignePaire2 = -1, colonnePaire2 = -1;

                    // Parcours des cellules dans le bloc
                    for (m = 0; m < N * N; m++)
                    {
                        int ligne = i + m / N;
                        int colonne = j + m % N;

                        if (estCandidat(g[ligne][colonne], k) && estCandidat(g[ligne][colonne], l))
                        {
                            compteur++;
                            if (compteur == 1)
                            {
                                lignePaire1 = ligne;
                                colonnePaire1 = colonne;
                            }
                            else if (compteur == 2)
                            {
                                lignePaire2 = ligne;
                                colonnePaire2 = colonne;
                            }
                        }
                    }

                    // Si une paire cachée est trouvée, éliminer les autres candidats de ces deux cases
                    if (compteur == 2 && (lignePaire1 / N == lignePaire2 / N) && (colonnePaire1 / N == colonnePaire2 / N))
                    {
                        for (m = 0; m < N * N; m++)
                        {
                            int ligne = i + m / N;
                            int colonne = j + m % N;

                            if ((ligne != lignePaire1 && ligne != lignePaire2) || (colonne != colonnePaire1 && colonne != colonnePaire2))
                            {
                                retirerCandidat(&g[ligne][colonne], k, 0);
                                retirerCandidat(&g[ligne][colonne], l, 0);
                            }
                        }
                    }
                }
            }
        }
    }

    // Parcours des lignes
    for (i = 0; i < TAILLE; i++)
    {
        // Parcours des paires de valeurs possibles
        for (k = 1; k <= TAILLE - 1; k++)
        {
            for (l = k + 1; l <= TAILLE; l++)
            {
                int compteur = 0; // Compteur de paires cachées

                int colonnePaire1 = -1;
                int colonnePaire2 = -1;

                // Parcours des cellules dans la ligne
                for (j = 0; j < TAILLE; j++)
                {
                    if (estCandidat(g[i][j], k) && estCandidat(g[i][j], l))
                    {
                        compteur++;
                        if (compteur == 1)
                        {
                            colonnePaire1 = j;
                        }
                        else if (compteur == 2)
                        {
                            colonnePaire2 = j;
                        }
                    }
                }

                // Si une paire cachée est trouvée, éliminer les autres candidats de ces deux cases
                if (compteur == 2)
                {
                    for (j = 0; j < TAILLE; j++)
                    {
                        if (j != colonnePaire1 && j != colonnePaire2)
                        {
                            retirerCandidat(&g[i][j], k, 0);
                            retirerCandidat(&g[i][j], l, 0);
                        }
                    }
                }
            }
        }
    }

    // Parcours des colonnes
    for (j = 0; j < TAILLE; j++)
    {
        // Parcours des paires de valeurs possibles
        for (k = 1; k <= TAILLE - 1; k++)
        {
            for (l = k + 1; l <= TAILLE; l++)
            {
                int compteur = 0; // Compteur de paires cachées

                int lignePaire1 = -1;
                int lignePaire2 = -1;

                // Parcours des cellules dans la colonne
                for (i = 0; i < TAILLE; i++)
                {
                    if (estCandidat(g[i][j], k) && estCandidat(g[i][j], l))
                    {
                        compteur++;
                        if (compteur == 1)
                        {
                            lignePaire1 = i;
                        }
                        else if (compteur == 2)
                        {
                            lignePaire2 = i;
                        }
                    }
                }

                // Si une paire cachée est trouvée, éliminer les autres candidats de ces deux cases
                if (compteur == 2)
                {
                    for (i = 0; i < TAILLE; i++)
                    {
                        if (i != lignePaire1 && i != lignePaire2)
                        {
                            retirerCandidat(&g[i][j], k, 0);
                            retirerCandidat(&g[i][j], l, 0);
                        }
                    }
                }
            }
        }
    }
}
