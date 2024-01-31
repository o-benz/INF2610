all:
	nasm -f elf64 minisys.asm && ld -s -o minisys minisys.o &&  rm -f minisys.o && gcc -o part1 ./part1.c && gcc -o part2 part2.c

minisys: minisys.asm
	nasm -f elf64 minisys.asm && ld -s -o minisys minisys.o
	rm -f minisys.o

part1: part1.c
	gcc part1.c -o part1

part2: part2.c
	gcc part2.c -o part2

handin:
	mkdir handin
	cp part1.c handin/
	cp part2.c handin/
	cp minisys.asm handin/
	cp output1.txt handin/
	cp output2.txt handin/
	cp output3.txt handin/
	cp output4.txt handin/
	tar -czvf handin.tar.gz handin
	rm -rf handin

clean:
	rm -f handin.tar.gz
