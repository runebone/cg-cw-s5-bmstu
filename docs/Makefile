PDF = index.pdf
MAIN = main.tex
MAIN_PDF = $(MAIN:.tex=.pdf)

$(PDF) : $(MAIN) *.tex
	xelatex $<
	xelatex $<
	mv $(MAIN_PDF) $(PDF)
	make clean

clean:
	rm *.aux *.log *.out *.toc

.PHONY: clean
