DESCRIPTION = Colibri is a set of generic libraries
URL = https://github.com/ikle/colibru

include make-core.mk

.PHONY: conf conf-clean conf-install
.PHONY: net   net-clean  net-install
.PHONY: sys   sys-clean  sys-install

all:     conf         net         sys
clean:   conf-clean   net-clean   sys-clean
install: conf-install net-install sys-install

conf:
	make -C conf

conf-clean:
	make -C conf clean

conf-install:
	make -C conf install

net:
	make -C net

net-clean:
	make -C net clean

net-install:
	make -C net install

sys:
	make -C sys

sys-clean:
	make -C sys clean

sys-install:
	make -C sys install
