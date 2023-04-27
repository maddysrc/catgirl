# the catgirl device

there's a catgirl in your kernel what will she do

```sh
./make modules
sudo insmod catgirl.ko
sudo mknod /dev/catgirl c "$(grep catgirl /proc/devices | cut -d' ' -f1)" 0
```
