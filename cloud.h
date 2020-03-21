#ifndef SMOOTHLY_CLOUD
#define SMOOTHLY_CLOUD
#include <irrlicht/irrlicht.h>
#include <time.h>
#include <string>
namespace smoothly{

class cloud{
    public:
        cloud(irr::video::IVideoDriver  * d,irr::scene::ISceneManager * s);
        irr::f32 cloudThre, // 云量，越大云越少
                 cloudy,    // 阴天
                 lightness; // 亮度
        irr::core::vector3df astronomical,//发光天体位置
                             astrLight,   //亮度
                             astrColor;   //天体颜色
        float                astrAtomScat,//大气层散射
                             astrTheta;   //天体在视野中夹角
    private:
        irr::video::IVideoDriver  * driver;
        irr::scene::ISceneManager * scene;
        struct skyBox{
            irr::video::IVideoDriver  * driver;
            irr::scene::ISceneManager * scene;
            irr::video::SMaterial cloudMaterial;
            irr::video::ITexture * cloudTop;
            irr::video::ITexture * cloudFront;
            irr::video::ITexture * cloudBack;
            irr::video::ITexture * cloudLeft;
            irr::video::ITexture * cloudRight;
            irr::scene::ISceneNode * box;
            void(*callback[80])(skyBox *);
            int count;
            bool first;
            void init(const std::string &name, irr::s32 cloud);
            bool process();
        };
        skyBox * sky_p , * sky_pb;
        skyBox sky_1,sky_2;
        class CloudShaderCallback:public irr::video::IShaderConstantSetCallBack{//shader回调
            public:
                cloud * parent;
                void OnSetConstants(irr::video::IMaterialRendererServices * services, irr::s32 userData)override;
        }cloudShaderCallback;
        irr::s32 cloudTime;
        void renderSky();
};

}
#endif // SMOOTHLY_ENGINE
