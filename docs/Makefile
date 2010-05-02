SOURCE ?= report.tex
TARGET ?= $(SOURCE:.tex=.pdf)

VIEW	 := osascript -e "tell application \"Skim\" to revert document \"$(TARGET)\"" || open -a Skim "$(TARGET)"

default: view

$(TARGET): $(TARGET).d

# Including generated dependencies
ifneq "$(MAKECMDGOALS)" "clean"
include $(TARGET).d
endif


### Checking for dependencies ################################################
### Functions ################################################################

# $(call make-depend,source-file,object-file,depend-file)
define make-pdf-depend
	./make_pdf_depend "$1" "$2" "$3"
endef

### Rules ####################################################################
# Remove default rule
%.dvi : %.tex


test:
	@echo $(TARGET) depends on $(DEPS)

view: $(TARGET)
	$(VIEW)


%.aux %.idx %.lof %.lot %.nlo %.glo %.toc: %.tex | $(INCLUDES) $(filter %.eps,$(FIGURES))
	pdflatex $<

%.ind: %.idx
	makeindex $<

%.bbl: %.aux $(BIBDB)
	bibtex $<

%.gls: %.glo
	makeindex $< -s nomencl.ist -o $@

%.nls: %.nlo
	makeindex $< -s nomencl.ist -o $@

%.pdf: %.png
	convert $< $@

%.pdf.d: %.tex make_pdf_depend
	$(call make-pdf-depend,$<,$(subst .d,,$@),$@)

%.pdf: %.tex %.pdf.d
	# $^
	pdflatex $<

%.dvi: %.tex $(DEPS)
	latex $<

%.png: %.yuml yuml.rb
	ruby yuml.rb $< $@

clean:
	-rm -f *.aux *.bbl *.blg *.glo *.gls *.idx *.ilg *.ind *.lof *.log *.out *.toc *.d

clean_all: clean
	-rm -f *.pdf *.dvi


.PHONY: default clean clean_all view
.SECONDARY: