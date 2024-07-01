# VKSM
Vulkan Shader Mixer. A short program to combine a vertex shader and a fragment shader into one file. It works with glslc and can be easily modified

## Installation
Run `./build.sh`, requires G++17 or greater

## Usage
`-f` tells `vksm` what file to compile<br/>
`-v` prints debug info <br/><br/>

The first line defines the name of the shaders<br/>
`#vert` defines the beginning of a vertex shader<br/>
`~` defines the end of a vertex shader<br/>
`#frag` defines the beginning of a fragment shader<br/>
Anything before `#vert` gets included in both shaders<br/><br/>

Due to the end of a fragment shader also being the end of a file, there is no need to put a `~` at the end of the fragment shader.

## Example
`example_shader/example.glsl`
