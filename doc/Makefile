SRC_DIR =../src
SRC = $(wildcard $(SRC_DIR)/*.c)
SRC += $(wildcard $(SRC_DIR)/*.h)
SRC_SORTED = $(sort $(SRC))
REPORT_IN_DIR = src

CODE_MD = $(REPORT_IN_DIR)/code.md
REPORT_IN = $(filter-out $(CODE_MD), $(sort $(REPORT_IN_DIR)/*.md))
REPORT_OUT=report.pdf

.PHONY: report

report: $(REPORT_OUT)

eisvogel.tex:
	wget -O $@ 'https://raw.githubusercontent.com/Wandmalfarbe/pandoc-latex-template/master/eisvogel.tex' 

$(REPORT_OUT): $(REPORT_IN) eisvogel.tex $(CODE_MD)
	pandoc -f markdown --template eisvogel.tex -N \
	    -o $@ --listings --pdf-engine xelatex \
	    $(REPORT_IN)
	    @echo "Build finished."

$(CODE_MD): $(SRC_SORTED)
	./gencode-md.sh $^ > $@
