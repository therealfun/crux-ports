DESTDIR := 
CC      := gcc
CF      := $(CFLAGS) -Wall $(shell pkg-config fuse --cflags) -DUSE_AUTH -D_XOPEN_SOURCE=500 -D_ISOC99_SOURCE -D_POSIX_C_SOURCE=200112L -DCERT_STORE=\"/etc/ssl/cert.pem\"
LF      := $(shell pkg-config fuse --libs | sed -e s/-lrt// -e s/-ldl//)
CF_SSL  := $(CF) -DUSE_THREAD -DUSE_SSL $(shell pkg-config gnutls --cflags)
LF_SSL  := $(LF) -lpthread $(shell pkg-config gnutls --libs)
targets := httpfs2 httpfs2_ssl # httpfs2.1 httpfs2_ssl.1

all:           $(targets)
httpfs2:       httpfs2.c     ; $(CC) $(CF)     httpfs2.c $(LF)     -o httpfs2
httpfs2_ssl:   httpfs2.c     ; $(CC) $(CF_SSL) httpfs2.c $(LF_SSL) -o httpfs2_ssl
httpfs2.1:     httpfs2.1.txt ; a2x -f manpage $<
httpfs2_ssl.1: httpfs2.1     ; ln -sf httpfs2.1 httpfs2_ssl.1
clean:                       ; rm -f $(targets)
	
install: all
	install -Dm0755 httpfs2       $(DESTDIR)/usr/bin/httpfs2
	install -Dm0755 httpfs2_ssl   $(DESTDIR)/usr/bin/httpfs2_ssl
	# install -Dm0644 httpfs2.1     $(DESTDIR)/usr/share/man/man1/httpfs2.1
	# install -Dm0644 httpfs2_ssl.1 $(DESTDIR)/usr/share/man/man1/httpfs2_ssl.1
