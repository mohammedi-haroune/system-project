# Question 5 (Implementaion d'une barrière)
## Enoncé
> Implémenter une barrière de synchronisation (ou RDV) réutilisable entre un groupe de N processus a ajouter a votre bibliothèque. Le principe : tout le monde dors en appelant P sur un sémaphore et le dernier arrivé appellera V en boucle (N-1) pour réveiller tout les processus bloqués. Inspirez vous du code fournie.

# Réponse
### Solution Théorique
La solution proposé est d’écrire une fonction `join(n)` qui appele `P`
sur un sémaphore (c’est elle qui va le crée lors du premier appele) pour
les premiers (N - 1) processus sauf le dernier pour le quelle elle
appellera `V` en boucle pour réveiller tout les (N - 1) processus
bloqués.

### Implementaion
Pour savoir le nombre de nombre de processus qui attend dans la file
d’un sémaphore donée on a implementé une fonction `getNConf` qui fait
appele à la fonction `semctl` avec le flag `GETNCNT`

La fonction `join(n)` avec l’utlisation de la fonction `semget` avec les
flags `IPC_CREATE | IPC_EXCL | 0666` vérifie si un sémaphore est créer.
si oui elle vérifie la valuer de sémaphore (fonction `getNConf`) si la
valeur est inférieur à **N** elle appele `V` en boulce sur le sémaphore
crée précedement sinon elle `P` pour bloquer le processus. dans le cas
où le groupe du sémaphore est n’est pas créer (`semget` retourne **-1**)
la fonction créer un et l’initialise à **0**.

### Resultats de l’execution avec `N = 3`

## Basic usage
le programme `barriere` implemente un simple test de la fonction `join` avec paramètre `n == 3`.
Etapes : 

1. première étape : compilation du programme
```shell
make barriere
```
2. Dans trois terminals différents exécuter le porgramme `barriere` avec la commade `./barriere`. Vous allez constater que les deux premières sont bloquer jusqu'à l'arriver du toisième

4. Enjoy !
