hyperfine -w 5 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/AnalyzeLoadFactorDependence/data1.json \
"taskset -c 2 ./hashTableBenchLoadFactor.out -f test.txt -c {size}" \
--parameter-list size 200,500,1000,2000,4000,5000,6000,8000,10000,15000,17000,20000,25000,50000