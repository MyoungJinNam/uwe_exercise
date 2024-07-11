# reference 

exercise_this := $(lastword $(MAKEFILE_LIST))
exercise_curdir := $(realpath $(dir $(exercise_this)))
exercise_project := $(notdir $(exercise_curdir))

ifeq ($(COMPILER_FAMILY),gcc)
EXERCISE_LFLAGS = -L $(OBJDIR) -Wl,-R$(OBJDIR) -l util 
else
EXERCISE_LFLAGS =
endif

exercise_objfiles = \
	$(OBJDIR)/$(exercise_project)/instrumented.c.o 

main: $(BINDIR)/exercise

$(BINDIR)/%: $(OBJDIR)/$(exercise_project)/%.c.o | $(BINDIR)
	$(CC) $(LFLAGS) $^ -o $@ $(EXERCISE_LFLAGS)

$(BINDIR)/exercise: $(OBJDIR)/$(exercise_project)/instrumented.c.o | $(BINDIR)
	$(CC) $(LFLAGS) $^ -o $@ $(EXERCISE_LFLAGS)

$(exercise_objfiles): CFLAGS += -I$(exercise_curdir) -O0

ifeq ($(COMPILER_FAMILY),gcc)
$(OBJDIR)/$(exercise_project)/subobject.c.o: CFLAGS += -O0 
else
$(OBJDIR)/$(exercise_project)/subobject.c.o: CFLAGS += -Wno-attributes
endif

$(exercise_objfiles): $(exercise_this)
