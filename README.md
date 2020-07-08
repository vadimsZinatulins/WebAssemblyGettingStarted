# WebAssemblyGettingStarted
First project of WebAssmebly

## Compile canvas.cpp
```
emcc .\lib\canvas.cpp -s WASM=1 -s EXPORTED_FUNCTIONS="['_main', '_getCircles']" -o .\public\canvas.js
```

## Run project
```
npm start
```