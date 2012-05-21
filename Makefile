# Dear emacs, this is a -*- makefile -*-

# Copyright Simon Heisterkamp 2012

LIBRARY = PyConfigure
SRCDIR  = src
INCDIR  = include

OBJDIR  = obj
DEPDIR  = $(OBJDIR)/dep

# Some compilation options
VPATH    += $(OBJDIR) $(SRCDIR)
INCLUDES += -I./ -I./include/

# Set the locations of some files
EXECUTABLE = main
BINCPPFILE = src/$(EXECUTABLE).cpp
TESTFILE = unittest
TESTCPPFILE = src/$(EXECUTABLE).cpp
CENTER_FILE = PyConfigure

TEST_O = $(TESTFILE).o
CENTER_O = $(CENTER_FILE).o
SKIPCPPLIST = $(BINCPPFILE) $(TESTCPPFILE) $(SRCDIR)/$(CENTER_FILE).cpp
SKIPHLIST   = 
SHLIBFILE = ./lib/lib$(LIBRARY).so

CXXFLAGS += -O2 -pipe -Wall -W -Woverloaded-virtual -pthread -m64 $(shell python-config --includes) -Wall -Wno-overloaded-virtual -Wno-unused
# CXXFLAGS += -O2 -pipe -Wall -W -Woverloaded-virtual -pthread -m64 -I/Users/simon/software/root/clang/include -Wall -Wno-overloaded-virtual -Wno-unused
CPP = clang -E
LD = clang++
LDFLAGS = -O2 -m64 $(shell python-config --libs)
SOFLAGS = -dynamiclib -single_module -install_name $(PWD)/$(SHLIBFILE)

default: shlib bin

# Set up the default targets
ifeq ($(MAKECMDGOALS),test)
CXXFLAGS += -DBUILDTESTS
endif

# List of all header and source files to build automatically
HLIST   = $(filter-out $(SKIPHLIST),$(wildcard $(INCDIR)/*.h))
RAWCPPLIST = $(wildcard $(SRCDIR)/*.cpp)
CPPLIST = $(filter-out $(SKIPCPPLIST),$(RAWCPPLIST))

# List of all object files to build automatically
OLIST = $(patsubst %.cpp,%.o,$(notdir $(CPPLIST)))


# Implicit rule to compile all sources
%.o : %.cpp
	@echo "Compiling $<"
	@mkdir -p $(OBJDIR)
	@clang++ -c $< -o $(OBJDIR)/$(notdir $@) $(INCLUDES) $(CXXFLAGS)

##############################
# The dependencies section   
# - the purpose of the .d files is to keep track of the
#   header file dependence
# - this can be achieved using the makedepend command 
##############################
# .d tries to pre-process .cc
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
-include $(foreach var,$(notdir $(RAWCPPLIST:.cpp=.d)),$(DEPDIR)/$(var))
endif
endif

$(DEPDIR)/%.d: %.cpp
	@mkdir -p $(DEPDIR)
	@if test -f $< ; then \
		echo "Making $(@F)"; \
		$(SHELL) -ec '$(CPP) -MM $(CXXFLAGS) $(INCLUDES) $< | sed '\''/Cstd\/rw/d'\'' > $@'; \
	fi

# Rule to comile the executable
$(EXECUTABLE): $(EXECUTABLE).o $(SHLIBFILE)
	@echo "Making $(EXECUTABLE)"
	@clang++ -L$(dir $(SHLIBFILE)) -l$(LIBRARY) -o $@ $(OBJDIR)/$(EXECUTABLE).o $(CXXFLAGS)

# Rule to comile the tests
$(TESTFILE): $(TEST_O) $(SHLIBFILE)
	@echo "Making $(TESTFILE)"
	@clang++ -L$(dir $(SHLIBFILE)) -l$(LIBRARY) -o $@ $(OBJDIR)/$(TEST_O) $(CXXFLAGS)

# Rule to combine objects into a unix shared library
$(SHLIBFILE): $(OLIST) $(CENTER_O)
	@echo "Making shared library: $(SHLIBFILE)"
	@rm -f $(SHLIBFILE)
	@mkdir -p $(dir $(SHLIBFILE))
# ifneq (,$(findstring macosx,$(ARCH)))
	@$(LD) $(LDFLAGS) -dynamiclib -single_module -undefined dynamic_lookup $(addprefix $(OBJDIR)/,$(OLIST)) $(OBJDIR)/$(CENTER_O) -o $(SHLIBFILE) $(CXXFLAGS)
# else
#	$(LD) $(LDFLAGS) $(SOFLAGS) $(addprefix $(OBJDIR)/,$(OLIST)) $(OBJDIR)/$(CENTER_O) -o $(SHLIBFILE)
# endif

# Useful build targets
shlib: $(SHLIBFILE)

bin: $(EXECUTABLE)

test: $(TESTFILE) bin
	@echo "Running $(TESTFILE):"
	@./$(TESTFILE)

clean:
	@rm -f $(EXECUTABLE)
	@rm -f $(TESTFILE)
	@rm -f $(OBJDIR)/*.o
	@rm -f $(SHLIBFILE)

distclean: clean
	@rm -rf $(OBJDIR)
	@rm -rf $(DEPDIR)

.PHONY : shlib default clean bin
