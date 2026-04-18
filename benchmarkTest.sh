hyperfine -w 5 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/hashFuncInlined/comparisonData1.json \
"taskset -c 2 ./hashTableBenchInlinedHashFunc.out -f test.txt" \
"taskset -c 2 ./hashTableBenchAddrImprovedLFind.out -f test.txt" \