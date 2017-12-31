#   Version 3 (automatic refresh) : 
Dans cette version on va traiter le cas de  rafraichisse automatiquement a chaque modification
survenue sur les sémaphores du groupe  :

pour faire l'exécution de ce traitement on va suivre les étapes se-dessous


**les etapes a suivre :**


1. `ipcs -s` 
aprés prend un semid ( une valeur de `semid` ) et puis
2. ` gcc sem-monitor.c -o exe` puis `./exe semid `
sachant que semid est la valeur que t'as pris/a partir du  ipcs -s
3. `ipcs -s -i` `semid`  la meme valeur


## Resultat : 
Si on lance la commande : '`ipcs -s -i semid`' et `./exe semid`'   ---> on aura le meme affichage.
![ipcs](../out/2-The result when i execute my program.png "`ipcs -s -i semid`")


## ENJOY!
