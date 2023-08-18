PDF = index.pdf
MAIN = main.tex
MAIN_PDF = $(MAIN:.tex=.pdf)
MAIN_AUX = $(MAIN:.tex=.aux)

$(PDF) : $(MAIN) *.tex
	xelatex $<
	xelatex $<
	mv $(MAIN_PDF) $(PDF)
	make clean

bib: $(MAIN) *.tex
	xelatex $<
	bibtex $(MAIN_AUX)
	make

clean:
	rm *.aux *.log *.out *.toc *.bbl *.blg

.PHONY: clean, bib
