# Question 2 (Utilisation de `SEM_UNDO`)
## Enoncé

> Qu'est ce qui se passera si on envoie un signal kill a un des processus client pendant que la voiture est en tournée (essayez en ligne de commande: kill -9 pid). 
> Est ce qu'on peut régler ce problème en utilisant le flag SEM_UNDO (avec le P).
> Expliquez le principe de ce flag dans ce cas précis.

## Note 
L'implementaion de cette question n'est rien que la première avec `flag = SEM_UNDO` dans la stucture de l'operation `P`.

## Réponse
l’envoie un signal kill a un des processus client pendant que la voiture
est en tournée (commande: ` kill -9 pid`) bloque le processuss voiture
et tout autres processus clients dans le systems. le blockage est dû au
vaiable `nbDebarques` qui ne sera jamais égales à `P` et donc le
processus voiture se block dans l’instruction `P(semid, semTousDehors)`
et les processus clients se block dans l’instruction
`P(semid, semEmbarquement)`.

le flag `SEM_UNDO` permet au processus de libérer les sémaphores dans le
quelle il a l’acces avant sa terminision (remetre en cause les
différentes modifications sur les différentes sémaphores) en utilisant
une variable special `semadj` qui est définie pour chaque processus et
pour chaque semaphore et qui sauvgarde la somme de toutes les operations
effectuer par chaque processus sur chaque sémaphore.

Avec l’utlisation de ce flag dans les opérations des sémaphores `P` et
`V` le problème ne sera pas réglé puisque il été engendré par la valeur
du variable `nbDebarques` non pas par des valuers de sémaphores.

On peut réglé le problème si on utilise un sémaphore `semDedans` qui
sera incréménté a chaque embarquement d’un processus et décrementé à
chaque débarquement, comme ça si on tue un processus qui a monté et qui
n’a pas encore decendu (c’est la cause du problème précedent) la valeur
du sémaphore `semDedans` va décrementer en specifiant le flag
`SEM_UNDO`, et donc le processus voiture ne va pas bloquer puisque le
nombre des clients dans la voiture

**Détail sur `SEM_UNDO`**

-   Si la valeur du sémaphore est modifié par `SETVALL` ou `SETALL` la
    valeur du variable special `semadj` est reinitialisé. On doit pensé
    à utilisé les flags du système `CLONE_SYSTEMV` dans ce cas.\

-   l’OS linux applique la stratégie **décrementer la valeur tant que
    possible** lors du remetre en cause des operations effectuer par un
    processus sur un sémaphore (effet du flag `SEM_UNDO`).


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
