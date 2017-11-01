default:
	g++ ASM.cpp ASMParser.cpp Instruction.cpp Opcode.cpp RegisterTable.cpp -o run

w:
	g++ -Wall ASM.cpp ASMParser.cpp Instruction.cpp Opcode.cpp RegisterTable.cpp -o run

o:
	vim -p ASMParser.cpp ASMParser.h Instruction.cpp Instruction.h Opcode.cpp Opcode.h
v:
	valgrind -v ./run inst.asm

r:
	./run inst.asm

gdb:
	gdb ./run
	r inst.mach inst.asm

clean:
	rm run
	rm a.out
