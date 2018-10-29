# ode
Solve simple 2nd order ODEs

### prerequisites

* cmake  (probably **build-essential** as well)
* (optional) doxygen doxygen-latex graphviz
* (optional) python3.6-dev  ( to show plot of results )

#### Special thanks to

Check the latest version directly

https://github.com/lava/matplotlib-cpp


### compiling ...

```
git clone https://github.com/rcorbish/ode.git
cd ode
cmake 
make
```

if no python matplot required 

```
git clone https://github.com/rcorbish/ode.git
cd ode
cmake -D_NO_MATPLOT=1 .
make
```

### running

Without ```PYTHONPATH``` being set I kept getting the following
```
    terminate called after throwing an instance of 'std::runtime_error'
    what():  Error loading module matplotlib!
    Aborted (core dumped)
```
until I added this ``` export PYTHONPATH=${HOME}/anaconda3/lib/python3.6/site-packages ```

```./ode ```
or
``` ./run.sh ```





