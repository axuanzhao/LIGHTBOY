

#ifndef __AIP_FACE_H__
#define __AIP_FACE_H__

#include "base/base.h"

namespace aip {

    class Face: public AipBase
    {
    public:
        
        std::string _detect =
            "https://aip.baidubce.com/rest/2.0/face/v2/detect";
        
        std::string _match =
            "https://aip.baidubce.com/rest/2.0/face/v2/match";
        
        std::string _identify =
            "https://aip.baidubce.com/rest/2.0/face/v2/identify";
        
        std::string _verify =
            "https://aip.baidubce.com/rest/2.0/face/v2/verify";
        
        std::string _user_add =
            "https://aip.baidubce.com/rest/2.0/face/v2/faceset/user/add";
        
        std::string _user_update =
            "https://aip.baidubce.com/rest/2.0/face/v2/faceset/user/update";
        
        std::string _user_delete =
            "https://aip.baidubce.com/rest/2.0/face/v2/faceset/user/delete";
        
        std::string _user_get =
            "https://aip.baidubce.com/rest/2.0/face/v2/faceset/user/get";
        
        std::string _group_getlist =
            "https://aip.baidubce.com/rest/2.0/face/v2/faceset/group/getlist";
        
        std::string _group_getusers =
            "https://aip.baidubce.com/rest/2.0/face/v2/faceset/group/getusers";
        
        std::string _group_adduser =
            "https://aip.baidubce.com/rest/2.0/face/v2/faceset/group/adduser";
        
        std::string _group_deleteuser =
            "https://aip.baidubce.com/rest/2.0/face/v2/faceset/group/deleteuser";
        

        Face(const std::string & app_id, const std::string & ak, const std::string & sk): AipBase(app_id, ak, sk)
        {
        }

        std::string vector_join_base64(const std::vector<std::string> & v_images) {
            std::string images;
            size_t count = v_images.size();
            for (size_t i = 0; i < count;i++)
            {
                std::string image = v_images[i];
                images += base64_encode(image.c_str(), (int) image.size());
                if (i != count) {
                    images += ",";
                }

            }
            return images;
        }
        
      
        Json::Value detect(
            std::string const & image,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["image"] = base64_encode(image.c_str(), (int) image.size());

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_detect, null, data, null);

            return result;
        }
        
       
        Json::Value match(
            const std::vector<std::string> & images,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["images"] = vector_join_base64(images);

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_match, null, data, null);

            return result;
        }
        
    
        Json::Value identify(
            std::string const & group_id,
            std::string const & image,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["group_id"] = group_id;
            data["image"] = base64_encode(image.c_str(), (int) image.size());

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_identify, null, data, null);

            return result;
        }
        

        Json::Value verify(
            std::string const & uid,
            std::string const & image,
            std::string const & group_id,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["uid"] = uid;
            data["image"] = base64_encode(image.c_str(), (int) image.size());
            data["group_id"] = group_id;

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_verify, null, data, null);

            return result;
        }
        
    
        Json::Value user_add(
            std::string const & uid,
            std::string const & user_info,
            std::string const & group_id,
            std::string const & image,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["uid"] = uid;
            data["user_info"] = user_info;
            data["group_id"] = group_id;
            data["image"] = base64_encode(image.c_str(), (int) image.size());

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_user_add, null, data, null);

            return result;
        }
        
     
        Json::Value user_update(
            std::string const & uid,
            std::string const & image,
            std::string const & user_info,
            std::string const & group_id,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["uid"] = uid;
            data["image"] = base64_encode(image.c_str(), (int) image.size());
            data["user_info"] = user_info;
            data["group_id"] = group_id;

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_user_update, null, data, null);

            return result;
        }
        

        Json::Value user_delete(
            std::string const & uid,
            std::string const & group_id,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["uid"] = uid;
            data["group_id"] = group_id;

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_user_delete, null, data, null);

            return result;
        }
   
        Json::Value user_get(
            std::string const & uid,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["uid"] = uid;

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_user_get, null, data, null);

            return result;
        }
        

        Json::Value group_getlist(
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_group_getlist, null, data, null);

            return result;
        }
        

        Json::Value group_getusers(
            std::string const & group_id,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["group_id"] = group_id;

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_group_getusers, null, data, null);

            return result;
        }
    
        Json::Value group_adduser(
            std::string const & group_id,
            std::string const & uid,
            std::string const & src_group_id,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["group_id"] = group_id;
            data["uid"] = uid;
            data["src_group_id"] = src_group_id;

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_group_adduser, null, data, null);

            return result;
        }
      
        Json::Value group_deleteuser(
            std::string const & group_id,
            std::string const & uid,
            const std::map<std::string, std::string> & options)
        {
            std::map<std::string, std::string> data;
            
            data["group_id"] = group_id;
            data["uid"] = uid;

            std::copy(options.begin(), options.end(), std::inserter(data, data.end()));

            Json::Value result =
                this->request(_group_deleteuser, null, data, null);

            return result;
        }
        
    };
}
#endif
