hyperfine -w 5 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/findOptimalSearchAmount2.json \
"taskset -c 2 ./hashTableOptimalSearch.out -f test.txt -n {searches}" \
--parameter-list searches 1,2,5,10,20,50,100,200,500,1000,2000,5000,10000,20000,50000,100000,200000,500000,1000000,2000000,5000000,10000000,20000000,50000000,100000000