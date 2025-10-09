# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG -O0
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
INC = -I../pomiar_czasu

# biblioteki
LIB = -L../pomiar_czasu -lpomiar_czasu -lm
# -------------------------------------------------------------
# zaleznosci i komendy
fork: fork.o 
	$(LOADER) $(OPT) fork.o -o fork $(LIB)

# jak uzyskac plik fork.o ?
fork.o: fork.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) fork.c $(INC) 

# -------------------------------------------------------------
# zaleznosci i komendy
clone: clone.o 
	$(LOADER) $(OPT) clone.o -o clone $(LIB)

# jak uzyskac plik clone.o ?
clone.o: clone.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) clone.c $(INC) 
# -------------------------------------------------------------
# zaleznosci i komendy
zad5: zad5.o 
	$(LOADER) $(OPT) zad5.o -o zad5 $(LIB)

# jak uzyskac plik zad5.o ?
zad5.o: zad5.c ../pomiar_czasu/pomiar_czasu.h
	$(CCOMP) -c $(OPT) zad5.c $(INC) 

clean:
	rm -f *.o fork clone zad5
