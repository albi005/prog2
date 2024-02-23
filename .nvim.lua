local dap = require('dap')

local options = "-g -D MEMTRACE -O0 -U _FORTIFY_SOURCE"

-- TODO: set up debugging
dap.configurations.cpp = {
    {
        name = "Run C++ program",
        type = "cppdbg",
        request = "launch",
        program = function()
            local dir = vim.fn.expand('%:h')
            local cmd = '!g++ ' .. options .. ' '.. dir .. '/*.cpp'
            vim.cmd(cmd)
            return '${workspaceFolder}/a.out'
        end,
        cwd = function ()
            return '${workspaceFolder}'
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
    local input = vim.fn.expand('%:r') .. '.in'
    local exists = vim.fn.filereadable(input)
    local dir = vim.fn.expand('%:h')
    local cmd = '!g++ ' .. options .. ' '.. dir .. '/*.cpp && ./a.out'
    if exists == 1 then
        vim.cmd(cmd .. ' < "' .. input .. '"')
    else
        vim.cmd(cmd)
    end
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
vim.keymap.set('n', '<Leader>c', ":'<,'>s/ / /g"); -- &nbsp babyyyyyyyyyyyyy
