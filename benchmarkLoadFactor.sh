hyperfine -w 3 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/AnalyzeLoadFactorDependence/data2.json \
"taskset -c 2 ./hashTableBench.out -f test.txt -c {size}" \
--parameter-list size 200,500,1000,4000,5000,10000,15000,20000,25000,50000