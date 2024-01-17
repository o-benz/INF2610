all:
	gcc -O0 -std=gnu11 -Werror -Wall -Wno-unused-result -Wno-unused-variable -o lab  lab.c

handin:
	mkdir handin
	cp lab.c handin/
	tar -czvf handin.tar.gz handin
	rm -rf handin

clean:
	rm -f lab
	rm -f handin.tar.gz
