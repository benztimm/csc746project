# KMP-Search-instruction

# Build instructions - general

After login to NERSC Permulter, 

    Clone the repo
    Go to dataset folder, run 
        ls -l 
    please check if 700mb.txt is in correct size or not. The correct size should be "733438928"

    If the file is a placeholder(not in correct size) you need to install the Git LFS
    simply run,

    git lfs install

    git lfs pull

    Note that each pull used up the bandwidth from my account, I purchased the additional data pack which gave us 50GB bandwidth to use. Still please be mindful when you're cloning the repo


Go to the clone repository. If the build folder already exists, then run this command

    rm -rf build

Then, create build folder and make file by:

    mkdir build  
    cd build  
    cmake ../  
    make

It is OK to do builds on the login node
All code should be executed on a CPU node.

# How to run code

## Allocate the CPU NODE in NERSC Permulter
simply run,

    salloc --nodes 1 --qos interactive --time 00:30:00 --constraint cpu --account=m3930
    
## For kmpsearch-basic, 

Simply run,

    srun kmpsearch-basic


## For kmpsearch-openmp,

First, change the omp thread by

    export OMP_NUM_THREADS=NUM_THREAD

Then, simply run

    srun kmpsearch-openmp
