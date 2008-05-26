##
## Makefile
## $Id: Makefile,v 1.2 2008/05/26 18:37:06 mina86 Exp $
##

all:
	exec $(MAKE) -C src all

%: FORCE
	exec $(MAKE) -C src $@

.PHONY: FORCE
