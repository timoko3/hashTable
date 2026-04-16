hyperfine -w 5 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/comparisonHashFunctions/comparisonData.json \
"taskset -c 2 ./hashTableBenchCrcOpt.out -f test.txt" \
"taskset -c 2 ./hashTableBenchGnu.out -f test.txt" \
"taskset -c 2 ./hashTableBenchRol.out -f test.txt" \
"taskset -c 2 ./hashTableBenchMurMur.out -f test.txt" 