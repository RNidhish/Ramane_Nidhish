/**
* 
* Ce programme permet de simuler la gestion d'un système bancaire à petite échelle.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NB_CLIENTS 100 /** Nombre de client·e·s maximum que le programme peut gérer */
#define NB_EMPLOYES 10 /** Nombre d'employé·e·s nécessaires pour encadrer le nombre de client*/

#define NB_AGENCES 4 /** Nombre d'agences que la banque posséde */


int listeAgences[NB_AGENCES]; /** Liste des agences par leur numéro d'identification */

typedef struct {
        int id ; /** Son identifiant */
    char nom[10]; /** Son nom */
    char dernierRdv [8] ; /** Date de son dernier rendez-vous */
    int agence; /** L'agence qui lui est assignée */
}   str_client; /** Structure d'un·e client·e */

int chiffreAffaire; /** Entier permettant de suivre le chiffre d'affaire réalisé */

void nouveauRdv(str_client client, char date []);

typedef struct {
        int id ; /** Son identifiant */
    char nom[10]; /** Son nom */
    char status ; /** Son status dans l'agence où il travaille */
    int agence; /** L'agence qui lui est assignée */
}   str_employe; /** Structure d'un·e employé·e */
float projectionAnnee();

/**
* \brief Programme principal.
*
* \detail Le programme principal permet d'initialiser et de suivre NB_CLIENTS clients répartis dans
* NB_AGENCES agences et gérés par NB_EMPLOYES sur le cours d'une année puis de simuler une projection
* pour l'année suivante.
*
* \return int Code de sortie du programme (0 : sortie normale).
*
*/
int main()
{
    str_client nathan;
    str_employe eliott;

    char bday [8] = "27/03/24";
    nathan.agence = listeAgences[3];
    
    nouveauRdv(nathan,bday);
    projectionAnnee();
    
    return EXIT_SUCCESS; /* Fin de la simulation */
}

/**
*
* \brief Réalise une projection sur l'année suivante.
*
* \detail Cette fonction utilise toutes les données récupérées au cours de l'année pour
* réaliser une projection sur l'année suivante. Elle dessine une courbe détaillée
* en incluant des pistes stratégiques à envisager.
*
* \return float Chiffre d'affaire estimée pour l'année suivante.
*/
float projectionAnnee();
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
* \brief Procédure permettant au client de préparer un nouveau rendez-vous
*
* \detail La procédure demande à l'utilisateur de choisir une date pour son prochain rendez-vous
* et de choisir le type de rendez-vous souhaité pour lui permettre de le préparer convenablement.
*
* \param str_client client Client souhaitant un nouveau rendez-vous.
* \param char[] date Date du prochain rendez-vous.
*/ void nouveauRdv(str_client client, char date [])
{
    str_client cli;
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
