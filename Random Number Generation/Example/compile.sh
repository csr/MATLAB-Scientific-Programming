# This may not work on your machine. Please use the following link to find the settings
# that are right for your machine:
# https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor/

source /opt/intel/bin/compilervars.sh intel64
gcc-9 -Wall -DMKL_ILP64 -m64 -I${MKLROOT}/include -c main.cpp -o main.o
gcc-9 -L${MKLROOT}/lib -Wl,-rpath,${MKLROOT}/lib -lmkl_intel_ilp64 -lmkl_tbb_thread -lmkl_core -ltbb -lc++ -lpthread -lm -ldl -o main main.o -fopenmp
./main