# Inverted Search

A C-based command-line tool that performs inverted indexing and search on a set of text files.

## Features
- Builds an inverted index from .txt files
- Searches for keywords across files
- Uses hash table for fast lookups

## Files
- main.c, create_database.c, search.c, etc. — source code
- *.txt — input text files
- file.sh — script file

## How to Compile
bash
gcc *.c -o inverted_search
