.PHONY: all project test clean

all: project test

project:
	$(MAKE) -C src

test:
	$(MAKE) -C test
