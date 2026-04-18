hyperfine -w 5 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/goodSizeHashTable/comparisonData1.json \
"taskset -c 2 ./hashTableBenchGoodSizeHashTable.out -f test.txt" \
"taskset -c 2 ./hashTableBenchAddrImprovedLFind.out -f test.txt" \