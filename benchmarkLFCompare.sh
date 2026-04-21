hyperfine -w 5 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/lfOptimize/comparisonData1.json \
"taskset -c 2 ./hashTableBenchBadLf.out -f test.txt" \
"taskset -c 2 ./hashTableBenchGoodLf.out -f test.txt" \