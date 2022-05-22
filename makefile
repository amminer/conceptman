CFLAGS=     -std=c++17 -g -Wall
VFLAGS=		--leak-check=full
SOURCES=	ConceptMgr.cpp RBT.cpp Concept.cpp SubConcept.cpp
EXE=     	main.out
CC=			g++

main:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE)

clean:
	rm $(EXE)

test:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE)
	./$(EXE)

prod:
	$(CC) -std==c++17 $(SOURCES) -o $(EXE)

memch:
	#if [ ! -f ./a.out ]; then
	#	$(CC) $(CFLAGS) $(SOURCES)fi
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXE)
	valgrind $(VFLAGS) $(EXE)
