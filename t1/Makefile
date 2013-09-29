FLAGS=-Wall -lrt -O2 -lm
FLAGS=-Wall -O2 -lm

all: clean
	@gcc paa.c knth_nk.c $(FLAGS) -o knth_nk -DMAIN
	@gcc paa.c knth_merge.c $(FLAGS) -o knth_merge -DMAIN
	@gcc paa.c knth_n_mom.c $(FLAGS) -o knth_n_mom -DMAIN
	@gcc paa.c knth_n_quickselect.c -o $(FLAGS) -o knth_n_quickselect -DMAIN
	@gcc gen_instances.c paa.c knth_nk.c knth_merge.c knth_n_mom.c knth_n_quickselect.c benchmark.c $(FLAGS) -o benchmark

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
	@gcc gen_instances.c paa.c knth_nk.c knth_merge.c knth_n_mom.c knth_n_quickselect.c benchmark.c -g $(FLAGS) -o benchmark
