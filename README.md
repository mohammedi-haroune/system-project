# Question 4 (Utilisation du \texttt{semtimedop})
## Enoncé
> Que se passera t il si il n'y a pas p client pour monter dans la voiture? (donnez n<p). Expliquer la raison du problème remarqué.
>Pour régler ce problème utilisez la fonction semtimedop au lieu de semop (créez une nouvelle fonction appelée Ptimed par exp). Expliquer le principe de la fonction semtimedop et comment l'utiliser pour régler le problème précédant. (man 2 semtimedop).

## Réponse

### Pricipe du `semtimedop`

`semtimedop()` se comporte comme `semop()` sauf que dans le cas où le
processus doit dormir, la durée maximale du sommeil est limitée par la
valeur spécifiée dans la structure ` timespec ` dont l’adresse est
transmise dans le paramètre timeout. Si la limite indiquée a été
atteinte, `semtimedop()` échoue avec errno contenant ` EAGAIN ` (et
aucune opération de sops n’est réalisée).

### Solution Théorique

l’utilisation d’une fonction `Ptimed` au lieu de `P` dans le processus
voiture avec le sémaphore `semTousAbord` nous permet de garantir une
attente borné dans la file du sémaphore en question. Après la libération
le processus voiture remet a zéro la valeur du variable `nbEmbarques` et
du sémaphore `semEmbarquemnt` (appeles successifs du `V` pour bloquer
les eventueles clients qui arrivent). Il vérifie si il ya plus de
`C / 3` client dans la variable `nbEmbarques` si oui il commence a
tourner (fonction `rouler()`) sinon il décharge les clients et tente une
autre fois.

lors du déchargement on fait la meme chose avec la variable
`nbDebarques` et les sémaphores `semDebarquement` et `semTousDehors`.

### Implementaion

la valeur `EAGAIN` dans `errno` nous permet de savoir si la terminison
du fonction `semtimedop` est dû à l’écoulement du temps spécifiée dans
`timeout`, les valeurs des variables et des sémaphores sont
réinitialisées à l’aide des fonctions défine dans notre librarie
`semaphore1.h` notament `setNbDebarques`, `setNbEmbarques` et
`V(semid, id`.

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
