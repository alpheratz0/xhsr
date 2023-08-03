.POSIX:
.PHONY: all clean install uninstall dist

include config.mk

all: xhsr

xhsr: xhsr.o
	$(CC) $(LDFLAGS) -o xhsr xhsr.o $(LDLIBS)

clean:
	rm -f xhsr xhsr.o xhsr-$(VERSION).tar.gz

install: xhsr
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f xhsr $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/xhsr
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f xhsr.1 $(DESTDIR)$(MANPREFIX)/man1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/xhsr.1

dist: clean
	mkdir -p xhsr-$(VERSION)
	cp -R COPYING config.mk Makefile README xhsr.1 xhsr.c xhsr-$(VERSION)
	tar -cf xhsr-$(VERSION).tar xhsr-$(VERSION)
	gzip xhsr-$(VERSION).tar
	rm -rf xhsr-$(VERSION)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/xhsr
	rm -f $(DESTDIR)$(MANPREFIX)/man1/xhsr.1
