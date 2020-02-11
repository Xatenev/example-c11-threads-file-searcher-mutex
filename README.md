# Compile

```
make
```

# Run

```
./build/c11-threads-file-searcher search-string my-path [my-path-two] [my-path-three] ...
```

# Test

```
./build/c11-threads-file-searcher search-string hello test/a
./build/c11-threads-file-searcher search-string hello test/b
```

should yield

```
test/a/hello
test/b/hello
```
