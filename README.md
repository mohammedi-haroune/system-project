# Excercice 4 (pipe)
##      version 1 :
Dans cette version on va traiter que le cas de recupération des commandes et l'exécuté
Alors une fois on lance l'exécution par exemple `./exe cmd`
on récupére le contenu de cmd et puis on la traite comme une commande ecrite sur l'invite de commande

##      version 2 :

dans la version suivante, on gérer le traitement du commande avec un processus
cette version est presque la meme chose avec la premiére version, mais on montre
l'aspect de creation d'un processus fils et l'affichage de son pid

##      version 3 :

dans la version suivante, on gérer le meme traitement  avec plusieurs processus en utilisant la fonction fork()
et on peut dire aussi que cette version ressemle avec les deux premiers versions, mais la on traite les commande passé en argument
*--> chaque processus exécute une commande .
alors si on passe plusieurs commande en arguments , ils seront exécuté par la suite par les processus crée
**PS** le nombre de processus créé egale au nombre de commande passé en argument
