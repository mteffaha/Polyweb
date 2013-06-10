#           Author: Erick Gallesio [eg@unice.fr]
#    Creation date: 24-Apr-2013 17:21 (eg)
# Last file update:  8-Jun-2013 23:25 (eg)

SUBDIR=src ext tests demos doc

all:
	for i in $(SUBDIR) ;do (cd $$i; $(MAKE) all) ;done

clean:
	for i in $(SUBDIR) ;do (cd $$i; $(MAKE) clean) ;done
	rm -f **/*~

clobber: clean
	for i in $(SUBDIR) ;do (cd $$i; $(MAKE) clobber) ;done
	rm -rf distrib distrib.tgz

distrib: all distrib.tgz

distrib.tgz: all
	rm -rf distrib
	mkdir -p distrib
	cp -a Makefile README $(SUBDIR) distrib
	(cd distrib; rm ext/cgi.c ext/mytraceuri.c ext/prettify.c \
	    ext/ssi.c src/config.c src/handler.c src/http.c \
	    src/mimetype.c src/misc.c)
	tar cvfz distrib.tgz distrib
	rm -rf distrib
