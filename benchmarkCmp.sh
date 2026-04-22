hyperfine -w 5 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/hashFuncInlined/comparisonData2.json \
"taskset -c 2 ./hashTableBenchWithoutFuncPtr.out -f test.txt" \
"taskset -c 2 ./hashTableBenchWithFuncPtr.out -f test.txt" \