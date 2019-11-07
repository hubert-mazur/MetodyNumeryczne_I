LANG_EXT=cpp
BACKUP_VER=0
ifeq ($(LANG_EXT),cpp)
CXX=g++
else
CXX=gcc
endif

OUTPUT="exec"
CXX=g++
CXXFLAGS=-Wall -g

#Dependency for the ouotput file
DEP_FLAGS=-MMD
DEP_FLAGS+=-MP

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
DEP=${SRC:.cpp=.d}

#Add dependency generation to the compiler options
CXXFLAGS+=$(DEP_FLAGS)


all: $(OUTPUT)
	@echo "Builded! name: $(OUTPUT)"

$(OUTPUT): $(OBJ)
	@$(CXX) $(OBJ) -o $@
	
%.o: %.cpp
	@$(CXX) -c $(CXXFLAGS) $<

clean:
	@rm *.o *.d *.dat *.jpg ${OUTPUT}
	@echo "cleared!"
run: 
	@./$(OUTPUT)
memcheck:
	@valgrind ./$(OUTPUT)

pack:
	@zip IMN_Mazur_Hubert_lab_${1}.zip *.cpp *.h *.dat *.jpg gnuplot.sh Makefile
draw:
	@gnuplot gnuplot.sh

.PHONY: clean all check pack run draw
-include $(DEP)
