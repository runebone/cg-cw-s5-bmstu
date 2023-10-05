PDF = index.pdf
MAIN = main
FLAGS = -synctex=1 -interaction=nonstopmode

all:
	make bib

$(PDF) : $(MAIN).tex *.tex report/*.tex
	xelatex $(FLAGS) $<
	xelatex $(FLAGS) $<
	mv $(MAIN).pdf $(PDF)

bib: $(MAIN).tex *.tex report/*.tex
	xelatex $(FLAGS) $<
	# bibtex $(MAIN).aux
	biber $(MAIN).bcf
	xelatex $(FLAGS) $<
	xelatex $(FLAGS) $<
	mv $(MAIN).pdf $(PDF)

clean:
	rm report/*.aux *.aux *.log *.out *.toc *.bbl *.blg $(MAIN).bcf $(MAIN).run.xml *.synctex.gz

.PHONY: clean, bib
