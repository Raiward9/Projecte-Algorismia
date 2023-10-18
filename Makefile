# Especifica el compilador que deseas utilizar
CXX = g++

# Opciones del compilador
CXXFLAGS = -Wall -O2 -std=c++11

# Nombres de los archivos de origen y el ejecutable
SRC = experiments.cpp
HEADERS = BinarySearchTree.h BinarySearchTreeGenerator2.h
OUT = experiments

# Regla para compilar el programa
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Regla para limpiar los archivos generados
clean:
	rm -f $(OUT)
