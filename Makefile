CXX ?= g++

SRCDIR = src
BUILDDIR = build
TARGET = birds
SRCEXT := cc
SOURCES = $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
CFLAGS = -Wall -Wextra -std=c++11
LIBS = -lglfw -lGL -ldl -L lib
INCLUDE = -I include

$(TARGET): $(OBJECTS) lib/libariamis.a
	@mkdir -p $(BUILDDIR)
	$(CXX) $^ lib/libariamis.a -o $@ $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	@rm -rf $(BUILDDIR)
	@rm -f $(TARGET)

install-deps:
	git clone --depth=1 https://github.com/Zunawe/ariamis.git && cd ariamis && make && mkdir -p ../lib ../include/ariamis && cp lib/libariamis.a ../lib/ && cp -r include/* ../include/ariamis && cd .. && rm -rf ariamis

.PHONY: clean install-deps
