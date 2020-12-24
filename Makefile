CXX ?= g++

SRCDIR = src
BUILDDIR = build
TARGET = birds
SRCEXT := cc
SOURCES = $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
CFLAGS = -Wall -Wextra -std=c++11
LIBS = -lglfw -lGL -ldl
INCLUDE = -I include

$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $^ -o $@ $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	@rm -rf $(BUILDDIR)
	@rm -f $(TARGET)
