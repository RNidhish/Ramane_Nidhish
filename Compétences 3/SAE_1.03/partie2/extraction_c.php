#!/usr/bin/php
<?php
$fichierC = 'src2.c';
$contenuFichier = file_get_contents($fichierC);
$motif = '/\/\*\*(.*?)\*\//s';
preg_match_all($motif, $contenuFichier, $commentaires);

foreach ($commentaires[1] as $commentaire)
{
     echo $commentaire . PHP_EOL;
}
?>
