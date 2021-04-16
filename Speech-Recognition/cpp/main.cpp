// C++SDK root
#include "/usr/code/sdk-demo-master/speech/aip-cpp-sdk-4.15.4/speech.h"
#include "stdio.h"
#include "unistd.h"
#include "wiringPi.h"
#include "string.h"
void ASR(aip::Speech* client);

void ASR_url(aip::Speech* client);

void TTS(aip::Speech* client);

int main()
{
    // 
    aip::Speech * client = new aip::Speech("23982791", "F1PcszoB1OGDhwlXma3xh8PY", "PkO5RuUiPo2Tp3rvH1ku5PGcW8niDoOd");
    system("arecord -D \"plughw:1,0\" -d 3 -f S16_LE -r 16000 -c 1 -t wav temp.wav"); 
//    sleep(5);
    system("ffmpeg -y  -i temp.wav  -acodec pcm_s16le -f s16le -ac 1 -ar 16000 16k.pcm");
  //  sleep(1);
    // 
    client->setDebug(false);
    wiringPiSetup();
//    softPwmCreate(1,0,100);    
    // sppech recognition
    ASR(client);

    // sppech recognition
    TTS(client);

    
    
    // 
   // TTS(client);

    
    return 0;
}

/**
 * ASR
 */
int cur_light=100;
void ASR(aip::Speech* client) {
    std::map<std::string, std::string> options;
    std::string file_content;
    aip::get_file_content("./16k.pcm", &file_content);
    std::map<std::string, std::string> options1;
    options1["lan"] = "en";
    Json::Value result = client->recognize(file_content, "pcm",16000, options1);
    std::cout << "speech recognition:" << std::endl << result.toStyledString();

    pinMode(1,PWM_OUTPUT);
    if(strstr(result.toStyledString().c_str(),"turn on")!=NULL)
    {
      pwmWrite(1,1024);
      cur_light=1024;
    }
    else  if(strstr(result.toStyledString().c_str(),"turn off")!=NULL)
{
pwmWrite(1,0);
cur_light=0;
}
else if(strstr(result.toStyledString().c_str(),"light up")!=NULL)
{
if(cur_light>=724)
{ 
cur_light =1024;
}
else
{ 
cur_light+=300;
}
 pwmWrite(1,cur_light);
}
else if(strstr(result.toStyledString().c_str(),"light down")!=NULL)
{ 
if(cur_light>=300)
{
cur_light -=300;
}
else
{
cur_light=0;
}
 pwmWrite(1,cur_light);

}
else
{
   std::cout << "FAILED" << std::endl << result.toStyledString();
}
   // pwmWrite(1,1024);

   // pwmWrite(1,100);
}

/**
 * ASR
 */
void ASR_PRO(aip::Speech* client) {
    std::map<std::string, std::string> options;
    std::string file_content;
    aip::get_file_content("../assets/16k_test.pcm", &file_content);
    Json::Value result = client->recognize(file_content, "pcm", 16000, options);
    std::cout << "check local file:" << std::endl << result.toStyledString();
}

/**
 * TTs
 */
void TTS(aip::Speech* client) {
    std::ofstream ofile;
    std::string file_ret;
    std::map<std::string, std::string> options;
    options["spd"] = "5";
    options["per"] = "2";
    ofile.open("./tts.mp3", std::ios::out | std::ios::binary);
    Json::Value result = client->text2audio("hello world", options, file_ret);
    // 
    if (!file_ret.empty())
    {
        // save file
        ofile << file_ret;
        std::cout << "success，open tts.mp3" << std::endl;
    } else {
        // error， print info
        std::cout << result.toStyledString();
    }
}
