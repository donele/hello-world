#!/bin/bash

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

alias ssh06="ssh jelee@wron-mrct06"
alias ssh24="ssh jelee@smrc-chi24"
alias s="source ~/.bashrc"
#export BROWSER=/Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome

alias lt='ls -lrt'
alias tf='tail -f'
alias vic='cds && vim -c "NERDTreeToggle"'
alias vit='vim $HOME/Documents/.todo.txt'

# tail -f of the most recent file in the directory.
function ltf {
last_file=`ls -rt *.log | tail -n 1`
echo $ tail -f $last_file
tail -f $last_file
}

# Get the list of the log files of the running mx.exe's.
function lmx {
for pid in `ps -e | grep mx | grep -v lmx | awk '{print $1}'`
do
	ls -l /proc/$pid/fd | grep ' 1 ->' | awk "{print $pid,\$NF}"
done
}
