FROM	ubuntu:latest


RUN	apt-get update -y && \
	apt-get upgrade -y && \
	apt-get install build-essential git vim -y

RUN git clone https://github.com/42Paris/minilibx-linux mlx && \
	apt-get install libxext-dev -y && \
	apt-get install libbsd-dev -y &&\
	apt-get install libx11-dev -y

RUN	cd mlx; make && ./configure && \
	cp libmlx.a /usr/lib/ && \
	cp mlx.h /usr/include/

RUN apt-get install -y make
WORKDIR /fdf
COPY . .
RUN make
RUN DEBIAN_FRONTEND=noninteractive apt-get install openssh-server sudo -y
RUN mkdir /var/run/sshd
RUN useradd -rm -d /home/ubuntu -s /bin/bash -g root -G sudo -u 1000 test 
RUN  echo 'test:test' | chpasswd
RUN service ssh start
EXPOSE 22
CMD ["/usr/sbin/sshd", "-D"]
