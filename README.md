#    PIPE EXERCICE1:
## Enoncé :
> on récrit le programme et on l'exécute , remarque :

**Question 01 :**

> Que se passera-t-il si le processus pere ne ferme pas le descripteur d'ecriture apres avoir fini d'ecrire?

**Réponse :**

le processus fils n'exécute pas l'instruction  `printf("Processus fils-FIN \n");`
car la condition de la boucle `read(p[0],buf, 20)>0` reste toujours vérifier

**Question 02 :**

> Pourquoi il faut toujours fermer les descripteurs qu'un processus n'utilise pas?

**Réponse :**

Car le processus fils est encore en attente pour récupérer les buf envoyé par le processus pere
vu que le processus pere n'a pas fermé le descripteur -> le processus qui reçoit les message attends
la fermeture du déscripteur d'ecriture pour  fini son travail
