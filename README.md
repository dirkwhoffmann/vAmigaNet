
<p align="center">
  <div><img src="https://dirkwhoffmann.github.io/vAmiga/images/va-net-banner-1.png"></div>
</p>

# Installation istructions

```bash
# Clone the project
git clone https://github.com/dirkwhoffmann/vAmigaNet.git

# Install components
cd vAmigaNet 
npm install

# Setup a build directory
mkdir wasm
emcmake cmake -S cpp -B build

# Build the WASM part
cd wasm
make -j

# Option 1: Run a local build
cd ..
npm run dev

# Option 2: Deploy
npm run build
```
