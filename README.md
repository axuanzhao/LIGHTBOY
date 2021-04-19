<!--Project-->
<h2 align="center">LIGHT BOY </h2>  
<p align="center">
  <a href="https://github.com/axuanzhao/Voice-Recognition-Controlling">
    <img src="Images/logo.png" alt="Logo">
  </a>
  
  <p align="center">
    Sensory light powered by intelligent voice recognition via Raspberry Pi 
    <br />
</div>

<p align="center">
  <a href="https://twitter.com/lightboyofficial">
    <img src="Images/twitter.png" alt="Twitter"  width="64" height="64">
  </a>
  <a href="https://www.youtube.com/channel/UCQwc7ckxd-EJKTK4yuo6-4g">
    <img src="Images/youtube.png" alt="YouTube"  width="64" height="64">
  </a>
  <a href="https://www.instagram.com/lightboy_2021/">
    <img src="Images/instagram.png" alt="Instagram"  width="64" height="64">
  </a>
  
  
<!-- Contents -->
## Contents

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
Raspberry Pi can make the home smarter. With the Raspberry Pi, it is the equivalent of adding a small computer to the home system to act as the brain of the home system. Take the lighting system for example, in order to make the home lighting more convenient, we implement the function of voice recognition to control the lighting through the Raspberry Pi, and the user's movement can be sensed through the sensors, and the lights will automatically turn on when the user enters the room and other actions. Bringing a smarter experience for the user. Making room lighting control more convenient.
The project is carried out in three parts, the first part is speech recognition, calling the Baidu API for speech-to-text recognition of speech, and the recognized commands are used for lighting control. The second part is the use of sensors, sensing human movement through infrared sensors. The third part is the multi-threaded control, which allows the use of sensors and the control of voice recognition to take place simultaneously.

<!--getting-started-->
## Getting-started
Turn on the Equipment  
Run the program and speak/move in front of the LightBoy  
Then it works as your order  
When you move in front of the sensor(some particular position in your room),the light turns on itself

<!--hardware-->
### `hardware`
1.A Raspberry Pi 4B  
2.LEDS  
3.A microphone with USB interface  
4.A breadboard and wires  
5.A infrared sensor  
<img src="https://user-images.githubusercontent.com/78051838/115126853-120d3e00-9fca-11eb-9d82-3e28bb1365fa.png" width="40%" height="40%">
<!--software-->
### `software`
Geany,Jsoncpp,WinSCP,Putty,VNC viewer,VisualStudioGDB.


<!--usage-->
## Usage
### `sense light`
For timer-sense-light, use following commands:

    cd /LIGHTBOY/gpio/timer-sense-light/deploy/script
    ./run-timer-sense-light.sh

The lights can be controlled from webpage. To do that, use a browser to visit the webpage. (Assume the ip address of my RaspberryPi is 100.76.149.76.)


<!--lightboy-->
## Lightboy



<!--contributing-->
## Contributing

See `CONTRIBUTING` for more information.

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
