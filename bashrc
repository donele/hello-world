#!/bin/bash

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# \e[x;ym : start color scheme, x = 0, y = 30-36
# \e[m : stop color scheme
# 0;36 : cyan
get_git_branch() {
    git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}
weekday() {
    date +%a
}
export PS1="\e[0;36m[\$(weekday) \t \u@\h:\w]\e[m\$(get_git_branch)\e[m\n$ "
alias s="source ~/.bashrc"
export EDITOR=vim
#export BROWSER=/Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome

export EDITOR=vim
#export PS1="\e[0;36m[\t \u@\h:\w, \j jobs, \$?]\e[m\n$ "
export PS1="\e[0;36m[\t \u@\h:\w]\e[m\n$ "

alias lt='ls -lrt'
alias ll='ls -al'
alias tf='tail -f'
alias gt='git status'
alias ga='git add'
alias gc='git commit -v'
alias gd='git diff'
alias gl='git log --oneline'
alias gb='git branch'
alias cmake_debug='cmake -DCMAKE_BUILD_TYPE=Debug'

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

