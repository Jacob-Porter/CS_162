COMPILER = g++ -g
EXE_FILE = run

all: $(EXE_FILE)

$(EXE_FILE): catalog.o catalog.h run_catalog.cpp
	$(COMPILER) catalog.o run_catalog.cpp -o $(EXE_FILE)

catalog.o: catalog.h catalog.cpp
	$(COMPILER) -c catalog.cpp

clean:
	rm -f *.o $(EXE_FILE)
