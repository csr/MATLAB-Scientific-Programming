# This may not work on your machine. Please use the following link to find the settings
# that are right for your machine:

source /opt/intel/compilers_and_libraries_2019.5.281/mac/mkl/bin/mklvars.sh intel64
gcc-9 -DMKL_ILP64 -m64 -I${MKLROOT}/include -c template.c
gcc-9 -L${MKLROOT}/lib -lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm -ldl template.o -o template
./template