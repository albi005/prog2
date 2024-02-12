local dap = require('dap')

local options = "-lm -Wall -std=c11 -g -O0"

dap.configurations.c = {
    {
        name = "Run C program",
        type = "cppdbg",
        request = "launch",
        program = function()
            local cmd
            if string.find(vim.fn.expand('%'), 'nhf') then
                cmd = '!gcc ' .. options .. ' ' .. vim.fn.expand('%:p:h') .. '/*.c'
            else
                cmd = '!gcc ' .. options .. ' "' .. vim.fn.expand('%') .. '"'
            end
            vim.cmd(cmd)
            return '${workspaceFolder}/a.out'
        end,
        cwd = function ()
            if string.find(vim.fn.expand('%'), 'nhf') then
                return '${workspaceFolder}/nhf'
            end
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
    if exists == 1 then
        vim.cmd('!gcc ' .. options .. ' "%" && ./a.out < "' .. input .. '"')
    else
        vim.cmd('!gcc ' .. options .. ' "%" && ./a.out')
    end
end)

-- compile and run in an interactive shell
vim.keymap.set('n', '<Leader>t', function ()
    local cmd
    if string.find(vim.fn.expand('%'), 'nhf') then
        cmd = '!gcc ' .. options .. ' ' .. vim.fn.expand('%:p:h') .. '/*.c'
    else
        cmd = '!gcc ' .. options .. ' "' .. vim.fn.expand('%') .. '"'
    end
    vim.cmd(cmd)

    local dir = vim.fn.expand('%:p:h')

    vim.cmd(':te (cd ' .. dir .. ' && ../a.out)')
end)

--- compile and run SDL2 program
vim.keymap.set('n', '<Leader>s', ':!gcc ' .. options .. ' "%" `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_mixer && ./a.out <CR>', { noremap = true });

vim.keymap.set('n', '<Leader>h', ':ClangdSwitchSourceHeader<CR>');
