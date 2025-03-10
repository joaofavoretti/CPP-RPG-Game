#!/usr/bin/env bash

# Start a tmux session named 'dev'
tmux new-session -d -s dev

# Rename the window to 'editor' and start nvim in the src directory
tmux rename-window -t dev:0 'editor'
tmux send-keys -t dev:0 'cd src; nvim .' C-m

# Split the window horizontally and start a terminal in the src directory
tmux split-window -v -t dev:0 -p 10
tmux send-keys -t dev:0.1 'cd src' C-m

# Split the right pane vertically and start a terminal in the build directory
tmux split-window -h -t dev:0.1
tmux send-keys -t dev:0.2 'cd build' C-m

# Attach to the tmux session
tmux attach-session -t dev
