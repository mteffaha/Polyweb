# Makefile pour le projet SI3 -- Serveur Web 
#
#          Author: Erick Gallesio [eg@unice.fr]
#    Creation date: 22-Apr-2013 12:19 (eg)
# Last file update:  8-Jun-2013 23:34 (eg)


MD	= $(wildcard ../ext/*.md)
TEX     = $(wildcard *.tex)
PDF     = $(TEX:.tex=.pdf)

EXT_HTML= doc-extensions.html

%.pdf: %.tex
	@pdflatex $< && rm -f $*.aux $*.log $*.out *.blg *.bbl


all: $(EXT_HTML) $(PDF)


$(EXT_HTML): $(MD)
	cat Ressources/prelude.md $(MD) > tmp.md
	pandoc -H Ressources/doc-css.html -s tmp.md > $(EXT_HTML)
	rm -f tmp.md

clean:
	/bin/rm -f  *~

clobber: clean
	rm -f  $(EXT_HTML) $(PDF)
