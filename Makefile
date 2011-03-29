MAIN=syntheticBlocks

clean:
	-rm ${MAIN} *.o
%.swap01:
	test -f "$*"
	< "$*" egrep Summary -A6 | egrep bool -B3 | egrep -v ,  | while true; do read z; read p1; read dashes; test "$$dashes" = "--" || break; test 1 = $$(echo "$$p1" | cut -d: -f2) && echo "$$z" || { echo "$$z" | tr 01 10; } ; done | head -n40000 | tail -n 20000 > "$@"

LDFLAGS=-lgsl -lgslcblas

