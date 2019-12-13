SRC_DIR = ../src
C       = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(SRC_DIR)/*.h)
SRC     = $(sort $(C) $(HEADERS))

MD_DIR  = src
CODE_MD = $(MD_DIR)/99_code.md
MD_WC   = $(filter-out $(CODE_MD), $(wildcard $(MD_DIR)/*.md))
MD      = $(sort $(MD_WC))

OUT = report.pdf

FROM     = markdown
TO       = latex
METADATA = $(MD_DIR)/01_metadata.yaml

WATCHED_FILES = $(METADATA) $(SRC) $(MD)

PANDOC_IN = $(METADATA) $(MD) $(CODE_MD)

FLAGS = --pdf-engine xelatex
FLAGS += --template eisvogel.tex
FLAGS += -N --listings

.PHONY: all watch open clean

all: $(OUT)

$(OUT): $(PANDOC_IN)
	@echo "Starting Pandoc ..."
	@pandoc $(PANDOC_IN) -f $(FROM) -t $(TO) -o $@ $(FLAGS)
	@echo "$(OUT) updated"

$(CODE_MD): $(SRC)
	@./gencode-md.sh $^ > $@

watch:
	@echo $(WATCHED_FILES) | tr ' ' '\n' | \
	    entr -s 'notify-send -t 5000 "Compiling PDF" && \
            $(MAKE) --no-print-directory && \
            notify-send -t 5000 "Done" || \
            notify-send -t 5000 "Failed"'

open:
	zathura --fork $(OUT)

clean:
	rm $(OUT) $(CODE_MD)
