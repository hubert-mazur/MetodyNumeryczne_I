LANG_EXT=cpp
LAB_NUMB=0
BACKUP_VER=0
ifeq ($(LANG_EXT),cpp)
CXX=g++
else
CXX=gcc
endif

OUTPUT="Lab_$(LAB_NUMB)."
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
	@rm *.o
	@echo "cleared!"
run: 
	@./$(OUTPUT)
check:
	@valgrind ./$(OUTPUT)
backup: 
	@tar -czf backup_$(LANG_EXT)_v_$(BACKUP_VER)_.tar.gz *.h *.$(LANG_EXT) Makefile
	@echo "backup created!"
pack:
	@touch info.txt
	@(echo "Archive created by: ")> info.txt
	@(whoami >> info.txt)
	@(echo "at: " )>>info.txt
	@(date >> info.txt)
	@mkdir Lab_$(LAB_NUMB)
	@cp *.$(LANG_EXT) *.h Makefile info.txt Lab_$(LAB_NUMB)
	@tar -czf lab_$(LAB_NUMB).tar.gz  Lab_$(LAB_NUMB)
	@echo "pack created!"
	@rm info.txt
	@rm -r Labq_$(LAB_NUMB)

.PHONY: clean all check backup pack run
-include $(DEP)
