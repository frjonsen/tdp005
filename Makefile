CXXFLAGS=-Wall -Wextra -Weffc++ -Wold-style-cast -Woverloaded-virtual -std=c++11 -pedantic -Werror
CXXFLAGS_DEBUG= $(CXXFLAGS) -g
LIB=-lSDL2 -lSDL2_image
SRCDIR=src
BUILDDIR=build
TARGETDIR=bin
TARGET=$(TARGETDIR)/app

INC=-I include
CC=g++

all: $(TARGET)

SRCEXT=cc
SOURCES=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS=$(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(TARGETDIR)
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CXXFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
