# stb_image_wrapper

Python bindings for [stb_image.h](https://github.com/nothings/stb) and stb_image_write.h.

## Features
- Load images into NumPy arrays
- Save images as PNG or JPEG
- Minimal dependencies, cross-platform

## Installation
```bash
pip install .
```

## Example
```python
import stb_image_wrapper as si
img = si.load_image("example.png")
print(img.shape)
si.save_png("out.png", img)
si.save_jpg("out.jpg", img, quality=80)
```
