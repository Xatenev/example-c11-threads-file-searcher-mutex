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
./build/c11-threads-file-searcher hello test
or 
./build/c11-threads-file-searcher hello test/a test/b
```

should yield

```
test/a/hello
test/b/hello
```
