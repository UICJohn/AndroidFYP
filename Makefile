work2 : work2.o 
	cc -o work2 work2.o 
work2.o : work2.c work2.h
	cc -c work2.c 
clean: 
	echo "[CLEAN]"
	rm -f *.o work2

