TESTFILE = *.test
GENERATES = *.so

wrapper: wrap.c
	gcc -shared -fPIC wrap.c -ldl -o wrap.so 

test:
	touch fileFIX.test
	touch file.test
	rm *.test
	touch file.test
	LD_PRELOAD=`pwd`/wrap.so rm file.test
	touch fileFIX.txt
	LD_PRELOAD=`pwd`/wrap.so rm fileFIX.test
	rm fileFIX.txt

cleantest:
	rm -f $(TESTFILE)
cleangen: 
	rm -f $(GENERATES)
 
clean: cleantest cleangen
