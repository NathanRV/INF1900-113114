# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Machines à états finis logicielles
+ Section #  : 3
+ Équipe #   : 114
+ Correcteur : Claudia Onorato

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |            |
| __Résultat partiel__                         | __(1.5/1.5)__ |

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (0.5/0.5)     |
| Noms de variables décrivent l'intention      | (0.5/0.5)     |
| Noms de fonctions décrivent l'intention      | (0.5/0.5)     |
| __Résultat partiel__                         | __(1.5/1.5)__ |

## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme ou procédure 
 + peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(0.5/1.0)__ |


## Indentation   

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Indentation structurée                       |            |
| Indentation uniforme dans le programme       |            |
| __Résultat partiel__                         | __(1.0/1.0)__ |


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| __Résultat partiel__                         | __(1.0/1.0)__ |


## Bonne application des concepts de systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation des registres appropriée         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisés    |            |
| etc                                          |            |
| __Résultat partiel__                         | __(4.0/4.0)__ |

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (1.5/1.5)     |
| Absence de fichiers inutiles                 | (1.5/1.5)     |
| __Résultat partiel__                         | __(3.0/3.0)__ |


## Compilation    

| Pénalité par erreur                          | -2.0       |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation |            |
| Absence de messages d'attention (*warning*)  |            |
| __Résultat partiel__                         | __(2.0/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (2.5/2.5)     |
| Cas limites observables                      | (2.5/2.5)     |
| __Résultat partiel__                         | __(5.0/5.0)__ |

# Résultat

__Total des points: 19.5/20__

# Commentaires du correcteur:

Wow! Bon travail!

Mon seul commentaire est que certains commentaires n'aident pas à la compréhension du code (ex. `//switches according to state`). Si vous voyez que votre code est suffisament clair, vous n'avez pas à mettre des commentaires.

# Basé sur le commit suivant
```
commit 8a5f225ac2b559a4d7741197acc4b7d31fc62a4b
Author: David Saikali <dasaic@l3818-10.info.polymtl.ca>
Date:   Thu Jan 30 16:41:29 2020 -0500

    Fin du tp3
```

# Fichiers indésirables
```

```

# Sortie de make dans les sous-répertoires
```
======================= Sortie de make dans tp/tp2/pb1 =============================
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c p1.cpp
avr-gcc -Wl,-Map,pb1.out.map -mmcu=atmega324pa -o pb1.out  p1.o \
	-lm 

======================= Sortie de make dans tp/tp2/pb2 =============================
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c p2.cpp
avr-gcc -Wl,-Map,pb2.out.map -mmcu=atmega324pa -o pb2.out  p2.o \
	-lm 


```