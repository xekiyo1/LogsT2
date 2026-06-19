BTree=src/arbolitos/BinaryTree.h src/arbolitos/BinaryTree.cpp
AVLFiles=src/arbolitos/AVL.h src/arbolitos/AVL.cpp
SplayFiles=src/arbolitos/SplayTree.h src/arbolitos/SplayTree.cpp
RandomFiles=src/RandomGen/RandomArray.h src/RandomGen/RandomArray.cpp

Tester=src/main/experimentos.cpp
Teoremas=src/main/experimentosTeoremas.cpp
Bonus=src/main/experimentosBonus.cpp


ALL-TREES=$(BTree) $(SplayFiles) $(AVLFiles)
UTIlS= $(RandomFiles)

FILES-CONSTRUCT=$(Tester) $(ALL-TREES) $(UTIlS)
FILES-CONSTRUCT2=$(Teoremas) $(ALL-TREES) $(UTIlS) 
FILES-BONUS=$(Bonus) $(ALL-TREES) $(UTIlS)
FLAGS-CONSTRUCT=-O3 -o "$(OUT)"

OUT=a.out

exec:
	./$(OUT)

compile:
	g++ $(FLAGS-CONSTRUCT) $(FILES-CONSTRUCT)
compile-teorema:
	g++ $(FLAGS-CONSTRUCT) $(FILES-CONSTRUCT2)
compile-bonus:
	g++ $(FLAGS-CONSTRUCT) $(FILES-BONUS)
run:
	make compile
	make exec
	make compile-teorema
	make exec
run-bonus:
	make compile-bonus
	make exec
run-all:
	make compile
	make exec
	make compile-teorema
	make exec	
	make compile-bonus
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
	g++ $(FLAGS-CONSTRUCT) src/main/testAVL.cpp $(BTree) $(AVLFiles)
	make exec