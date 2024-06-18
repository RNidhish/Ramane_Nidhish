
<?php
    $fichier_md= file('DOC_UTILISATEUR.md');
    //print_r($fichier_md);
    ?>
<!DOCTYPE html>
<html lang="fr">
<head>
<title>Document</title>
</head>
<body>
    <main>

        <?php
        foreach($fichier_md as $line)
        {
            if(str_starts_with($line,'# '))
            {
                $line = ltrim($line,'# ') ;
                echo "<h1>$line<\h1> \n";
            }
            
            if(str_starts_with($line,'## '))
            {
                $line = ltrim($line,'## ') ;
                echo "<h2>$line<\h2> \n";
            }

            if(str_starts_with($line,'### '))
            {
                $line = ltrim($line,'### ') ;
                echo "<h3>$line<\h3> \n";
            }

            if(str_starts_with($line,'#### '))
            {
                $line = ltrim($line,'#### ') ;
                echo "<h4>$line<\h4> \n";
            }

        }
        ?>

        <dl>
            <?php
                foreach($fichier_md as $line)
                {
                    if(str_starts_with($line,'# '))
                        






                }
         

    </main>

        
</body>

