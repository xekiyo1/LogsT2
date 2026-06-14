BTree=src/arbolitos/BinaryTree.h src/arbolitos/BinaryTree.cpp
AVLFiles=src/arbolitos/AVL.h src/arbolitos/AVL.cpp
SplayFiles=src/arbolitos/SplayTree.h src/arbolitos/SplayTree.cpp

Tester=src/main/experimentos.cpp

Timer=src/util/calcTime/calcTime.cpp

ALL-TREES=$(BTree) $(AVLFiles) $(SplayFiles)
FILES-CONSTRUCT=$(Tester) $(ALL-TREES)
FLAGS-CONSTRUCT=-O3 -o "$(OUT)"

OUT=a.out

exec:
	./$(OUT)

compile:
	g++ $(FLAGS-CONSTRUCT) $(ALL-TREES)
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