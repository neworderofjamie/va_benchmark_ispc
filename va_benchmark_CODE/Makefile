ISPCOBJECTS := customUpdateISPC.o neuronUpdateISPC.o synapseUpdateISPC.o
OBJECTS := customUpdate.o neuronUpdate.o synapseUpdate.o init.o runner.o

ISPC := ispc
ISPCFLAGS := --pic --target=avx2-i32x8
CXXFLAGS := -c -fPIC -std=c++11 -MMD -MP 
LINKFLAGS := -shared 

DEPS := $(OBJECTS:.o=.d)

.PHONY: all clean

all: librunner.so

librunner.so: $(OBJECTS) $(ISPCOBJECTS) runner.o 
	@$(CXX) $(LINKFLAGS) -o $@ $(OBJECTS) $(ISPCOBJECTS)

-include $(DEPS)

%.o: %.cc %.d
	@$(CXX) $(CXXFLAGS) -o $@ $<

%.d: ;


# **TODO** figure out dependency arguments
%.o: %.ispc
	$(ISPC) $(ISPCFLAGS) -o $@ $< 

clean:
	@rm -f $(OBJECTS) $(ISPCOBJECTS) $(DEPS) librunner.so
