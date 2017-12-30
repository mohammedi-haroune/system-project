# Question 1 (Implementaion de la solution)
## Enoncé

> Fixer P dans les deux programmes et passer N au clavier. Lancer les deux programmes dans deux terminaux différents. En prenant le soin de toujours lancer le processus voiture d'abord (car c'est lui qui va créer tout ce qui est nécessaire pour le problème, les sémaphores par exp).

## Réponse
Pour l’implémentation du problème donnée en utilisant le système
`IPC V`, on a définit les sémaphores indiqué dans la solution théorique
donnée à l’aide des appels système linux `semget, semctl` et une mémoire
partagée pour sauvegarder le nombre de clients embarquées et débarquées
(la structure `state`). les mémoires partagées sont gérées à l’aide des
appels système `shmget, shmat`. Notant que l’utlisation de ces appels
système nécessite la création d’un clé `key_t`.

Pour facilité la tache de compilation des différents fichiers **C** on a
utlisé l’outil **CMake**. Pour cela on a écrit le fichier `CMakeLists.txt`
qui contient tout les information concernant les fichiers du project.

## Basic usage
le dossier `code` contient les tois programmes suivants : `voiture`, `clients` et `run_clients`.

le programme `run_clients` prend un numéro **N** en paramètre et execute N processus `clients`.

Etapes : 

1. première étape : compilation des différents programmes
```shell
make voiture
make clients 
make run_clients
```
l'exécution de ces trois commandes compile et crée les exécutable nommée `voiture`, `clients`, `run_clients` respectivement.

2. Dans un terminal exécuter le porgramme `voiture` avec la commade `./voiture`.

3. Dans un autre terminal éxécuter le programme `run_clients` avec un numéro superieur à 3 (P est égale à 3 par défaul)

4. Enjoy !
