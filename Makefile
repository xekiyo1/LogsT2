BTree=src/arbolitos/BinaryTree.h src/arbolitos/BinaryTree.cpp
AVLFiles=src/arbolitos/AVL.h src/arbolitos/AVL.cpp
SplayFiles=src/arbolitos/SplayTree.h src/arbolitos/SplayTree.cpp
RandomFiles=src/RandomGen/RandomArray.h src/RandomGen/RandomArray.cpp

Tester=src/main/experimentos.cpp

Timer=src/util/calcTime/calcTime.cpp

ALL-TREES=$(BTree) $(SplayFiles) #$(AVLFiles)
UTIlS= $(RandomFiles)

FILES-CONSTRUCT=$(Tester) $(ALL-TREES) $(UTIlS)
FLAGS-CONSTRUCT=-O3 -o "$(OUT)"

OUT=a.out

exec:
	./$(OUT)

compile:
	g++ $(FLAGS-CONSTRUCT) $(FILES-CONSTRUCT)
run:
	make compile
	make exec

clean:
	find . -type f -name "*.bin" ! -path "*/data/*" -delete
	find -type f -name "*.out" -delete
clean-logs:
	find -type f -name "*.log | *.csv"
allow-cli:
	chmod +rx ./sh/cli.sh
	chmod +rxw ./sh/logger.sh

init:
	install -Dv /dev/null bin/commands/__init_placeholder__.out
	install -Dv /dev/null bin/trees/__init_placeholder__.out
	make clean
	make allow-cli

test:
	g++ $(FLAGS-CONSTRUCT) src/main/test.cpp $(BTree) $(SplayFiles)
	make exec