TEST_INCLUDE=-Iinclude -I./lib/sunit/include

test: out/test_request_status_parser \
	
	@echo 'ALL TESTS PASSED!'

out/test_%: all
	$(CC) -o$@ $(TEST_INCLUDE) test/$(patsubst out/test_%,%,$@)_test.c $(CFLAGS) -Lout -lshttp
	LD_LIBRARY_PATH=out $(MIDDLEWARE) ./$@

.PHONY: test

