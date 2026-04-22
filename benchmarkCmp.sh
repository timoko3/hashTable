hyperfine -w 5 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/lfOptimize/comparisonData2.json \
"taskset -c 2 ./hashTableBenchWithLfind.out -f test.txt" \
"taskset -c 2 ./hashTableBenchWithoutLfind.out -f test.txt" \