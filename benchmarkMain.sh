hyperfine -w 5 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/withOptimizationCrc/hashIntrinsickOptimization.json \
"taskset -c 2 ./hashTableBench.out -f test.txt" 