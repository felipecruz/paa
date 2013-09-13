all:
	gcc knth_nk.c -Wall -o knth_nk
	gcc knth_merge.c -Wall -o knth_merge
	gcc knth_n_mom.c -Wall -o knth_n_mom

test:
	./knth_nk
	./knth_merge
	./knth_n_mom

debug:
	gcc knth_nk.c -g -Wall -o knth_nk
	gcc knth_merge.c -g -Wall -o knth_merge
	gcc knth_n_mom.c -g -Wall -o knth_n_mom

	gdb knth_merge
