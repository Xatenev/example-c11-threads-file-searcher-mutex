# C11 threads and mutexes

Illustrating the use of C11 threads and mutexes by recursively searching a directory for filenames.

## Compile

```
make
```

## Run

```
./build/xfs search-string my-path [my-path-two] [my-path-three] ...
```

## Test

```
./build/xfs hello test
```
or
```
./build/xfs hello test/a test/b
```

should yield

```
test/a/hello
test/b/hello
```
