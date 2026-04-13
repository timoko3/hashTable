hyperfine -w 5 \
--min-runs 10 --max-runs 30 \
--export-json benchmarks/compareO0andO3.json \
"taskset -c 2 ./hashTableO0.out -f test.txt" \
"taskset -c 2 ./hashTableO3.out -f test.txt"

python3 benchmarks/handleBenchResult.py