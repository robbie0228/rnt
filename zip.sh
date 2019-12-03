cd ./tests

for file in $(ls *.cc *.h *.txt *.args *.in)
do
    if [ $(egrep -c "" $file) -ne $(wc -l < $file) ]; then
        echo "" >> $file
    fi
done

if [ -e Makefile ]; then
    if [ $(egrep -c "" Makefile) -ne $(wc -l < Makefile) ]; then
        echo "" >> Makefile
    fi
fi

cd ../

for file in $(ls *.cc *.h *.txt *.args *.in)
do
    if [ $(egrep -c "" $file) -ne $(wc -l < $file) ]; then
        echo "" >> $file
    fi
done

if [ -e Makefile ]; then
    if [ $(egrep -c "" Makefile) -ne $(wc -l < Makefile) ]; then
        echo "" >> Makefile
    fi
fi

rm a.zip 2> /dev/null

zip a.zip *.cc *.h Makefile
