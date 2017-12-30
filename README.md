# Question 3 (Limite du nombre de tounrées)
## Enoncé

> On souhaite maintenant limiter le nombre de tournées pour chaque client a un nombre déterminé par le processus voiture (et qu'il peut changer lui même bien sur). Modifier le code des processus client pour prendre en considération cette limitation (la condition de la boucle while(true)) en respectant les contraintes suivantes : 
> - Le processus voiture lui doit rester toujours en vie en attente de nouveau clients qui arrivent (des processus clients qu'on lance a partir d'un autre terminal par exemple).
> - Réaliser un teste de cette situation. 

## Réponse
### Implementaion

Pour l’implémentation du limite des trounée pour chaque clients, on doit
sauvegarder le nombre du tournée pour chaque clients. Pour cela on a
définie les variables `int nbClients`, `int clients[]` et `int tours[]`
dans la structure `state`. `nbClients` contients le nombre de clients
dans le systèmes. `clients` contients les **pids** des clients dans le
système. `tours` contients le nombre de tournées pour chaque **pid**
dans `clients`.

on définie aussi les variables `MAX_TOURS` qui peut être mise à jourer
par le processus voiture et `MAX_CLIENTS` qui contient le nombre maximum
du clients qui peut être enregister dans les tableaux précedents.

Une sémahpore `mutex3` pour protéger les variables `int nbClients`,
`int clients[]` et `int tours[]`

**Note :** une milleur solution peut etre implementer en utilisant les
structure dynamiques.

L’idée est que chaque nouveau clients (son **pid**) est sauvegarder dans
la case numéro `nbClients` du tableau **clients** et son nombre de
tournée associer est sauvegardé dans la case numéro `nbClients` du
tableau `tours`.

A l’arrivé du clients il fait appele à la foction `inscription` qui lui
enregister dans le tableau `clients` et initialise son nombre de tours à
zero.

Pour pouvoir fait une tournée (la condition d’entrée) il fait appele à
la fonction `peutTourner` qui retourne `vrai` que si le nombre de tours
du clients est inférieur au nombre maximale de trournée

Chaque fin de tournées le processus cliens fait appele à la fonction
`finTour` qui incrémente son nombre de tours.


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
