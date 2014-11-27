CXXFLAGS=-Wall -Wextra -Weffc++ -Wold-style-cast -Woverloaded-virtual -fdiagnostics-color=always -std=c++11 -pedantic -Werror
CXXFLAGS_DEBUG= $(CXXFLAGS) -g
LIB=-lSDL2
SRCDIR=src
BUILDDIR=build
TARGET=bin/app

INC=-I include
CC=g++-4.9

SRCEXT=cc
SOURCES=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
 	