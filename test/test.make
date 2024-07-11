#  test

override test_this := $(lastword $(MAKEFILE_LIST))
override test_curdir := $(realpath $(dir $(test_this)))

test:
	$(BINDIR)/dfi
	$(BINDIR)/exercise

.PHONY: test
