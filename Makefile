include config.mk
include lib/libs.mk
all: out/libshttp.so

out/libshttp.so: out \
	obj/methods.c.o \
	obj/version.c.o \
	obj/request_status_parser.c.o \
	
	if [ -n '$(wildcard obj/*.cpp.o)' ]; then $(CXX) -shared $(LDFLAGS) -o'out/libshttp.so' $(wildcard obj/*.o) $(wildcard lib/bin/*.a); else $(CC) -shared $(LDFLAGS) -o'out/libshttp.so' $(wildcard obj/*.o) $(wildcard lib/bin/*.a); fi
	$(OBJCOPY) --only-keep-debug 'out/libshttp.so' 'out/libshttp.so.dbg'
	chmod -x out/libshttp.so*
	$(OBJCOPY) --strip-unneeded 'out/libshttp.so'
	$(OBJCOPY) --add-gnu-debuglink='out/libshttp.so.dbg' 'out/libshttp.so'

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

include test/tests.mk

compiledb: clean
	bear -- $(MAKE) test

.PHONY: clean all compiledb
