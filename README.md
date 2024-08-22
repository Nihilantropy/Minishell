# Minishell: aka Minihell :fire:!

Welcome to Minihell, your very own journey into the magical world of command-line interfaces! 
🌟 Imagine it as your personal little bash, crafted from scratch, and, like all things small and wonderful, it’s as beautiful as a shell.

## 🐚 Project Overview

Minihell is a project that lets you create a basic yet functional shell, akin to the one you use every day but with a twist: it’s your creation!
You’ll dive deep into the inner workings of processes, file descriptors, and command execution.
By the end of this adventure, you’ll have your own shell that mimics many of the features of bash, but with your unique touch.

## Why Build a Shell?

Once upon a time, developers communicated with computers by flipping 1/0 switches. This wasn’t
just tedious—it was downright frustrating! So, they invented something more human: the shell. It
allowed them to interact with computers using commands typed in plain (well, sort of) English. With
Minihell, you’ll step into their shoes, tackling the challenges they faced before the days of Windows 
and fancy GUIs.

## 🎯 The Mission

Your task is to create a shell that can:

1. **Display a Prompt**: When it’s time for a new command, your shell will ask politely.

2. **Handle History**: Like a good friend, your shell remembers what you’ve said before.

3. **Execute Commands**: Whether it’s finding an executable in your PATH or running something
	by absolute path, your shell’s got you covered.

4. **Signal Handling**: It’s tough to avoid global variables, but try to use just one for signal handling.
	It’s like a tiny flag your shell waves when something important happens.

5. **Quotes and Meta-Characters**: Your shell understands the power of quotes (single ' and double "), and it won’t misinterpret them.

6. **Redirections**: <, >, <<, and >> – these symbols have special meanings, and your shell knows them all.

7. **Pipes**: Your shell will expertly pass the output of one command to the input of another, just like bash.

8. **Environment Variables**: $VARIABLES are magical tokens that your shell will expand to their corresponding values.

9. **Exit Status**: $? tells the story of the last command’s success or failure.

10. **Interactive Mode**: In the heat of command-line battle, your shell handles ctrl-C, ctrl-D, and ctrl-\ with grace, just like bash.

## 🛠️ Builtin Commands

Minihell will also support several built-in commands, including:

- [x] echo (with -n option)

- [x] cd (change directory)

- [x] pwd (print working directory)

- [x] export (set environment variables)

- [x] unset (unset environment variables)

- [x] env (print environment)

- [x] exit (close the shell)

## ⚙️ Bonus Challenges

Once you’ve perfected the essentials, take on these bonus tasks:

- [ ] **Logical Operators**: Implement **&&** and **||** for command chaining, with support for parentheses to dictate priority.

- [ ] **Wildcards**: Allow **\*** to match files in the current directory, adding a bit of flair to your command execution.

## 🚀 Getting Started

### Prerequisites

 - Ensure you’re working in a Unix-like environment.

 - Install the necessary libraries and headers for readline.

 ### Installation

To get your Minihell up and running:

```bash
make
```

### Usage

Fire up your shell:

```bash
./minihell
```

From here, you can start typing commands, exploring directories, and even writing small scripts to see how your shell handles them.

### Testing

While testing is not mandatory, it’s highly encouraged! Creating tests will help you understand
how your shell behaves in various scenarios and is incredibly helpful during peer evaluations.

## 📜 Final Submission

When you’re done crafting your Minihell, submit your work to your assigned Git repository.
Double-check everything because only what’s in your repo will be graded!

If you are just a C programmer enthusiast... Great job! Upload it to your GitHub and see
if you can get any reviews!

## 👥 Peer Evaluations

After submission, you’ll participate in peer evaluations. This is your chance to see how your
peers approached the same challenge and to show off your own work. The more thorough and fair you
are in these evaluations, the better the feedback you’ll receive.

## Conclusion

Congratulations on embarking on this shell-building adventure! We hope you enjoy every bit of 
it and walk away with a deeper understanding of how shells work under the hood.

May your code be bug-free and your shell flawless!

Happy hacking! 🎉

## Leave a stra :star:!

If you'd like to see an in-depth analisy of this code, leave a star to let us know! :love_letter: