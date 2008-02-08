##
## Makefile
## $Id: Makefile,v 1.1 2008/02/08 21:47:32 mina86 Exp $
##

all:
	exec $(MAKE) -C src all

%:
	exec $(MAKE) -C src $@

