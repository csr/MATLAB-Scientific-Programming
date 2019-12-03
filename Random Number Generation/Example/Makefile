main: main.cpp
	gcc-9 -Wextra -DMKL_ILP64 -m64 -I${MKLROOT}/include -c main.cpp -o main.o
	gcc-9 -fopenmp -L${MKLROOT}/lib -Wl,-rpath,${MKLROOT}/lib -lmkl_intel_ilp64 -lmkl_tbb_thread -lmkl_core -ltbb -lc++ -lpthread -lm -ldl -o main main.o

PHONY: clean

clean:
	rm *.o main
