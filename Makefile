CC := g++
SRCDIR := src
BUILDDIR := build
TESTDIR := test
TARGET := bin/cp
TARGETDIR := bin
UTIL := util
UTILBIN := bin/datasetHelper

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
UTILSOURCES := $(shell find $(UTIL) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -w -std=c++11
INC := -I include
STATIC_ANALYZER := oclint
TESTLIB := -lgtest -lgtest_main -lpthread

$(TARGET) : $(OBJECTS)
	@echo " Linking "
	@mkdir -p bin
	@echo " $(CC) $(CFLAGS) $^ -o $(TARGET) $(LIB) $(LINKER)"; $(CC) $(CFLAGS) $^ -o $(TARGET)

$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

helper: $(UTILBIN)
	@mkdir -p data/images

$(UTILBIN): $(UTILSOURCES)
	@mkdir -p bin
	@echo " $(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^"; $(CC) $(CFLAGS) $(INC) $(LIB) -o $@ $^

static-analyze:
	$(STATIC_ANALYZER) $(SOURCES) -- -c $(CFLAGS) $(INC) $(LIB)

clean:
	@echo " Cleaning... "
	@echo " rm -rf $(BUILDDIR) $(TARGETDIR)/*"; rm -rf $(BUILDDIR) $(TARGETDIR)/*

run:
	./bin/cp -n 60000 -d 784 -f data/Mnist.ds

runMedian:
	./bin/cp -n 60000 -d 784 -f data/Mnist.ds -m

.PHONY: clean
.PHONY: run
.PHONY: runMedian
