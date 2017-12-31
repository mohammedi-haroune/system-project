#    VERSION 2: 

dans cette version on va traiter le cas de  rafraichisse automatiquement a chaque modification
survenue sur les sémaphores du groupe et aussi si un utilisateur lance l'exécution avec un autre SEMID , il se rafaichisse 
les resources de ce SEMID chez tout les utilisateur 



**Dans ce cas on vas utiliser:
	1- le meme Groupe pour les semaphore 
	`ET`
	2- le meme Groupe pour la variable partager (`SEMID` qui se change aussi)



**Et pour cela : 
		on a ecrit 2 programme 
		1- **initSemaphoreHere** :  pour initialiser les semaphore du meme Groupe 
								en utiliser les memes chemins dans ce programme et le programme  'semStart' 
								pour qu'on manipule sur le meme groupe de semaphore 

		2- **semStart** : pour faire les test ( lancement de l'exécutable sur deux fenetres /Terminal1.Terminal2)
					  traitement: on va lancer le premier test sur le terminal'1' avec un semid (1)
					  resultat  : on aura l'affichage des resource de ce `SEMID` 
					  traitement: et puis on lance l'exécution avec semid (2) sur un autre terminal'2' 
					  resultat  : l'affichage des resources de semid (2) se fait sur le  terminal 1 et 2



					  les semaphore sont initialiser a 0 dans le programme `initSemaphoreHere`

					  alors si un utilisateur A  lance l'exécution du 'semStart'  il se bloque aprés
					  le premier affichage (met en veille) .
					  un utilisateur B vient et lance l'exécution --> la il va revéiller tout les 
					  utilisateurs qui sont en veille 
					  
					  Remarque :	en lisant les commentaire qui sont ecirtes sur le code du
					  				deux programmes pour bien comprendre leur fonctionnements

pour lancer l'exécution de ce qu'on a' expliqué se-dessu , suivre les etapes suivante : 




**  Les ETAPES : ** 

1. pour initialiser les semaphore utilisé , on exécuter les deux commandes sivante 

			cmd:
			>gcc initSemaphoreHere.c -o init 
			>./init

			>la, on a initialiser le semaphore qui a l'ID : MONITOR_ID  --> le meme semaphore va etre utliser pas 'semStart' ---Semaphore du meme Groupe 
				et on va utiliser la meme variable SEMID --W comme-t-il est expliquer se-dessus  

2. on prend un semid existant : en exécutant la commande suivante 

			>cmd :  
			>`>ipcs -s` 

			>les `SEMID` sont cité sur la colone 'semid'

3. pour lancer l'exécution de `semStart`: 

			>cmd1: 
			>`>gcc semStart -o start` 
			>`>./start semid1`

**puis** : 
			>cmd2: 
			>`>./start semid2` 





##   resultat :	

				>*******************************************************************
				>*sur `cmd1` : on aura l'affichage des resources de `SEMID1` Et `SEMID2` *
				>*sur `cmd2` : on aura l'affichage des resources de `SEMID2`			  *	 	
				>*******************************************************************

** Ps ** : 
		>`si` un autre utilisateur lance l'exécution avec autre semid 
		>`alors` --> il sera affiché sur cmd1 et cmd2 ,et ainsi de suite


##ENJOY!!