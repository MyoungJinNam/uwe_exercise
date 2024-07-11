# reference 

override dfi_this := $(lastword $(MAKEFILE_LIST))
override dfi_curdir := $(realpath $(dir $(dfi_this)))
override dfi_project := $(notdir $(dfi_curdir))

override DFI_LFLAGS = -L $(OBJDIR) -Wl,-R$(OBJDIR) -l util 

override dfi_objfiles = \
	$(OBJDIR)/$(dfi_project)/corrupted.c.o 

main: $(BINDIR)/dfi

$(BINDIR)/%: $(OBJDIR)/$(dfi_project)/%.c.o | $(BINDIR)
	$(CC) $(LFLAGS) $^ -o $@ $(DFI_LFLAGS)

$(BINDIR)/dfi: $(OBJDIR)/$(dfi_project)/corrupted.c.o | $(BINDIR)
	$(CC) $(LFLAGS) $^ -o $@ $(DFI_LFLAGS)

$(dfi_objfiles): CFLAGS += -I$(dfi_curdir) -O0

ifeq ($(COMPILER_FAMILY),gcc)
$(OBJDIR)/$(dfi_project)/subobject.c.o: CFLAGS += -O0 
else
$(OBJDIR)/$(dfi_project)/subobject.c.o: CFLAGS += -Wno-attributes
endif

$(dfi_objfiles): $(dfi_this)
