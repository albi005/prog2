local dap = require('dap')

local options = "-g -D MEMTRACE -D DEBUG -O0 -U _FORTIFY_SOURCE --std=c++11"

dap.configurations.cpp = {
    {
        name = "Run C++ program",
        type = "cppdbg",
        request = "launch",
        program = function()
            local dir = vim.fn.expand('%:p:h')
            local cmd = '!TARGET=a.out make --environment-overrides --directory ' .. dir
            vim.cmd(cmd)
            return dir .. "/a.out"
        end,
        cwd = function()
            local dir = vim.fn.expand('%:p:h')
            return dir
        end,
        stopAtEntry = false,
        setupCommands = {
            {
                text = '-enable-pretty-printing',
                description =  'enable pretty printing',
                ignoreFailures = false
            },
        },
    },
}

dap.adapters.cppdbg = {
    id = 'cppdbg',
    type = 'executable',
    command = os.getenv'OPEN_DEBUG_PATH',
}

-- compile and run, pass in input if it exists
vim.keymap.set('n', '<Leader>r', function ()
    local dir = vim.fn.expand('%:h')
    local cmd = '!g++ ' .. options .. ' '.. dir .. '/*.cpp && ./a.out'
    vim.cmd(cmd)
end)

-- compile and run in an interactive shell
vim.keymap.set('n', '<Leader>t', function ()
    local cmd
    cmd = '!g++ ' .. options .. ' "' .. vim.fn.expand('%') .. '"'
    vim.cmd(cmd)

    local dir = vim.fn.expand('%:p:h')

    vim.cmd(':te (cd ' .. dir .. ' && ../a.out)')
end)

vim.keymap.set('n', '<Leader>h', ':ClangdSwitchSourceHeader<CR>');
vim.keymap.set('n', '<Leader>c', "ggvG:s/ / /g"); -- &nbsp babyyyyyyyyyyyyy
