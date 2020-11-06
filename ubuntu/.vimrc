"
" This file works for both vim and gvim.
"
" ===============
" DEFAULT OPTIONS
" ===============
" set nocompatible
" source $VIMRUNTIME/vimrc_example.vim
" source $VIMRUNTIME/mswin.vim
" behave mswin
"
" set diffexpr=MyDiff()
" function MyDiff()
"   let opt = ''
"   if &diffopt =~ 'icase' | let opt = opt . '-i ' | endif
"   if &diffopt =~ 'iwhite' | let opt = opt . '-b ' | endif
"   silent execute '!"C:\Program Files\vim\vim62\diff" -a ' . opt . '"' . v:fnam
" endfunction

" ===========
" GUI OPTIONS
" ===========

set guifont=6x13-ISO8859-1:h10
set guioptions-=T
set guioptions+=b
set guicursor=a:block-Cursor-blinkon0
highlight Normal guifg=black guibg=gray
highlight Search guibg=NONE
highlight Visual guifg=NONE guibg=NONE

" disable colors (this will also disable matching brace highlighting if set to 0)
" set t_Co=0

" ================
" STANDARD OPTIONS
" ================

" turn off syntax highlighting
syntax off

" turn off file type detection
filetype off

" fix the backspace key (broke when running linux xterms through Reflection X)
"if $ARCH == "linux"
"    set t_kb=
"    fixdel
"endif

" do not wrap lines
set nowrap

" support reading all file formats
set fileformats=unix,dos,mac

" report all line changes
set report=0

" allow backspace over start of insert
set backspace=indent,eol

" complete to longest match and list on second <TAB>
set wildmode=longest,list

" list of default tags files to load
set tags=~/.tags

" do not wrap through top/bottom of buffer when searching
set nowrapscan

" jump to currently matched text as it is typed in search
set incsearch

" searching is case insensitive, except when search contains upper case
set ignorecase
set smartcase

" do not highlight the search target
set nohlsearch

" do not load functionality for matching brackets/parenthesis/braces
let loaded_matchparen = 1

" always display a status bar and use normal-inverse video display
set laststatus=2
set highlight=sr

" text on status line
function TabFormat ()
    if &softtabstop == 4
        return "4S"
    elseif &softtabstop == 2
        return "2S"
    elseif &tabstop == 8
        return "8T"
    elseif &tabstop == 4
        return "4T"
    elseif &tabstop == 2
        return "2T"
    else
        return "??"
    endif
endfunction
set statusline=%F\ %m%r%h%=%v(%c):%l\ [%n]\ [%{TabFormat()}]

" ===============
" INDENT OPTION 1
" ===============
" virtual tabstops using spaces
set shiftwidth=4
set softtabstop=4
set expandtab
" ===============
" INDENT OPTION 2
" ===============
" tabs stops at 4
"set tabstop=4
"set shiftwidth=4

" allow moving away from a modified file (note, this is dangerous)
set hidden


" ================
" PRIVATE MAPPINGS
" ================

" F1 and F2 go to matching close and open (respectively) braces
nmap <F1> 0f{%
nmap <F2> 0f}%

" F3 and F4 set and unset (respectively) line wrapping mode
nmap <F3> :set wrap<CR>
nmap <F4> :set nowrap<CR>

" F5 offers formatting options (tabs versus spaces)
function CheckResponse (response, default, alternate, error)
    if a:response == ""
        return a:default
    elseif a:response == a:default
        return a:response
    elseif a:response == a:alternate
        return a:response
    else
        return a:error
    endif
endfunction
function PromptFormat ()
    normal mz
    let tabs = input ("Tabs? [*y*/n]: ")
    let tabs = CheckResponse (tabs, "y", "n", "?")
    if tabs == "?"
        echo " "
        echo "please enter \"y\" or \"n\""
        return
    endif
    let width = input ("Width? [8]: ")
    if tabs == "y"
        if width == ""
            let width = 8
        endif
        if &expandtab
            set softtabstop=0
            set noexpandtab
        endif
        execute "set tabstop=".width
        execute "set shiftwidth=".width
    else
        execute "set softtabstop=".width
        execute "set shiftwidth=".width
        set expandtab
    endif
    execute "normal \<C-L>"
endfunction
nmap <F5> :execute PromptFormat()<CR>

" F6 and F7 move forward and backward (respectively) through the buffers
nmap <F6> :bprevious!<CR>
nmap <F7> :bnext!<CR>

" F8 opens up the :edit command and inserts the path to the current buffer
nmap <F8> :edit <C-R>=expand("%:p:h")."/"<CR>

" F9 runs clang-format on the current file
nmap <F9> :%py3file /usr/share/vim/addons/syntax/clang-format.py<CR>

" put C-style preprocessor comments around a line of code
nmap <C-x> O#ifdef TBD<Esc>jo#endif // TBD<Esc>0

" in command mode, C-a and C-k shift the current line right and left
" (respectively) by 4 spaces...in normal mode, C-a and C-k add or subtract
" (respectively) 4 spaces to the current line
nmap <C-a> 0i<Space><Space><Space><Space><Esc>0
nmap <C-k> 04x
imap <C-a> <Esc>A<Space><Space><Space><Space><Esc>A
imap <C-k> <Esc>3h4xA
