set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'

" The following are examples of different formats supported.
" Keep Plugin commands between vundle#begin/end.
" plugin on GitHub repo
Plugin 'tpope/vim-fugitive'
Plugin 'preservim/nerdtree'
" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required

" ==================================================================

" Leader.
let mapleader =" "

" Prefer vertical diffsplit
set diffopt=vertical

" Disable auto commenting.
autocmd FileType * setlocal formatoptions-=c formatoptions-=r formatoptions-=o

" Tab definitions.
set tabstop=4 softtabstop=0 expandtab shiftwidth=4

" Extend % matching.
runtime macros/matchit.vim

" Path used for finding files.
set path+=~/gtdev/globaltickdata/source/include

" Convenient command to see the difference between the current buffer and the
" file it was loaded from, thus the changes you made.
" Only define it when not defined already.
if !exists(":DiffOrig")
  command DiffOrig vert new | set bt=nofile | r ++edit # | 0d_ | diffthis | wincmd p | diffthis
endif

syntax on
colorscheme slate

"----------------------------------------------------------------------------
" Mappings ------------------------------------------------------------------
"----------------------------------------------------------------------------

" Quick write.
nnoremap <leader>w :w<cr>

" Disable F1
nmap <F1> <nop>
imap <F1> <nop>

" Let ; do what : does. Conflicts with current line search.
"nnoremap ; :

" Command history. Finger will come to 'k' anyway, so map it to 'k'.
nnoremap <leader>k q:

" Let <leader>/ clear highlights.
set hlsearch
nmap <silent> <leader>/ :nohlsearch<cr>

" Insert lines.
nmap <leader>o o<ESC>k
nmap <leader>O O<ESC>j

" Write as a root.
cmap w!! w !sudo tee % >/dev/null

"----------------------------------------------------------------------------
" Filetype detection --------------------------------------------------------
"----------------------------------------------------------------------------

" Only do this part when compiled with support for autocommands.
if has("autocmd")
  " Enable file type detection.
  " Use the default filetype settings, so that mail gets 'tw' set to 72,
  " 'cindent' is on in C files, etc.
  " Also load indent files, to automatically do language-dependent indenting.
  filetype plugin indent on

  " Put these in an autocmd group, so that we can delete them easily.
  augroup vimrcEx
  au!

  " For all text files set 'textwidth' to 78 characters.
  "autocmd FileType text setlocal textwidth=78

  " When editing a file, always jump to the last known cursor position.
  " Don't do it when the position is invalid or when inside an event handler
  " (happens when dropping a file on gvim).
  " Also don't do it when the mark is in the first line, that is the default
  " position when opening a file.
  autocmd BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g`\"" | endif

  augroup END
else
  set autoindent                " always set autoindenting on
endif " has("autocmd")

"----------------------------------------------------------------------------
" Swap splits with HJKL -----------------------------------------------------
"----------------------------------------------------------------------------
"function! MarkWindowSwap()
"	" marked window number
"	let g:markedWinNum = winnr()
"	let g:markedBufNum = bufnr("%")
"endfunction
"
"function! DoWindowSwap()
"	let curWinNum = winnr()
"	let curBufNum = bufnr("%")
"	" Switch focus to marked window
"	exe g:markedWinNum . "wincmd w"
"
"	" Load current buffer on marked window
"	exe 'hide buf' curBufNum
"
"	" Switch focus to current window
"	exe curWinNum . "wincmd w"
"
"	" Load marked buffer on current window
"	exe 'hide buf' g:markedBufNum
"endfunction

"nnoremap H :call MarkWindowSwap()<cr> <C-w>h :call DoWindowSwap()<cr>
"nnoremap J :call MarkWindowSwap()<cr> <C-w>j :call DoWindowSwap()<cr>
"nnoremap K :call MarkWindowSwap()<cr> <C-w>k :call DoWindowSwap()<cr>
"nnoremap L :call MarkWindowSwap()<cr> <C-w>l :call DoWindowSwap()<cr>

"----------------------------------------------------------------------------
" Netrw ---------------------------------------------------------------------
"----------------------------------------------------------------------------
"function! ToggleVExplorer()
"	if exists("t:expl_buf_num")
"		let expl_win_num = bufwinnr(t:expl_buf_num)
"		if expl_win_num != -1
"			let cur_win_nr = winnr()
"			exec expl_win_num . 'wincmd w'
"			close
"			exec cur_win_nr . 'wincmd w'
"			unlet t:expl_buf_num
"		else
"			unlet t:expl_buf_num
"		endif
"	else
"		exec '1wincmd w'
"		Vexplore
"		let t:expl_buf_num = bufnr("%")
"	endif
"endfunction
"map <silent> <leader>e :call ToggleVExplorer()<cr>

" Netrw size
"let g:netrw_winsize = -28

" Open file on the right split.
"let g:netrw_browse_split = 3 " Open in new tab
"let g:netrw_browse_split = 4 " Open in previous window
"let g:netrw_altv = 1

" netrw tree view.
"let g:netrw_liststyle = 3

" directories on the top, files below.
"let g:netrw_sort_sequence='[\/]$,*'

"----------------------------------------------------------------------------
" tmux navigation -----------------------------------------------------------
"----------------------------------------------------------------------------
if exists('$TMUX')
	function! TmuxOrSplitSwitch(wincmd, tmuxdir)
		let previous_winnr = winnr()
		silent! execute "wincmd " . a:wincmd
		if previous_winnr == winnr()
            let iszoomed = system("tmux list-panes -F '#F' | grep Z | wc -w")
            if iszoomed == 0
			    call system("tmux select-pane -" . a:tmuxdir)
			    redraw!
            endif
		endif
	endfunction

	let previous_title = substitute(system("tmux display-message -p '#{pane_title}'"), '\n', '', '')
	let &t_ti = "\<Esc>]2;vim\<Esc>\\" . &t_ti
	let &t_te = "\<Esc>]2;". previous_title ."\<Esc>\\" . &t_te

	nnoremap <silent> <C-h> :call TmuxOrSplitSwitch('h', 'L')<cr>
	nnoremap <silent> <C-j> :call TmuxOrSplitSwitch('j', 'D')<cr>
	nnoremap <silent> <C-k> :call TmuxOrSplitSwitch('k', 'U')<cr>
	nnoremap <silent> <C-l> :call TmuxOrSplitSwitch('l', 'R')<cr>
else
	map <C-h> <C-w>h
	map <C-j> <C-w>j
	map <C-k> <C-w>k
	map <C-l> <C-w>l
endif

"----------------------------------------------------------------------------
" Cscope --------------------------------------------------------------------
"----------------------------------------------------------------------------
"nmap <C-\>s :cs find s =expand("")
nmap <C-\>s :cs find s <C-R>=expand("<cword>")<cr><cr>
nmap <C-\>c :cs find c <C-R>=expand("<cword>")<cr><cr>

"----------------------------------------------------------------------------
" Bundles -------------------------------------------------------------------
"----------------------------------------------------------------------------

"set tags=~/gtdev/tags,~/.vim/optionlibs.tags,~/.vim/boost.tags
"set notagrelative
"set runtimepath^=~/.vim/bundle/ctrlp.vim
"set runtimepath^=~/.vim/bundle/tagbar
"set runtimepath^=~/.vim/bundle/nerdtree

" Let ,. do CtrlPTag.
"nnoremap <leader>. :CtrlPTag<cr>

" Let ,l to toggle Tagbar.
"nnoremap <silent> <leader>l :TagbarToggle<cr>

" Settings for vim-slime.
"let g:slime_target = 'tmux'
"let g:slime_python_ipython = 1

" Vimux.
"nnoremap <leader>r :call VimuxRunCommand("./" . expand("%:t"))<cr>

" Nerdtree
map <leader>n :NERDTreeToggle<cr>
