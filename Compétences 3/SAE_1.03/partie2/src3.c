/**
* 
* Ce programme permet de gérer les bulletins d'un·e étudiant·e au sein de l'IUT au cours de son année.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NB_UE 6 /** Nombre d'UE au cours d'un semestre */
#define NB_ETUDIANTS 122 /** Nombre d'étudiant·es inscrit·es */

float moyennes [NB_ETUDIANTS]; /** Liste des moyennes de chaque étudiant·e */

typedef struct {
int id ; /** Son identifiant allant de 0 à NB_ETUDIANTS-1 */
    char login[8]; /** Son login permettant de se connecter aux différentes plateformes */
    char prenom [20] ; /** Son prénom */
    char nom [20]; /** Son nom */
    float moyenneS1; /** Sa moyenne du premier semestre */
    float moyenneS2; /** Sa moyenne du second semestre */
    float moyenneAnnee; /** Sa moyenne sur l'année entière */
    float progression [30]; /** Historique de ses 30 dernières notes */
}   str_etudiant; /** Structure d'un·e étudiant·e */

int semaineActuelle; /** Entier égal à la semaine actuelle  */


typedef struct {
        int id ; /** Son identifiant allant de 0 à NB_UE-1 */
    char intitule[10]; /** Son intitulé */
    float moyenne ; /** Moyenne générale de tous les étudiant·es dans cette UE */
}str_ue; /** Structure d'une UE */

void ajoutNote(str_etudiant etudiant, str_ue ue, float note);
float courbeProgression(str_etudiant etudiant);

/**
* \brief Programme principal.
*
* \detail Le programme principal initialise l'étudiant·e à suivre, les UE qu'il/elle a choisi
* puis débute la boucle principale de saisi de notes et de suivi de progression
* jusqu'à atteindre la dernière semaine. 
*
* \return Code de sortie du programme (0 : sortie normale).
*
*/
int main()
{
    str_etudiant nathan;
    str_ue systeme;

    float note = 20; // Félicitations
    
    ajoutNote(nathan, systeme, note);
    courbeProgression(nathan);
    
    return EXIT_SUCCESS; /* Fin de l'année */
}

/**
*
* \brief Dessine la courbe de progression de l'étudiant·e.
*
* \detail Cette fonction utilise l'attribut d'historique des notes de la structure
*
*
* str_etudiant pour dessiner la progression de l'étudiant·e sur ses 30 notes dernières notes.
*
* \return float Coefficient de progression de l'élève.
*/
float courbeProgression(str_etudiant etudiant);
{
    int x[4],y[4],i;
    double put_x,put_y,t;
    float PI = 3.14159;
    int gr=DETECT,gm;

    initgraph(&gr,&gm,"C:\\TURBOC3\\BGI");
    printf("\n****** Bezier Curve ***********");
    printf("\n Please enter x and y coordinates ");

    for(i=0;i<4;i++)                 
    {
        scanf("%d%d",&x[i],&y[i]);
        putpixel(x[i],y[i],3); // Control Points
    }

    for(t=0.0;t<=1.0;t=t+0.001) // t always lies between 0 and 1
    {
        put_x = pow(1-t,3)*x[0] + 3*t*pow(1-t,2)*x[1] + 3*t*t*(1-t)*x[2] + pow(t,3)*x[3]; // Formula to draw curve
        put_y =  pow(1-t,3)*y[0] + 3*t*pow(1-t,2)*y[1] + 3*t*t*(1-t)*y[2] + pow(t,3)*y[3];
        putpixel(put_x,put_y, WHITE); // putting pixel 
    }
    getch();
    closegraph();

    return PI;
}

/**
*
* \brief Procédure permettant d'ajouter une nouvelle note
*
* \detail La procédure ajoute à l'étudiant·e ainsi qu'à l'UE la note passée en paramètre.
*
* \param str_etudiant etudiant Etudiant·e ayant une nouvelle note à rentrer
* \param str_ue ue UE correspondant à la nouvelle note
* \param float note Note à ajouter
*
*/




            void ajoutNote  (str_etudiant etudiant, str_ue ue, float note)
{
    char choix;
    double somme;
    printf("Numero du compte:");
    scanf("%d",&cli.numero_cmpt);
    if(!chercher_compte(fich,cli.numero_cmpt))
    {
        printf("Compte inexienstant...\n");
        return;
    }
    fread(&cli,sizeof(client),1,fich); // read from file
    printf("Compte %d\nNom %s\n Ancien solde %.2f\nNouveau solde %.2f\nDate %d/%d/%d\n",cli.numero_cmpt,cli.nom,cli.anc_solde,cli.nouv_solde,cli.date.jour,cli.date.mois,cli.date.annee);
    printf("Que voulez-vous faire?\n");
    do{
        printf("Versement:V\n Retrait:R\n Votre choix:");
        scanf("%c",&choix);
    }while (choix!='V'&& choix!='R');
    cli.anc_solde=cli.nouv_solde;
    printf("Somme:");
    scanf("%lf",&somme);
    if(somme<0.0)
    {
                somme=-somme;
    }
    if(choix='V') {
                cli.der_operation='V';
                cli.anc_solde+=somme;
    }
    else
    {
                cli.der_operation='R';
                cli.nouv_solde-=somme;
    }
    getDate(cli.date);
    fseek(fich,-11*sizeof(client),SEEK_CUR);
    fwrite(&cli,sizeof(client),1,fich);
    printf("Succes !");
}
