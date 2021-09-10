DESCRIPTION = Colibri is a set of generic libraries
URL = https://github.com/ikle/colibru

include make-core.mk

.PHONY: net net-clean net-install

all: net
clean: net-clean
install: net-install

net:
	make -C net

net-clean:
	make -C net clean

net-install:
	make -C net install
