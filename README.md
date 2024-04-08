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
- Load file contents if an existing file is supplied
- Handle character deletions correctly
- Add command status to about section
- Scroll lines if window length exceeded
- Scroll columns if window width exceeded
