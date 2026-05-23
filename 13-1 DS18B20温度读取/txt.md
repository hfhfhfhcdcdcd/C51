![alt text](image.png)

![alt text](image-1.png)

![alt text](image-2.png)

之前一直读不出来，是因为onewire的Onewire_receivebit函数写错啦。里面应该先把Onewire线释放，然后再读线上的数据。之前错是先读数据，再释放线。所以一直读不出来。