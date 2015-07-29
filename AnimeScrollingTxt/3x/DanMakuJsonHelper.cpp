//
//  DanMakuJsonHelper.cpp
//
//  Created by Rein on 2015/03/26.
//
//

#include "DanMakuJsonHelper.h"
#include "DanMakuData.h"
#include "json/document.h"

DanMakuJsonHelper* DanMakuJsonHelper::createJsonHelper(){
    auto ret = new (std::nothrow) DanMakuJsonHelper();
    if (ret)
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

std::vector<DanMakuData *> DanMakuJsonHelper::parseJson(const char* jsonString){
    std::vector<DanMakuData *> danmakuText;
    
    rapidjson::Document doc;
    doc.Parse<0>(jsonString);
    
    bool error = doc.HasParseError();
    if(error){
        printf("parse error\n");
        return danmakuText;
    }
    
    //弾幕のテキスト解析
    const rapidjson::Value& texts = doc["texts"];
    rapidjson::SizeType num = texts.Size();
    
    for(rapidjson::SizeType i = 0; i < num; i++){
        const rapidjson::Value& textUtil = texts[i];
        
        int textId = textUtil["textid"].GetInt();
        int textType = textUtil["texttype"].GetInt();
        
        const rapidjson::Value& textcolor = textUtil["textcolor"];
        
        double colorR = textcolor["r"].GetDouble();
        double colorG = textcolor["g"].GetDouble();
        double colorB = textcolor["b"].GetDouble();
        
        std::string text = textUtil["text"].GetString();
        
        int postionType = textUtil["positiontype"].GetInt();
        
        double delay = textUtil["delay"].GetDouble();
        
        double textSpeed = textUtil["speed"].GetDouble();
        
        double textsize = textUtil["textsize"].GetDouble();
        
        std::string textfont = textUtil["textfont"].GetString();
        
        std::string username = textUtil["username"].GetString();
        
        auto danmakuData = DanMakuData::create();
        danmakuData->setTextId(textId);
        danmakuData->setTextType((MakuTextType)textType);
        danmakuData->setTextColor(Color3B(colorR, colorG, colorB));
        danmakuData->setTextMessage(text);
        danmakuData->setPositionType((MakuTextPositionType)postionType);
        danmakuData->setDelayTime(delay);
        danmakuData->setTextSpeed(textSpeed);
        danmakuData->setTextFontSize(textsize);
        danmakuData->setTextFontName(textfont);
        danmakuData->setUserName(username);
        
        danmakuText.push_back(danmakuData);
    }
    
    return danmakuText;
}