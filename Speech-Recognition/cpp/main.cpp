// 请替换您下载的C++SDK路径
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
    // 务必替换百度云控制台中新建百度语音应用的 Api Key 和 Secret Key
    aip::Speech * client = new aip::Speech("23982791", "F1PcszoB1OGDhwlXma3xh8PY", "PkO5RuUiPo2Tp3rvH1ku5PGcW8niDoOd");
    system("arecord -D \"plughw:1,0\" -d 3 -f S16_LE -r 16000 -c 1 -t wav temp.wav"); 
//    sleep(5);
    system("ffmpeg -y  -i temp.wav  -acodec pcm_s16le -f s16le -ac 1 -ar 16000 16k.pcm");
  //  sleep(1);
    // 打印详细请求结果，可以打开查看详细请求内容
    client->setDebug(false);
    wiringPiSetup();
//    softPwmCreate(1,0,100);    
    // 语音识别调用
    ASR(client);

    // 语音识别调用
    TTS(client);

    
    
    // 语音识别极速版调用
   // TTS(client);

    
    return 0;
}

/**
 * ASR语音识别示例
 */
int cur_light=100;
void ASR(aip::Speech* client) {
    std::map<std::string, std::string> options;
    std::string file_content;
    aip::get_file_content("./16k.pcm", &file_content);
    std::map<std::string, std::string> options1;
    options1["lan"] = "en";
    Json::Value result = client->recognize(file_content, "pcm",16000, options1);
    std::cout << "语音识件结果:" << std::endl << result.toStyledString();

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
 * ASR语音识别极速版示例
 */
void ASR_PRO(aip::Speech* client) {
    std::map<std::string, std::string> options;
    std::string file_content;
    aip::get_file_content("../assets/16k_test.pcm", &file_content);
    Json::Value result = client->recognize(file_content, "pcm", 16000, options);
    std::cout << "识别极速版本地文件结果:" << std::endl << result.toStyledString();
}

/**
 * TTS语音合成示例
 */
void TTS(aip::Speech* client) {
    std::ofstream ofile;
    std::string file_ret;
    std::map<std::string, std::string> options;
    options["spd"] = "5";
    options["per"] = "2";
    ofile.open("./tts.mp3", std::ios::out | std::ios::binary);
    Json::Value result = client->text2audio("hello world", options, file_ret);
    // 如果file_ret为不为空则说明合成成功，返回mp3文件内容
    if (!file_ret.empty())
    {
        // 合成成功保存文件
        ofile << file_ret;
        std::cout << "语音合成成功，打开目录下的tts.mp3文件听听看" << std::endl;
    } else {
        // 合成出错，打印错误信息
        std::cout << result.toStyledString();
    }
}
