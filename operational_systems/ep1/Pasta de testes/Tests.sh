#!/bin/bash
make clean && make
clear
echo Compiling...
echo Generating trace files...
proc=(300)
finishedtest=0
for p in "${proc[@]}"
do
    echo 30 tests files $p processes each:
#    ./traceGenerator 30 1.5 $p 10 1.75
    a=Processos
    pasta=($(echo $p$a))
    for TYPE in {1..3..1}
    do
        for i in {0..29..1}
        do   
              
            input="trace$i.txt"
            output="output$i.txt"
            ./ep1 $TYPE $pasta/$input $pasta/$output
            line=($(cat $pasta/$output)) # array    
            escalonador=($(echo ${line[0]}))
            n=($(echo ${line[1]}))
            size=($(echo ${#line[@]}))
            context=($(echo ${line[$size-1]}))
            deadline=0
            START=2
            END=$size-1
            for (( k=$START; k<=$END; k++ ))
            do  
                x=($(echo ${line[$k]}))
                if (( $x == 1 )); then
                    deadline=$((deadline+1))
                fi
            done
            finishedtest=$((finishedtest+1))
            clear
            echo $finishedtest / 90 testes
            echo  TIPO_ESCAL= $TYPE
            echo  NU_PROCESS = $p

            TODAY=$(date)
            echo $finishedtest / 90 testes at $TODAY >> log.txt
            echo  -e ' \t ' TIPO_ESCAL= $TYPE >> log.txt
            echo  -e ' \t ' NU_PROCESS = $p >> log.txt
            echo  -e ' \t ' >> log.txt
            echo $p $TYPE $context $deadline >> RESULTADO_TESTES
        done
        
    done
done






































