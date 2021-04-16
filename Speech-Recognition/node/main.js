let AipSpeech = require("baidu-aip-sdk").speech;
let fs = require('fs');

// Baidu Yun Api Key And Secret Key
let client = new AipSpeech(0, '请填写Api Key', '请填写Secret Key');

let voice = fs.readFileSync('../assets/16k_test.pcm');

let voiceBase64 = new Buffer(voice);

// recognise local file
client.recognize(voiceBase64, 'pcm', 16000).then(function(result) {
    console.log('recognize local speech result: ' + JSON.stringify(result));
}, function(err) {
    console.log(err);
});

// recognize remote sppech
client.recognizeByUrl('http://bos.nj.bpc.baidu.com/v1/audio/8k.amr', 'http://yq01-ecom-holmes22-20150818112825.yq01.baidu.com:8492/aip/dump', 'amr', 8000).then(function(result) {
    console.log('recognize remote speech: ' + JSON.stringify(result));
}, function(err) {
    console.log(err);
});

// speech synthesis 
client.text2audio('', {spd: 0, per: 4}).then(function(result) {
    if (result.data) {
        console.log('speech synthesis success，save to tts.mp3，open it');
        fs.writeFileSync('tts.mp3', result.data);
    } else {
        // 合成服务发生错误
        console.log('failed: ' + JSON.stringify(result));
    }
}, function(err) {
    console.log(err);
});

