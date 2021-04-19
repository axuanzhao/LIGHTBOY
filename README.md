<!--Project-->
<h2 align="center">LIGHT BOY </h2>  
<p align="center">
  <a href="https://github.com/axuanzhao/LIGHTBOY">
    <img src="Images/logo.png" alt="Logo">
  </a>
  
  <p align="center">
    Intelligent body sensing LED via Raspberry Pi 
    <br />
</div>

<p align="center">
  <a href="https://twitter.com/LightBo30129343">
    <img src="Images/twitter.png" alt="Twitter"  width="64" height="64">
  </a>
  <a href="https://www.youtube.com/channel/UCQwc7ckxd-EJKTK4yuo6-4g">
    <img src="Images/youtube.png" alt="YouTube"  width="64" height="64">
  </a>
  <a href="https://www.instagram.com/lightboy_2021/">
    <img src="Images/instagram.png" alt="Instagram"  width="64" height="64">
  </a>
  
  
<!-- Contents -->
## Table Of Contents

<ol>
    <li><a href="#Description">Description</a></li>
    <li><a href="#getting-started">Getting Started</a></li>
      <ul>
      <li><a href="#hardware">hardware</a</li>
        <li><a href="#software">software</a</li>
      </ul>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#Lightboy">Lightboy</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
</ol>


<!--Description-->
## Description
Raspberry Pi can make your home smarter. It's the equivalent of adding a small computer to the home system to act as the brain of the home system. Taking lighting system as an example, in order to make home lighting more convenient, a Raspberry Pi based body sensing led with controllable switching time can be turned on and off through the Web UI interface and set into automatic mode, in which specific working time period can be set. At the same time, the voice recognition function controls the light on, for the user to bring a more intelligent experience. Make indoor lighting control more convenient. The project is mainly divided into three parts. The first part is the use of sensors. LED automatically lights up after sensing human movement through infrared sensors. The second part is the multi-threaded part, which controls the LED through the web page. The third part is speech recognition, call Baidu API for speech to text recognition, the recognition of the command for lighting control. At the same time, we can also control the lights through Siri.

<!--getting-started-->
## Getting-started
In order to successfully run the next program, you need to prepare the software and hardware in advance.

<!--hardware-->
### `hardware`
1.A Raspberry Pi 4B  
2.A infrared sensor (HC-SR501)  
3.A microphone with USB interface  
4.A breadboard and wires  
5.LEDs
<img src="https://user-images.githubusercontent.com/78051838/115126853-120d3e00-9fca-11eb-9d82-3e28bb1365fa.png" width="70%" height="70%">

<!--software-->
### `software`
Geany,WinSCP,Putty,VNC viewer,VSCODE.
The part of the software installation is omitted, you can go to the official website to download it yourself.


<!--usage-->
## Usage
<!--sense-light-->
### `sense-light`
Hardware setup can be found in the folder /SenseLight/circuit-diagram.

Before compiling this project, we need some software packages installed on the Raspberry Pi(besides the basic development tools such as gcc, etc.).
Required libraries:
* WiringPi(GPIO access library)

      sudo apt-get install wiringpi

* glog(Google logging)

      sudo apt-get install libgoogle-glog-dev

* libconfig(Configuration File Library)

      sudo apt-get install libconfig-dev

* gtest(Google's C++ test)

      sudo apt-get install libgtest-dev

After seeting up the environment, use following commands:

    cd ~/LIGHTBOY/SenseLight
    make
    make install
    cd deploy/script
switch into root before run the programm

    ./run-timer-sense-light.sh

The lights can be controlled from webpage. To do that, use a browser to visit the webpage. (Assume the ip address of my RaspberryPi is 100.76.149.76.) There are three modes, ON, OFF, and Auto. When in AUTO mode, time interval where the sense-light operates can be set.

<img src="https://user-images.githubusercontent.com/77740843/115274329-70582f00-a138-11eb-9703-20c5ceae0e1a.png" width="50%" height="50%">



<!--Speech Recognition-->
### `Speech Recognition`

Required Libraries  
* curl

      sudo apt-get install libcurl4-openssl-dev
      
* Jsoncpp

      sudo apt-get install libjsoncpp-dev
      
* OpenSSL

      wget https://www.openssl.org/source/openssl-1.1.1d.tar.gz
      tar zxf openssl-1.1.1d.tar.gz
      cd openssl-1.1.1d
      ./config --prefix=/usr/local/openssl --openssldir=/usr/local/openssl 
      make -j4 && make install
Then,we need to set up the microphone  

      sudo apt-get -y  install  alsa-utils   pulseseaudio
      arecord  -L

 After seeting up the environment, use following commands:
 
       cd /usr/code/sdk-demo-master/speech/cpp
       sudo su
       ./main
      
Then the device could record your words and recognize it into English words,then run commands and control lights.


<!--contributing-->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!--license-->
## License

Distributed under the  Apache-2.0 License. See `LICENSE` for more information.

<!--contact-->
## Contact

[Xuan Zhao](https://github.com/axuanzhao)
<br />
[Fangxin Tan](https://github.com/FangxinTan)
<br />
[Shengning Zhang](https://github.com/ShengningZ)
<br />
Project : [https://github.com/axuanzhao/Voice-Recognition-Controlling](https://github.com/axuanzhao/Voice-Recognition-Controlling)
