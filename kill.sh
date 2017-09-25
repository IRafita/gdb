#/bin/bash o algo paregut

kill -9 $(ps | grep gdb | awk '{print $1}')
