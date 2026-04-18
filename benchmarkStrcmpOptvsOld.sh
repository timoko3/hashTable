hyperfine -w 5 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/strcmpOptVsOld/comparisonData1.json \
"taskset -c 2 ./hashTableBenchOldStrcmp.out -f test.txt" \
"taskset -c 2 ./hashTableBenchOptStrcmp.out -f test.txt" \