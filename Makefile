DIRS := $(shell find * -depth 0 -type d)
default: src

docs: 
	cd $@ && make

src: 
	cd $@ && make

.PHONY: default docs src