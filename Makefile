include config.mk
include lib/libs.mk
all: out/libshttp.so

out/libshttp.so: out \
	obj/methods.c.o \
	obj/version.c.o \
	
	if [ -n '$(wildcard obj/*.cpp.o)' ]; then $(CXX) -shared $(LDFLAGS) -o'out/.so' $(wildcard obj/*.o) $(wildcard lib/bin/*.a); else $(CC) -shared $(LDFLAGS) -o'out/.so' $(wildcard obj/*.o) $(wildcard lib/bin/*.a); fi
	$(OBJCOPY) --only-keep-debug 'out/.so' 'out/.so.dbg'
	chmod -x out/.so*
	$(OBJCOPY) --strip-unneeded 'out/.so'
	$(OBJCOPY) --add-gnu-debuglink='out/.so.dbg' 'out/.so.dbg'

obj/%.cpp.o: obj src/%.cpp
	$(CXX) -c -o'$@' 'src/$(patsubst obj/%.cpp.o,%,$@).cpp' $(CXXFLAGS)

obj/%.c.o: obj src/%.c
	$(CC) -c -o'$@' 'src/$(patsubst obj/%.c.o,%,$@).c' $(CFLAGS)

clean:
	$(RM) -r out
	$(RM) -r obj

out:
	$(MKDIR) out

obj:
	$(MKDIR) obj


compiledb: clean
	bear -- $(MAKE)

.PHONY: clean all compiledb
