# Copyright (c) 2023 Arm Limited. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause

override util_this := $(lastword $(MAKEFILE_LIST))
override util_curdir := $(realpath $(dir $(util_this)))
override util_project := $(notdir $(util_curdir))

override UTIL_LFLAGS = -shared 

override util_objects = \
	$(OBJDIR)/$(util_project)/libutil.c.o

main: $(OBJDIR)/libutil.so

$(util_objects): CFLAGS += -fPIC

$(OBJDIR)/libutil.so: $(util_objects) | $(LIBDIR)
	$(CC) $(LFLAGS) $^ -o $@ $(UTIL_LFLAGS)

$(util_objects): $(util_this)
