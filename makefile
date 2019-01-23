SOURCES=*.c
HEADERS=*.h *.inc

.PHONY: test clean

prettysharp: $(SOURCES) $(HEADERS)
	clang -o prettysharp -Werror $(SOURCES)

test: prettysharp
	python3 ./test.py

clean:
	rm prettysharp