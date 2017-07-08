source $HOME/programs/intel/compilers_and_libraries/linux/bin/compilervars.sh intel64
source $HOME/programs/intel/impi/2017.3.196/bin64/mpivars.sh

#source $HOME/programs/intel/ipp/bin/ippvars.sh intel64
if [[ $1 = "debug" ]]; then
#    make -f makefile-gcc -j8 INFO=true CPPSCI_DEBUG=true rome_res test
#    make -f makefile-gcc -j8 CPPSCI_DEBUG=true rome_res test
    make -j8 CPPSCI_DEBUG=true
else
#    make -f makefile-gcc -j8 rome_res test
    make -j8
fi



