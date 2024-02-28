all:
	gcc -O0 -std=gnu11 -Werror -Wall -Wno-unused-result -Wno-unused-variable -o CommLab  CommLab.c

handin:
	mkdir handin
	cp TubesNommes.c TubesAnonymes.c In.txt handin/
	tar -czvf handin.tar.gz handin
	rm -rf handin

clean:
	rm -f CommLab
	rm -f handin.tar.gz
