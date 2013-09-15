FLAGS=-lrt

all:
	gcc paa.c knth_nk.c -Wall -o knth_nk -DMAIN
	gcc paa.c knth_merge.c -Wall -o knth_merge -DMAIN
	gcc paa.c knth_n_mom.c -Wall -o knth_n_mom -DMAIN
	gcc paa.c knth_n_quickselect.c -o -Wall -o knth_n_quickselect -DMAIN
	gcc gen_instances.c paa.c knth_nk.c knth_merge.c knth_n_mom.c knth_n_quickselect.c benchmark.c -Wall -lrt -lm -o benchmark
	gcc paa.c gen_instances.c -Wall -lrt -lm -o gen_instances -DMAIN

test:
	./knth_nk
	./knth_merge
	./knth_n_mom
	./knth_n_quickselect

clean:
	rm -f knth_nk
	rm -f knth_merge
	rm -f knth_n_mom
	rm -f knth_n_quickselect
	rm -f gen_instances

debug:
	gcc knth_nk.c -g -Wall -o knth_nk
	gcc knth_merge.c -g -Wall -o knth_merge
	gcc knth_n_mom.c -g -Wall -o knth_n_mom

	gdb knth_merge
