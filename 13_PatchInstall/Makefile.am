bin_PROGRAMS=numfinder
numfinder_SOURCES=main.c
pkgdata_DATA=ru/LC_MESSAGES/numfinder.mo

ru/LC_MESSAGES/numfinder.mo: ru_numfinder.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

ru_numfinder.po: numfinder.pot
	msgmerge -U $@ $<

numfinder.pot:	main.c  
	xgettext -k_ -c main.c -o numfinder.new.pot
	msgmerge -U numfinder.pot numfinder.new.pot
	rm numfinder.new.pot

en_numfinder: numfinder
	./numfinder

ru_numfinder:numfinder
	LANGUAGE=ru_RU PO_LOCAL=1 ./numfinder

gitclean:
	git clean -fd

clean:
	rm -rf ru messages.new.pot messages.pot
cleanall: clean
	rm compile config.status 

	rm -rf numfinder configure *~ *.o *.log *.in *.m4 config.h* \
		   Makefile depcomp config.status \
		   compile install-sh missing stamp-h1 autom4te.cache .deps
