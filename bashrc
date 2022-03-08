#!/bin/bash

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

alias s="source ~/.bashrc"
#export BROWSER=/Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome

export EDITOR=vim
#export PS1="\e[0;36m[\t \u@\h:\w, \j jobs, \$?]\e[m\n$ "
export PS1="\e[0;36m[\t \u@\h:\w]\e[m\n$ "
export KAYRROS_CLIENT_LOGIN=rlam@kempstar.com
export KAYRROS_CLIENT_PASSWORD=holymonkey@2014

alias lt='ls -lrt'
alias tf='tail -f'
gs='git status'
ga='git add'
gc='git commit =v'
gd='git diff'
gl='git log --oneline'

if [ -e $HOME/functions.sh ]
then
    source $HOME/functions.sh
fi

# tail -f of the most recent file in the directory.
function ltf {
last_file=`ls -rt *.log | tail -n 1`
echo $ tail -f $last_file
tail -f $last_file
}

