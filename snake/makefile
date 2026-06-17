

snake : main.o jeu.o plateau.o serpent.o fruit.o scores.o menu.o sauvegarde.o
	gcc -o snake main.o jeu.o plateau.o serpent.o fruit.o scores.o menu.o sauvegarde.o `pkg-config --libs MLV` 

#   -Wall -Wextra : active les warnings
#   -ansi -pedantic : conformité C89/C ANSI
#   -g : informations pour le débogage
#    pkg-config --cflags MLV : options de compilation pour MLV
#   -c : compile sans créer d'exécutable

main.o : main.c jeu.h plateau.h serpent.h fruit.h scores.h menu.h sauvegarde.h
	gcc -Wall -Wextra -ansi -pedantic -g `pkg-config --cflags MLV` -c main.c

jeu.o : jeu.c jeu.h plateau.h serpent.h fruit.h
	gcc -Wall -Wextra -ansi -pedantic -g `pkg-config --cflags MLV` -c jeu.c

plateau.o : plateau.c plateau.h
	gcc -Wall -Wextra -ansi -pedantic -g `pkg-config --cflags MLV` -c plateau.c

serpent.o : serpent.c serpent.h plateau.h
	gcc -Wall -Wextra -ansi -pedantic -g `pkg-config --cflags MLV` -c serpent.c

fruit.o : fruit.c fruit.h plateau.h
	gcc -Wall -Wextra -ansi -pedantic -g `pkg-config --cflags MLV` -c fruit.c

scores.o : scores.c scores.h
	gcc -Wall -Wextra -ansi -pedantic -g `pkg-config --cflags MLV` -c scores.c

menu.o : menu.c menu.h
	gcc -Wall -Wextra -ansi -pedantic -g `pkg-config --cflags MLV` -c menu.c

sauvegarde.o : sauvegarde.c sauvegarde.h
	gcc -Wall -Wextra -ansi -pedantic -g `pkg-config --cflags MLV` -c sauvegarde.c

#nettoyage
clean :
	rm -f *.o snake
