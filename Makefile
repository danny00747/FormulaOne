SRC_DIR=src
SRC=$(wildcard $(SRC_DIR)/*.c)
LIBS=$(wildcard lib/*.c)
CFLAGS=-Wall -Wextra -lpthread -lrt -std=gnu99
EXE=prog

.PHONY: compile format watch clean

compile: $(EXE)

$(EXE):	$(SRC) $(LIBS)
	@$(CC) $^ $(CFLAGS) -o $@
	@echo
	@echo "Build finished."

format:
	clang-format -i $(SRC)

watch:
	echo $(SRC) | entr -s 'make --no-print-directory compile' 

clean:
	rm $(EXE)


