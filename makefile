#

ifeq (,$(wildcard config.make))
$(error "Error: config.make not found.")
endif

include config.make

override C_SOURCES = $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)

override SOURCES  = $(C_SOURCES)

override OBJECTS  = $(C_SOURCES:src/%.c=$(OBJDIR)/%.c.o)

override DEPENDS = $(OBJECTS:%.o=%.d)
override OBJDIRS = $(sort $(dir $(OBJECTS)))

main:

# include subprojects here
include src/utils/util.make
include src/reference/dfi.make
#
#  TODO: Complete the exercise program (instrumented.c) and enable exercise.make 
#
#include src/exercise/exercise.make

# common compilation rules
$(OBJDIR)/%.c.o: src/%.c | $(OBJDIRS)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/%.S.o: src/%.S | $(OBJDIRS)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/%.cpp.o: src/%.cpp | $(OBJDIRS)
	$(CXX) -c $(CXXFLAGS) $< -o $@

# clean targets
clean:
	@rm -rf $(BUILD)

distclean: clean
	@rm -vf config.make

# rebuild when necessary
-include $(DEPENDS)

$(OBJECTS): makefile

$(OBJDIRS):
	@mkdir -p $@

$(BINDIR) $(LIBDIR):
	@mkdir -p $@

# tests

include test/test.make

.PHONY: main clean distclean
