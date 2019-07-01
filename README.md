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