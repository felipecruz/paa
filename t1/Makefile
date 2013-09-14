all:
	gcc paa.c knth_nk.c -Wall -o knth_nk -DMAIN
	gcc paa.c knth_merge.c -Wall -o knth_merge -DMAIN
	gcc paa.c knth_n_mom.c -Wall -o knth_n_mom -DMAIN
	gcc paa.c knth_n_quickselect.c -o -Wall -o knth_n_quickselect -DMAIN
	gcc paa.c knth_nk.c knth_merge.c knth_n_mom.c knth_n_quickselect.c benchmark.c -Wall -o benchmark

test:
	./knth_nk
	./knth_merge
	./knth_n_mom
	./knth_n_quickselect

debug:
	gcc knth_nk.c -g -Wall -o knth_nk
	gcc knth_merge.c -g -Wall -o knth_merge
	gcc knth_n_mom.c -g -Wall -o knth_n_mom

	gdb knth_merge
