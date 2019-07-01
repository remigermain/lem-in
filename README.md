# lem_in :heavy_check_mark:

Comment ça marche ?

•Votre programme va recevoir sur l’entrée standard la description de la fourmilière sous la forme suivante 
```
nombre_de_fourmis
les_salles
les_tubes
```

•La fourmilière est décrite par ses liaisons 

```
##start
1 23 3
2 16 7
#commentaire
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
##end
0 9 5
0-4
0-6
1-3
4-3
5-2
3-5
#autre commentaire
4-2
2-1
7-6
7-2
7-4
#C'est la fin
6-5
#autre commentaire
```

# Ce qui représente :

```
           _______________
          /               \
  ______[5]----[3]----[1]  |
 /              |     /    |
[6]-----[0]----[4]   /     |
 \    _________/ |  /      |
  \ /           [2]/______/
  [7]___________/
```

On a donc 2 parties :

◦La définition des salles sous la forme suivante :nom coord_x coord_y
◦La définition des tubes :nom1-nom2
◦Le tout entre-coupé de commentaires qui commencent par#

`Les noms des salles ne seront pas forcément des chiffres, ils neseront pas forcément dans l’ordre, et encore moins continus (onpourra trouver des salles aux noms zdfg, 256, qwerty, etc ...). Maisune salle ne commencera jamais par le caractère L ou le caractère #`
`Les coordonnées des salles seront toujours des nombres entiers`

•Les lignes commençant par un##sont des commandes modifiant les propriétés dela ligne significative qui vient juste après.

•Par exemple,##startindique l’entrée de la fourmilière et##endla sortie.

`Toute commande inconnue sera ignorée.`

•La première ligne non conforme ou vide entraîne la fin de l’acquisition de la four-milière et son traitement normal avec les données déjà acquises.

•S’il n’y a pas assez de donnée pour faire un traitement normal vous devrez sim-plement afficher ERROR

# e but de tout ca ?

•Le but du projet est de trouver le moyen le plus rapide de faire traverser la four-milière parnfourmis.

•Par moyen le plus rapide, nous entendons la solution avec le moins de lignes,respectant le format de sortie demandé ci-après.

•Évidemment, il y a quelques contraintes. Pour arriver le premier, il faut prendre lechemin le plus court (et pas forcément pour autant le plus simple), ne pas marchersur ses congénères, tout en évitant les embouteillages.

•Au début du jeu, toutes les fourmis sont sur la salle indiquée par la commande##start. Le but est de les amener sur la salle indiquée par la commande##endenprenant le moins de tours possible. Chaque salle peut contenir une seule fourmi àla fois (sauf##startet##endqui peuvent en contenir autant qu’il faut).

•On considère que les fourmis sont toutes dans la salle##startau démarrage.

•Vous n’afficherez à chaque tour que les fourmis qui ont bougé.

•À chaque tour vous pouvez déplacer chaque fourmi une seule fois et ce suivant untube (la salle réceptrice doit être libre).

•Vous devez sortir le résultat sur la sortie standard sous la forme suivante :

```
nombre_de_fourmis
les_salles
les_tubes
Lx-y Lz-w Lr-o ...
```

Oùx, z, rsont des numéros de fourmis (allant de 1 ànombre_de_fourmis) ety, w, odes noms de salles.

# Exemple

```
az@blackjack /tmp/lem-in $ ./lem-in < sujet1.map3
##start
0 1 0
##end
1 5 0
2 9 0
3 13 0
0-2
2-3
3-1

L1-2
L1-3 L2-2
L1-1 L2-3 L3-2
L2-1 L3-3
L3-1
zaz@blackjack /tmp/lem-in $
```

•Bien sûr votre algorithme doit rendre dans un délai raisonnable, même dans uncas à 4000 salles. 2 ou 3 secondes c’est très bien, 9 secondes c’est médiocre, 15secondes c’est beaucoup trop

`Ce sont des maps avec parfois plus de 10000 lignes, votre façon delire les données et de les écrire doit également être assez rapide.`

•Quant à savoir quel type d’opération les étudiants en magie pouvaient bien faireavec un tel ordinateur, tout ce qu’on en sait aujourd’hui, c’est que l’électricité c’estvachement plus fiable.