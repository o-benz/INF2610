all:
	gcc -c GestionMemoire.c -o GestionMemoire.o
	gcc GestionMemoire.o ./libs/evaluateur.o -o answer
	rm GestionMemoire.o

handin:
	mkdir handin
	cp -r GestionMemoire.c handin/
	tar -czvf handin.tar.gz handin
	rm -rf handin

clean:
	rm -f handin.tar.gz
