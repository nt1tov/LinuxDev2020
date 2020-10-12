GENERATES = prog README prog-a prog-so 
TRASH = *.o *~ o.* *.a out-* *.so out?
LOGGER = log_file
CFLAGS = -Wall -fPIC



all: README prog prog-a prog-so

test: 
	make logclean 
	make all
	./prog >> out0
	./prog 0  >> out1	
	./prog 0 1 2 >> out3
	./prog-a >> out-a0
	./prog-a 0  >> out-a1	
	./prog-a 0 1 2 >> out-a3
	LD_LIBRARY_PATH=$(PWD) ./prog-so >> out-so0
	LD_LIBRARY_PATH=$(PWD) ./prog-so 0  >> out-so1	
	LD_LIBRARY_PATH=$(PWD) ./prog-so 0 1 2 >> out-so3
	cmp out0 out-a0 && echo "Correct!Files prog prog-a w/o input are equal!" >> $(LOGGER) || echo "Error!Diff files w/o input prog prog-a!" >>$(LOGGER)
	cmp out0 out-so0 && echo "Correct!Files prog prog-so w/o input  are equal!" >> $(LOGGER) || echo "Error!Diff files w/o input prog prog-so!" >>$(LOGGER)	
	cmp out1 out-a1 && echo "Correct!Files input 1 par prog prog-a are equal!" >> $(LOGGER) || echo "Error!Diff files input 1 par  prog prog-a!" >>$(LOGGER)
	cmp out1 out-so1 && echo "Correct!Files inpit 1 par prog prog-so are equal!" >> $(LOGGER) || echo "Error!Diff files input 1 par prog prog-so!" >>$(LOGGER)
	cmp out3 out-a3 && echo "Correct!Files input 3 par prog prog-so are equal!" >> $(LOGGER) || echo "Error!Diff files input 3 par prog prog-so!" >>$(LOGGER)
	cmp out3 out-so3 && echo "Correct!Files input 3 par prog prog-so are equal!" >> $(LOGGER) || echo "Error!Diff files input 3 par prog prog-so!" >>$(LOGGER)
	cmp out-a0 out-so0 && echo "Correct!Files w/0 input prog-a prog-so are equal!" >> $(LOGGER) || echo "Error!Diff files w/o input  prog-a prog-so!" >>$(LOGGER)
	cmp out-a1 out-so1 && echo "Correct!Files input 1 par prog-a prog-so are equal!" >> $(LOGGER) || echo "Error!Diff files input 1 par prog-a prog-so!" >>$(LOGGER)
	cmp out-a3 out-so3 && echo "Correct!Files input 3 par prog-a prog-so are equal!" >> $(LOGGER) || echo "Error!Diff files input 3 par prog-a prog-so!" >>$(LOGGER)
	make genclean
		
prog: const.o fun.o prog.o

prog-a: prog.o libstatic.a
	cc -L. prog.o -lstatic -o prog-a

	
prog-so: libdyn.so prog.o
	cc -L. prog.o -ldyn -o prog-so


libstatic.a: const.o fun.o
	ar -rcs $@ $^

libdyn.so: const.o fun.o 
	cc -shared $^ -o $@


fun.o: outlib.h

README: prog
	./$< 2> $@

clean:
	rm -f $(TRASH)

genclean: clean
	rm -rf $(GENERATES)

logclean: genclean
	rm -f ${LOGGER}
