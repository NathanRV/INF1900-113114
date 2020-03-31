Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

Grille de correction des programmes:

Identification:
  Travail    : Mise en commun du code et formation de librairies
  Section #  : 3
  Équipe #   : 113114
  Correcteur : Claudia Onorato

Code:
– La qualités et le choix de vos portions de code choisies   (3/5)
– La qualités de vos modifications aux Makefiles             (3.5/5)

Le rapport:
– Explications cohérentes par rapport au code retenu
  pour former la librairie                                   (2/2)
– Explications cohérentes par rapport aux Makefiles modifiés (2/2)
– Explications claires avec un bon niveau de détails         (2/2)
– Bon français                                               (1/1)

Généralités:
– Bonne soumission de l'ensemble du code (compilation sans
  erreurs, …) et du rapport selon le format demandé          (3/3)

Total: 16.5/20

Commentaires du correcteur:

La qualités et le choix de vos portions de code choisies
- Codez en une seule langue (ex. paramètre `period` dans une fonction `attenuerDEL`).
- `controlerLumiereSelonIntensite` comporte une boucle infinie. Quand on appelle une fonction d'une librairie, à moins que ça soit clairement indiqué, on s'attend à ce que la fonction retourne après un certain moment.
- Attention aux indentations dans `controleMoteur.cpp`!
- Le paramètre `direction` de `dirigerRoues` peut avoir un impact sur d'autres périphériques (ex. DEL) s'ils sont également connectés au portD. Vaudrait mieux avoir reçu un booléen, par exemple, pour chaque roue.
- Vous avez oubliez d'éteindre la DEL après le temps de délai dans `couleurVert` et `couleurRouge`.

La qualités de vos modifications aux Makefiles
- Certaines règles et variables sont inutiles dans le Makefile de la librairie (ex. `install` et `AVRDUDE`).
- Certaines variables sont dédoublées entre les deux Makefiles, et auraient pu être regroupées dans un makefile commun.

# Basé sur le commit suivant
```
commit 419c08800cdc4f61030723dc5645759278347c11
Merge: 1242293 8ddc84c
Author: Nathan Ramsay-Vejlens <nathan.ramsay-vejlens@polymtl.ca>
Date:   Mon Mar 9 16:31:44 2020 -0400

    fin merge main modifie et make par defaut
```

# Fichiers indésirables
```
branche-113/tp/tp5/pb2/Makefile~
branche-113/tp/tp5/pb3/Makefile~
branche-113/tp/tp5/pb3/probleme3.d
branche-113/tp/tp5/pb3/probleme3.hex
branche-113/tp/tp5/pb3/probleme3.o
branche-113/tp/tp5/pb3/probleme3.out
branche-113/tp/tp5/pb3/probleme3.out.map
```

# Sortie de make dans les sous-répertoires
```
======================= Sortie de make dans tp/tp7/lib =============================
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c antirebond.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c can.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c capteurs.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c controleDEL.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c controleMoteur.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c delay.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c initialisation.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c interactionUART.cpp
avr-gcc -I. -MMD  -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c memoire_24.cpp
memoire_24.cpp:30:3: warning: #warning "F_CPU pas defini pour 'memoire_24.cpp'" [-Wcpp]
   30 | # warning "F_CPU pas defini pour 'memoire_24.cpp'"
      |   ^~~~~~~
avr-ar -crs -o lib_c.a  antirebond.o can.o capteurs.o controleDEL.o controleMoteur.o delay.o initialisation.o interactionUART.o memoire_24.o 
Librairie créée

======================= Sortie de make dans tp/tp7/exec =============================
avr-gcc -I. -MMD -I ../lib_c -g -mmcu=atmega324pa -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c main.cpp
avr-gcc -Wl,-Map,main.out.map -mmcu=atmega324pa -static -o main.out  main.o \
        -lm -L ../lib_c -l_c

```