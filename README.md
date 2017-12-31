#   VERSION1 : 
>dans cette version on va traiter le cas de  rafraichisse automatiquement a chaque modification
survenue sur les sémaphores du groupe  :

pour faire l'exécution de ce traitement on va suivre les étapes se-dessous


** les etapes a suivre : **


-	commande1 : 
				>`>ipcs -s`                                //aprés prend un semid ( une valeur de `semid` ) et puis ..




-	commande2 :
				>`>gcc sem-monitor.c -o exe` 
				>`>./exe`  `semid`                           //sachant que semid est la valeur que t'as pris/a partir du  ipcs -s





-	commande3 : 
				>`>ipcs -s -i` `semid`                       //la meme valeur




## Resultat : 
 >on aura les meme affichage / les resources .
 >			si on lance la commande : '`ipcs -s -i` `semid`' et './exécutable `semid`'   ---> on aura le meme affichage   

****************************************************************************************************************


# PS:   les affichages de l'exécution de cette version sont dans ce doissier 



##ENJOY!