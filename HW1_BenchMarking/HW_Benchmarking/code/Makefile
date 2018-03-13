all:	cpu_benchmark memory_benchmark
cpu_benchmark:
	$(info ********************** CPU Benchmark **********************)
	gcc cpu_benchmark.c -o output -lpthread
	./output 1 1
	./output 1 2
	./output 1 4
	./output 1 8
	./output 2 1
	./output 2 2
	./output 2 4
	./output 2 8
	
memory_benchmark:
	$(info ******************* Memory Benchmark **********************)
	gcc memory_benchmark.c -o output -lpthread
	
	./output 1 1 1
	./output 1 1 2
	./output 1 1 4
	./output 1 1 8
	
	./output 2 1 1
	./output 2 1 2
	./output 2 1 4
	./output 2 1 8

	./output 3 1 1
	./output 3 1 2
	./output 3 1 4
	./output 3 1 8
	
	./output 1 2 1
	./output 1 2 2
	./output 1 2 4
	./output 1 2 8	
	
	./output 1 3 1
	./output 1 3 2
	./output 1 3 4
	./output 1 3 8
	
	./output 1 4 1
	./output 1 4 2
	./output 1 4 4
	./output 1 4 8
	
	./output 2 2 1
	./output 2 2 2
	./output 2 2 4
	./output 2 2 8

	./output 2 3 1
	./output 2 3 2
	./output 2 3 4
	./output 2 3 8
	
	./output 2 4 1
	./output 2 4 2
	./output 2 4 4
	./output 2 4 8	
	
	./output 3 2 1
	./output 3 2 2
	./output 3 2 4
	./output 3 2 8
	
	./output 3 3 1
	./output 3 3 2
	./output 3 3 4
	./output 3 3 8
	
	./output 3 4 1
	./output 3 4 2
	./output 3 4 4
	./output 3 4 8
