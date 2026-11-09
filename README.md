# customBLAS

my own mini implementation of the BLAS library in C++ 23 to train a custom CNN, as part of the 
book "neuralnetworksanddeeplearning" by Michael Nielsen.

the library consists of Vector and Matrix implementation using the std::vector
C++ library, and is directly inherited of its properties.

the BLAS library fully supports normalization and other standard linalg methods
and is strictly bound to float datatype.

## structure
```
|
├── include
│   ├── blas_output.hpp
│   ├── Matrix.hpp
│   └── Vector.hpp
├── Makefile
└── src
    ├── main.cpp
    ├── Matrix.cpp
    └── Vector.cpp
```

note: build/ and bin/ are purposefull not included

## Use
clone the repository
```
git clone <repolink>
```
modify the src/main.cpp file to your liking

run 'make'
```
make
```

## TODO
[] Activation functions
