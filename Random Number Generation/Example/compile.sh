source /opt/intel/compilers_and_libraries_2019.5.281/mac/mkl/bin/mklvars.sh intel64
gcc-9 -fopenmp -m64 -I${MKLROOT}/include -c template.c
gcc-9 -L${MKLROOT}/lib -Wl,--no-as-needed -lmkl_intel_lp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl template.o -o template
./template