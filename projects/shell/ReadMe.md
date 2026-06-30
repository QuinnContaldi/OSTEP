# 🐾 Wish — Dr. Meowra's Unix Shell 🐾

![Dr. Meowra](./Dr.Meowra.jpg)

> *"Nya~! Today we're going to learn how Unix shells work from the inside out!"* — **Dr. Meowra** 🐱

## About

This repository contains my implementation of **Wish (Wisconsin Shell)** from the *Operating Systems: Three Easy Pieces (OSTEP)* projects. I added a few new things to it! Some custom catgirl commands of course. For THE MEOWRA SHELL!!!!!!!!!!!!

The goal isn't simply to create another shell it's to understand how a Unix shell actually works by building one from scratch. Throughout this project, I'll gain hands-on experience with Unix process management, command execution, and many of the core ideas behind modern operating systems.

## Features

- 🐾 Creating child processes with `fork()`
- 🐾 Executing programs with `execv()`
- 🐾 Synchronizing processes using `wait()` and `waitpid()`
- 🐾 Parsing user commands and arguments
- 🐾 Implementing built-in commands (`cd`, `exit`, `path`)
- 🐾 Managing executable search paths
- 🐾 Output redirection (`>`)
- 🐾 Running commands in parallel (`&`)

## Why?

> *"The best way to understand an operating system is to build one tiny piece of it yourself, nya~!"*

Operating systems often feel like magic. This project peels back the curtain by recreating one of the most important Unix programs: the shell.

## Build

```bash
gcc -Wall -Wextra -o wish wish.c
```

## Run

Interactive mode:

```bash
./wish
```

Batch mode:

```bash
./wish batch.txt
```

---

Remember: every segmentation fault is just another opportunity to learn, nya~! 🐈