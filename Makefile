.PHONY: all project test clean

all: project

project:
	$(MAKE) -C src

test:
	$(MAKE) -c test
