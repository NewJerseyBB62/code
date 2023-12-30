#ifndef _SRODRENDER_H_
#define _SRODRENDER_H_

extern bool g_enableHardwareAcceleration;

#ifdef WIN32

#include "SDL.h"
#include <memory>


class SrodRender
{
private:
    class InitSDL
    {
    public:
        static InitSDL* getInstance();
        ~InitSDL();
    private:
        InitSDL();
    };

    class SdlMutexAutoLock
    {
    public:
        SdlMutexAutoLock(SDL_mutex* p_sdlMutex);

        virtual ~SdlMutexAutoLock();
    private:
        SDL_mutex* m_sdlMutex;
    };

#define  LOCK_SDL_MUTEX(mutex)	SdlMutexAutoLock obj_##mutex(mutex)
public:
    SrodRender(void* p_playWnd);
    virtual ~SrodRender(void);

    int initVideo(void* p_playWnd);
    void resizeWindow(int p_wndWidth, int p_wndHeight);
    void setStretch(bool p_bStretch);

    int play(unsigned char** p_data, int* p_linesize, int p_imageWidth, int p_imageHeight);

    void close();

private:
    int createRenderer();
    int createTexture(int p_imageWidth, int p_imageHeight);
    int display(unsigned char** p_data, int* p_linesize);

    void setFullScreenRect(int p_w, int p_h);
    void setImageScaleRect(int p_w, int p_h);

private:
    void*           m_hDisplayWindow;   //�ⲿ���ھ��
    SDL_mutex*		m_mutex;
    SDL_Window*		m_sdlWindow;    //��Ⱦ����
    SDL_Renderer*	m_render;    //��Ⱦ��
    SDL_Texture*	m_sdlTexture;   //����

    int				m_imageWidth;   //ͼ����
    int				m_imageHeight;  //ͼ��߶�

    SDL_Rect		m_renderImageScale; //ͼ�����
    SDL_Rect		m_renderFullScreen; //ȫ��
    SDL_Rect*		m_pRenderDestRect;
};

#endif


#endif //_SRODRENDER_H_