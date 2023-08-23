PDF = index.pdf
MAIN = main

$(PDF) : $(MAIN).tex *.tex report/*.tex
	xelatex $<
	xelatex $<
	mv $(MAIN).pdf $(PDF)
	make clean

bib: $(MAIN).tex *.tex report/*.tex
	xelatex $<
	# bibtex $(MAIN).aux
	biber $(MAIN).bcf
	make

clean:
	rm report/*.aux *.aux *.log *.out *.toc *.bbl *.blg $(MAIN).bcf $(MAIN).run.xml

.PHONY: clean, bib
