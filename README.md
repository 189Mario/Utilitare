# Utilitare

## Overview
Utilitare is a small personal project that brings together a set of utility functions written in C. It is structured around several distinct tasks, each targeting a specific feature—such as parsing command-line arguments, listing directory contents, determining the common directory between two paths, and generating the shortest edit script between two files. The sections below provide a detailed overview of each task and explain how the core functions interact to deliver the project’s overall functionality.

## Table of Contents

- [Overview](#overview)

- [Tasks](#tasks)

  - [Task 1: Command-line Argument Parser](#task-1-command-line-argument-parser)

  - [Task 2: Directory Listing Utility](#task-2-directory-listing-utility)

  - [Task 3: Relative Directory Computation](#task-3-relative-directory-computation)

  - [Task 4: Shortest Edit Script Generator](#task-4-shortest-edit-script-generator)

## Tasks

### Task 1: Command-line Argument Parser
Task 1 is designed to process and sort the command-line inputs provided to the program. It categorizes the inputs into three types:

1. **Arguments** – Non‑numeric strings or data inputs that are not options or flags.

2. **Options** – Command‑line options that usually come with a numeric value. They can be presented in:

   - **Long Form**: e.g., `--option=value`

   - **Short Form**: e.g., `-o value`

3. **Flags** – Boolean toggles that indicate a state (e.g., activated with `-f` or `--flag`).

- **Task 1 Function:**
  - `populare()` - Makes a list that contains organized information about each argument

The rest is being done in main where the values that need to be found for the specified arguments will be found within the structure made by populare().

### Task 2: Directory Listing Utility
Task 2 implements a directory listing feature. It non‑recursively scans the contents of a directory and prints a hierarchical list of files and subdirectories including their sizes. This is achieved with:

- **dirent** functions (`opendir`, `readdir`, `closedir`) to iterate over directory entries.

- **sys/stat** (`stat`, `lstat`) to get file metadata, such as file size.

- **Task 2 Functions:**

  - `printType()`, `free_list()`, `long_int_to_string()` - Sugestive enough names

  - `creaza_lista()` - Makes a list for each directory

  - `sorteaza_lista()` - Sorts the alredy created lists

  - `output_r()` - Makes the output recursively, and frees the memory

### Task 3: Relative Directory Computation
Task 3 computes the longest common directory between two paths. These functions work in unison to tokenize path strings and then compare tokens to find the common base.

- **Task 3 Functions:**
  - `find_parent_for_relative_path()` -Sugestive name

  - `creare_output_3()` – Makes the output

### Task 4: Shortest Edit Script Generator

Task 4 generates a shortest edit script that details the differences between two files. Its functions integrate file I/O, string processing, and an external edit distance algorithm.

- **Task 4 Function:**
  - `task4()` - Uses a matrix that is initially 0's and 1's (1's where there can be made a match). We then start from the bottom right corner and update it recursively such that each 1 is updated into the value of all the posible matches that can be made if we go through that place. After that we start from the top left corner and find I,D and R.

For more info visit the site:[sitePA](https://site-pa.netlify.app/proiecte/director_fisiere/)
