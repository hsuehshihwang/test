# doxygen usage

---


## Installaition

```bash
sudo apt update
sudo apt install -y doxygen graphviz
```

---

## Simple Sample for HTML output

```bash
doxygen -g Doxyfile
```

**Doxyfile**
```bash
PROJECT_NAME           = MyProject
OUTPUT_DIRECTORY       = docs
RECURSIVE              = YES
GENERATE_HTML          = YES
GENERATE_LATEX         = NO
EXTRACT_ALL            = YES
INPUT                  = ./src ./include
HAVE_DOT               = YES
CALL_GRAPH             = YES
CALLER_GRAPH           = YES
```




