
#   Date:       	17-04-2020
#   Auteur:    		Nathan Ramsay-Vejlens
#   Nom fichier:	Makefile
#	Description:	Makefile pour faciliter la compilation
#					de différents sous-dossier.


# Le seigneur des Makefile
# Un Makefile pour les gouverner tous
# Pour ajouter d'autres dossier au répertoire, ajouter
# SUBDIR_3 = 'chemin relatif vers un dossier'
# ajouter la variable à SUDIRS ainsi qu'au .PHONY.
# Finalement, copier les 2 premières lignes du clean
# en modifiant afin d'appeller SUBDIR_3.


SUBDIR_1 = tp/tp7/codeCommun/lib_c 
SUBDIR_2 = projet/executable

SUBDIRS = $(SUBDIR_1) $(SUBDIR_2) 


# Make permet de générer la librairie utiliser avant de générer l'exécutable
all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean: 
	cd $(SUBDIR_1) 
	$(MAKE) clean -C $(SUBDIR_1)
	cd $(SUBDIR_2) 
	$(MAKE) clean -C $(SUBDIR_2)

.PHONY: all clean $(SUBDIRS) $(SUBDIR_1) $(SUBDIR_2)