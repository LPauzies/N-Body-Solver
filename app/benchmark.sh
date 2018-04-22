#!/bin/zsh

repeats=20
command_to_run='bin/prog'
file=''

round() {
  printf "%.${2}f" "${1}"
}

run_tests() {
    # -------------------------------------------------------------------------
    # Benchmark loop
    # --------------------------------------------------------------------------
    echo 'Benchmarking ' $command_to_run '...'
    echo 'Repeats='${repeats}'\n'
    means=0
    # Run the given command [repeats] times
    for (( i = 1; i <= $repeats ; i++ ))
    do
        # percentage completion
        p=$(( $i * 100 / $repeats))
        # indicator of progress
        l=$(seq -s "+" $i | sed 's/[0-9]//g')

        # Calculate time for the excecution
        timee=$({/usr/bin/time -f '%e' $command_to_run -b -n 1000 -f $file;} 2>&1)
        echo $i') '$timee' s\033[K'

        # Calculate the average of the times
        average=$((average + $timee))
        echo -ne ${l}' '${p}'% \r'
    done;
    average=$((average/${repeats}))
    echo '---------------\033[K'
    echo -ne 'Average= '$(round ${average} 3)'s\n'
}

# Option parsing
while getopts n:f: OPT
do
    case "$OPT" in
        n)
            repeats=$OPTARG
            ;;
        f)
            file=$OPTARG
            run_tests
            ;;
        \?)
            echo 'No arguments supplied'
            exit 1
            ;;
    esac
done

shift `expr $OPTIND - 1`
