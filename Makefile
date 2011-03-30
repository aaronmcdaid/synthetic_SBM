MAIN=syntheticBlocks
CC=g++

clean:
	-rm ${MAIN} *.o

LDFLAGS=-lgsl -lgslcblas

${MAIN}: cmdline.o syntheticBlocks.o

syntheticBlocks.o: cmdline.c

cmdline.c: cmdline.ggo
	# remake cmdline.c . But it's OK unless you change the .ggo file. You'll need gengetopt(1) to be able to run this.
	gengetopt  --unamed-opts < cmdline.ggo














%.swap01:
	test -f "$*"
	< "$*" egrep Summary -A6 | egrep bool -B3 | egrep -v ,  | while true; do read z; read p1; read dashes; test "$$dashes" = "--" || break; test 1 = $$(echo "$$p1" | cut -d: -f2) && echo "$$z" || { echo "$$z" | tr 01 10; } ; done | head -n40000 | tail -n 20000 > "$@"


