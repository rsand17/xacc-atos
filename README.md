# xacc-atos
XACC plugins for interacting with the ATOS QLM simulator

Installation
------------
Connect to the Atos Quantum Learning Machine via ssh into your home directory.
With the XACC framework installed on the QLM already, xacc-atos can be installed in the following ways;

First run the following
```bash
$ git clone https://github.com/rsand17/xacc-atos.git
$ mkdir build && cd build
```
In the future the repository to clone from will change to https://github.com/ORNL-QCI/xacc-atos.git

Next choose to run CMake and Make without Python support
```bash
$ cmake .. -DXACC_DIR=$HOME/.xacc (or wherever you installed XACC)
$ make install 
```
or with Python support
```bash
$ cmake .. -DXACC_DIR=$(python -m pyxacc -L)
$ make install
```

Utilisation
-----------
Before trying to run XACC kernels, it is neccessary to do the following
```bash
$ module load qat/dev
$ qprocd --qproc-handlers qat.linalg &
$ qpud &
```

