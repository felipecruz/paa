FLAGS=-lrt -O3

all: clean
	@gcc paa.c knth_nk.c -Wall -o knth_nk -DMAIN
	@gcc paa.c knth_merge.c -Wall -o knth_merge -DMAIN
	@gcc paa.c knth_n_mom.c -Wall -o knth_n_mom -DMAIN
	@gcc paa.c knth_n_quickselect.c -o -Wall -o knth_n_quickselect -DMAIN
	@gcc gen_instances.c paa.c knth_nk.c knth_merge.c knth_n_mom.c knth_n_quickselect.c benchmark.c -Wall -lm -O2 -o benchmark
	@gcc paa.c gen_instances.c -Wall -lm -o gen_instances -DMAIN

test:
	./knth_nk
	./knth_merge
	./knth_n_mom
	./knth_n_quickselect

clean:
	@rm -f knth_nk
	@rm -f knth_merge
	@rm -f knth_n_mom
	@rm -f knth_n_quickselect
	@rm -f gen_instances
	@rm -f benchmark

debug:
	@gcc gen_instances.c paa.c knth_nk.c knth_merge.c knth_n_mom.c knth_n_quickselect.c benchmark.c -g -Wall -lm -o benchmark
