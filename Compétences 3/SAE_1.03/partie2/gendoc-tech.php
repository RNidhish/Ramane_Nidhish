#!/usr/bin/php
<?php
$jour = "Bonjour";
$fichier = file('src1.c');
// Commentaires
$tete = array();

// Booléen
$estTete = false;

// En-tête
$tete[0] = $fichier[0];

if (str_contains($tete[0], "/**")) {
    $estTete = true;
    $deb = 1;
    foreach ($fichier as $cle => $ligne) {
        if (str_contains($ligne, "*/") && $estTete) {
            $estTete = false;
            getEnTete($deb, $cle);
        }
    }
}

function getEnTete($deb, $fin)
{
    global $fichier;
    global $tete;
    $j = 0;
    for ($i = $deb; $i < $fin; $i++) {
        trim($fichier[$i]);
        preg_match_all('/[a-zA-Z ]+/', $fichier[$i], $tete);
        print_r($tete);
        $j++;
    }
    //print_r($tete);
}

?>