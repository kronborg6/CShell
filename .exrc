let s:cpo_save=&cpo
set cpo&vim
inoremap <C-G>S <Plug>(nvim-surround-insert-line)
inoremap <C-G>s <Plug>(nvim-surround-insert)
inoremap <silent> <M-j> <Cmd>ToggleTerm
cnoremap <silent> <Plug>(TelescopeFuzzyCommandSearch) e "lua require('telescope.builtin').command_history { default_text = [=[" . escape(getcmdline(), '"') . "]=] }"
inoremap <C-W> u
inoremap <C-U> u
nnoremap <silent>  :TmuxNavigateLeft
nnoremap <silent> <NL> :TmuxNavigateDown
nnoremap <silent>  :TmuxNavigateUp
nnoremap <silent>  :TmuxNavigateRight
nmap  d
nnoremap <silent>  :TmuxNavigatePrevious
nnoremap  gs <Cmd>Telescope git_status
nnoremap  gfc <Cmd>Telescope git_bcommits
nnoremap <silent>  bb <Cmd>Telescope jumplist
nnoremap <silent>  fb 
nnoremap  fgc <Cmd>Telescope git_commits
nnoremap  fh <Cmd>Telescope harpoon marks
nnoremap    <Cmd>Telescope buffers
nnoremap  fo <Cmd>Telescope oldfiles
nnoremap  er <Cmd>NvimTreeRefresh
nnoremap  ec <Cmd>NvimTreeCollapse
nnoremap  ef <Cmd>NvimTreeFindFileToggle
nnoremap  ee <Cmd>NvimTreeToggle
nnoremap  gb <Cmd>Telescope git_branches
nnoremap  z :tabe %
nnoremap  bc :DBUIToggle
nnoremap  p "0p
nnoremap  th :ToggleTerm size=15 direction=horizontal name=desktop
nnoremap  tf :ToggleTerm size=10 direction=float name=floating terminal
xnoremap  p "0p
nnoremap  nv :vnew
nnoremap  l :wincmd l
nnoremap  h :wincmd h
nnoremap  v :vsplitl
omap <silent> % <Plug>(MatchitOperationForward)
xmap <silent> % <Plug>(MatchitVisualForward)
nmap <silent> % <Plug>(MatchitNormalForward)
nnoremap & :&&
xnoremap <silent> <expr> @ mode() ==# 'V' ? ':normal! @'.getcharstr().'' : '@'
xnoremap <silent> <expr> Q mode() ==# 'V' ? ':normal! @=reg_recorded()' : 'Q'
xnoremap S <Plug>(nvim-surround-visual)
nnoremap Y y$
omap <silent> [% <Plug>(MatchitOperationMultiBackward)
xmap <silent> [% <Plug>(MatchitVisualMultiBackward)
nmap <silent> [% <Plug>(MatchitNormalMultiBackward)
omap <silent> ]% <Plug>(MatchitOperationMultiForward)
xmap <silent> ]% <Plug>(MatchitVisualMultiForward)
nmap <silent> ]% <Plug>(MatchitNormalMultiForward)
xmap a% <Plug>(MatchitVisualTextObject)
nnoremap cS <Plug>(nvim-surround-change-line)
nnoremap cs <Plug>(nvim-surround-change)
nnoremap ds <Plug>(nvim-surround-delete)
xnoremap gS <Plug>(nvim-surround-visual-line)
omap <silent> g% <Plug>(MatchitOperationBackward)
xmap <silent> g% <Plug>(MatchitVisualBackward)
nmap <silent> g% <Plug>(MatchitNormalBackward)
nmap gcu <Plug>Commentary<Plug>Commentary
xmap gr <Plug>ReplaceWithRegisterVisual
nmap grr <Plug>ReplaceWithRegisterLine
nmap gr <Plug>ReplaceWithRegisterOperator
omap gc <Plug>Commentary
nmap gcc <Plug>CommentaryLine
xmap gc <Plug>Commentary
nmap gc <Plug>Commentary
nnoremap ySS <Plug>(nvim-surround-normal-cur-line)
nnoremap yS <Plug>(nvim-surround-normal-line)
nnoremap yss <Plug>(nvim-surround-normal-cur)
nnoremap ys <Plug>(nvim-surround-normal)
xmap <silent> <Plug>(MatchitVisualTextObject) <Plug>(MatchitVisualMultiBackward)o<Plug>(MatchitVisualMultiForward)
onoremap <silent> <Plug>(MatchitOperationMultiForward) :call matchit#MultiMatch("W",  "o")
onoremap <silent> <Plug>(MatchitOperationMultiBackward) :call matchit#MultiMatch("bW", "o")
xnoremap <silent> <Plug>(MatchitVisualMultiForward) :call matchit#MultiMatch("W",  "n")m'gv``
xnoremap <silent> <Plug>(MatchitVisualMultiBackward) :call matchit#MultiMatch("bW", "n")m'gv``
nnoremap <silent> <Plug>(MatchitNormalMultiForward) :call matchit#MultiMatch("W",  "n")
nnoremap <silent> <Plug>(MatchitNormalMultiBackward) :call matchit#MultiMatch("bW", "n")
onoremap <silent> <Plug>(MatchitOperationBackward) :call matchit#Match_wrapper('',0,'o')
onoremap <silent> <Plug>(MatchitOperationForward) :call matchit#Match_wrapper('',1,'o')
xnoremap <silent> <Plug>(MatchitVisualBackward) :call matchit#Match_wrapper('',0,'v')m'gv``
xnoremap <silent> <Plug>(MatchitVisualForward) :call matchit#Match_wrapper('',1,'v'):if col("''") != col("$") | exe ":normal! m'" | endifgv``
nnoremap <silent> <Plug>(MatchitNormalBackward) :call matchit#Match_wrapper('',0,'n')
nnoremap <silent> <Plug>(MatchitNormalForward) :call matchit#Match_wrapper('',1,'n')
nmap <silent> <Plug>CommentaryUndo :echoerr "Change your <Plug>CommentaryUndo map to <Plug>Commentary<Plug>Commentary"
nnoremap <silent> <M-j> <Cmd>execute v:count . "ToggleTerm"
nnoremap <Plug>PlenaryTestFile :lua require('plenary.test_harness').test_file(vim.fn.expand("%:p"))
nnoremap <silent> <C-Bslash> :TmuxNavigatePrevious
nnoremap <silent> <Plug>ReplaceWithRegisterVisual :call setline('.', getline('.'))|execute 'silent! call repeat#setreg("\<Plug>ReplaceWithRegisterVisual", v:register)'|call ReplaceWithRegister#SetRegister()|if ReplaceWithRegister#IsExprReg()|    let g:ReplaceWithRegister#expr = getreg('=')|endif|execute 'normal!' ReplaceWithRegister#VisualMode()|call ReplaceWithRegister#Operator('visual', "\<Plug>ReplaceWithRegisterVisual")
vnoremap <silent> <Plug>ReplaceWithRegisterVisual :call setline('.', getline('.'))|execute 'silent! call repeat#setreg("\<Plug>ReplaceWithRegisterVisual", v:register)'|call ReplaceWithRegister#SetRegister()|if ReplaceWithRegister#IsExprReg()|    let g:ReplaceWithRegister#expr = getreg('=')|endif|call ReplaceWithRegister#Operator('visual', "\<Plug>ReplaceWithRegisterVisual")
nnoremap <silent> <Plug>ReplaceWithRegisterLine :call setline('.', getline('.'))|execute 'silent! call repeat#setreg("\<Plug>ReplaceWithRegisterLine", v:register)'|call ReplaceWithRegister#SetRegister()|if ReplaceWithRegister#IsExprReg()|    let g:ReplaceWithRegister#expr = getreg('=')|endif|call ReplaceWithRegister#SetCount()|execute 'normal! V' . v:count1 . "_\<Esc>"|call ReplaceWithRegister#Operator('visual', "\<Plug>ReplaceWithRegisterLine", 1)
nnoremap <silent> <Plug>ReplaceWithRegisterExpressionSpecial :let g:ReplaceWithRegister#expr = getreg('=')|execute 'normal!' v:count1 . '.'
nnoremap <expr> <Plug>ReplaceWithRegisterOperator ReplaceWithRegister#OperatorExpression()
nnoremap <silent> <C-K> :TmuxNavigateUp
nnoremap <silent> <C-J> :TmuxNavigateDown
nnoremap <silent> <C-H> :TmuxNavigateLeft
nmap <C-W><C-D> d
nnoremap <silent> <C-L> :TmuxNavigateRight
inoremap S <Plug>(nvim-surround-insert-line)
inoremap s <Plug>(nvim-surround-insert)
inoremap  u
inoremap  u
inoremap jk 
inoremap jj 
let &cpo=s:cpo_save
unlet s:cpo_save
set clipboard=unnamedplus
set cmdheight=0
set completeopt=menu,menuone,noselect
set expandtab
set grepformat=%f:%l:%c:%m
set grepprg=rg\ --vimgrep\ -uu\ 
set helplang=en
set nohlsearch
set isfname=#,$,%,+,,,-,.,/,48-57,=,@,_,~,@-@
set noloadplugins
set operatorfunc=<SNR>16_go
set packpath=/tmp/.mount_nvimJUYgpb/usr/share/nvim/runtime
set runtimepath=~/.config/nvim,~/.local/share/nvim/lazy/lazy.nvim,~/.local/share/nvim/lazy/nvim-surround,~/.local/share/nvim/lazy/nvim-colorizer.lua,~/.local/share/nvim/lazy/nvim-autopairs,~/.local/share/nvim/lazy/friendly-snippets,~/.local/share/nvim/lazy/cmp_luasnip,~/.local/share/nvim/lazy/LuaSnip,~/.local/share/nvim/lazy/lspkind.nvim,~/.local/share/nvim/lazy/cmp-path,~/.local/share/nvim/lazy/cmp-buffer,~/.local/share/nvim/lazy/nvim-cmp,~/.local/share/nvim/lazy/vim-commentary,~/.local/share/nvim/lazy/fine-cmdline.nvim,~/.local/share/nvim/lazy/toggleterm.nvim,~/.local/share/nvim/lazy/nvim-ts-autotag,~/.local/share/nvim/lazy/nvim-treesitter,~/.local/share/nvim/lazy/nvim-notify,~/.local/share/nvim/lazy/nui.nvim,~/.local/share/nvim/lazy/noice.nvim,~/.local/share/nvim/lazy/telescope-ui-select.nvim,~/.local/share/nvim/lazy/telescope-fzf-native.nvim,~/.local/share/nvim/lazy/telescope.nvim,~/.local/share/nvim/lazy/nvim-tree.lua,~/.local/share/nvim/lazy/nvim-web-devicons,~/.local/share/nvim/lazy/lualine.nvim,~/.local/share/nvim/lazy/nvim-nio,~/.local/share/nvim/lazy/nvim-dap-virtual-text,~/.local/share/nvim/lazy/nvim-dap-ui,~/.local/share/nvim/lazy/nvim-dap-go,~/.local/share/nvim/lazy/nvim-dap,~/.local/share/nvim/lazy/plenary.nvim,~/.local/share/nvim/lazy/harpoon,~/.local/share/nvim/lazy/inc-rename.nvim,~/.local/share/nvim/lazy/cmp-nvim-lsp,~/.local/share/nvim/lazy/omnisharp-extended-lsp.nvim,~/.local/share/nvim/lazy/typescript.nvim,~/.local/share/nvim/lazy/nvim-lspconfig,~/.local/share/nvim/lazy/none-ls.nvim,~/.local/share/nvim/lazy/mason-null-ls.nvim,~/.local/share/nvim/lazy/mason-lspconfig.nvim,~/.local/share/nvim/lazy/mason.nvim,~/.local/share/nvim/lazy/vim-tmux-navigator,~/.local/share/nvim/lazy/vim-ReplaceWithRegister,~/.local/share/nvim/lazy/catppuccin,/tmp/.mount_nvimJUYgpb/usr/share/nvim/runtime,/tmp/.mount_nvimJUYgpb/usr/share/nvim/runtime/pack/dist/opt/matchit,/tmp/.mount_nvimJUYgpb/usr/lib/nvim,~/.local/state/nvim/lazy/readme,~/.local/share/nvim/lazy/cmp_luasnip/after,~/.local/share/nvim/lazy/cmp-path/after,~/.local/share/nvim/lazy/cmp-buffer/after,~/.local/share/nvim/lazy/cmp-nvim-lsp/after,~/.local/share/nvim/lazy/catppuccin/after
set scrolloff=8
set shiftwidth=4
set showtabline=0
set softtabstop=4
set splitbelow
set splitright
set statusline=%#Normal#
set tabstop=4
set termguicolors
set updatetime=50
set window=41
" vim: set ft=vim :
