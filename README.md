# Zash

A wicked fast command-line text editor written in pure C.

## Running

```bash
mkdir build && cd build
cmake ..
make
./zash /path/to/my/file.txt
```

## To Do

- Implement dynamic text buffer
- Properly handle backspaces (not insert a space)
- Handle cursor positioning like normal text editor
- Change window switching key (esc is too slow)
- Add command status to about section
- Scroll lines if window length exceeded
- Scroll columns if window width exceeded
- Load file contents if an existing file is supplied
- Handle UTF-8 encoding

## Down the Road

- Syntax highlighting
- Plugins
