# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../Rack-SDK

# FLAGS will be passed to both the C and C++ compiler
FLAGS +=
CFLAGS +=
CXXFLAGS +=

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

# Add .cpp files to the build
SOURCES += $(wildcard src/*.cpp)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk


all: faust $(TARGET)
	@RACK_DIR=$(RACK_DIR) $(MAKE) -f $(RACK_DIR)/plugin.mk $@


clean: faust-clean
	@RACK_DIR=$(RACK_DIR) $(MAKE) -f $(RACK_DIR)/plugin.mk $@


faust: src/faust_generated.cpp src/faust/main-svg/process.svg


faust-clean: 
	rm -f src/faust_generated.cpp
	rm -rf src/faust/main-svg/*


run: install
	Rack


src/faust/main-svg/process.svg:
	@echo "Generating Faust diagrams..."
	faust2svg --simple-names --simplify-diagrams --fold-complexity 25 src/faust/main.dsp
	@echo


src/faust_generated.cpp: $(wildcard src/faust/*.dsp) src/faust/architecture_rack.cpp
	@echo "Compiling Faust files..."
	faust -a src/faust/architecture_rack.cpp -o src/faust_generated.cpp -os src/faust/main.dsp
	@echo


.PHONY: clean dist
.DEFAULT_GOAL := all
