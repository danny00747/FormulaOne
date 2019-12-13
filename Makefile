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
		@echo $(SRC) $(LIBS) | tr ' ' '\n' | \
    	entr -s 'notify-send -t 5000 "Compiling source files" && \
            $(MAKE) --no-print-directory && \
             notify-send -t 5000 "Done" || \
             notify-send -t 5000 "Failed"'

clean:
	rm $(EXE)


