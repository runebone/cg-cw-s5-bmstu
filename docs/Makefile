PDF = index.pdf
RUNOV = Runov-IU7-54B-RPZ-CW.pdf
MAIN = main
# FLAGS = -shell-escape
CC = pdflatex
# CC = xelatex
FLAGS = 
SHIT = *.aux *.log *.out *.toc *.bbl *.blg *.nav *.snm

all: bib

pres : pres.tex preamble.tex
	-$(CC) $(FLAGS) $<
	-$(CC) $(FLAGS) $<
	-mv pres.pdf $(PDF)
	make moveout

$(PDF) : $(MAIN).tex *.tex report/*.tex
	make resurrect
	-$(CC) $(FLAGS) $<
	-$(CC) $(FLAGS) $<
	-mv $(MAIN).pdf $(PDF)
	make moveout

bib: $(MAIN).tex *.tex report/*.tex
	make resurrect
	-$(CC) $(FLAGS) $<  # > /dev/null
	-bibtex $(MAIN).aux > /dev/null
	-$(CC) $(FLAGS) $<  # > /dev/null
	-$(CC) $(FLAGS) $<  > /dev/null
	-mv $(MAIN).pdf $(RUNOV)
	make moveout

moveout:
	-mkdir -p out > /dev/null
	-mkdir -p out/report > /dev/null
	-mv $(SHIT) out > /dev/null
	-cd report && mv *.aux ../out/report > /dev/null

resurrect:
	-mv out/report/* report > /dev/null
	-mv out/* . > /dev/null

clean:
	-rm  $(SHIT) > /dev/null
	-cd report && rm $(SHIT) > /dev/null
	rm -rf out

.PHONY: all, clean, bib, moveout, resurrect
