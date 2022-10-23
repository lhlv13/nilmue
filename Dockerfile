FROM ubuntu:18.04
USER gcc
RUN apt update ** apt upgrade -y
RUN apt install vim
RUN apt install build-essential -y
RUN apt install tmux
RUN apt install python3 -y
RUN apt install python3-pip -y
RUN pip3 install numpy
RUN apt install libjpeg-dev zlib1g-dev -y
RUN pip3 install pillow
RUN apt install libffi-dev libssl-dev
RUN pip3 install matplotlib
VOLUME ["E:/docker/project", "/home/project"]


