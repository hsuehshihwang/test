# Xvfb testing

---

## Quick Start

- [Ralph's Github test - Xvfb](https://github.com/hsuehshihwang/test/tree/main/Xvfb)
- Install `docker.ce` or `docker.io`
- Run the following scripts.

```bash
./build.sh
./run.sh
docker ps -a
CONTAINER ID   IMAGE             COMMAND            CREATED         STATUS         PORTS     NAMES
e00a8c88f801   xvfb-nginx-rtmp   "/entrypoint.sh"   8 minutes ago   Up 8 minutes             xvfb-nginx-rtmp
```

- Use macbook's finder to connect vnc server as below 
    - [vnc://192.168.2.33:5900](vnc://192.168.2.33:5900) / pwd: `12345`
    - :exclamation: Change 192.168.2.33 to your docker PC IP
- Use web browser to open player
    - [http://192.168.2.33:8080/player](http://192.168.2.33:8080/player)
    - :exclamation: Change 192.168.2.33 to your docker PC IP


