all:
	gcc -O0 -std=gnu11 -Werror -Wall -Wno-unused-result -Wno-unused-variable -o processlab ./libprocesslab/libprocesslab.c  part1.c part2.c ./libprocesslab/processlab.c -lrt 

mac:
	gcc -O0 -std=gnu11 -Werror -Wall -Wno-unused-result -Wno-unused-variable -o processlab ./libprocesslab/libprocesslab.c  part1.c part2.c ./libprocesslab/processlab.c

handin:
	mkdir handin
	cp part1.c handin/
	cp part2.c handin/
	cp output.txt handin/
	tar -czvf handin.tar.gz handin
	rm -rf handin

clean:
	rm -f handin.tar.gz
