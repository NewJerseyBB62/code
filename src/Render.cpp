#include "SrodRender.h"

#ifdef WIN32
#include <stdio.h>
#include "mediacommon.h"
#include <assert.h>
#include <memory>
#include "SrodError.pb.h"

bool g_enableHardwareAcceleration = false;


SrodRender::InitSDL* SrodRender::InitSDL::getInstance()
{
    static InitSDL obj;
    return &obj;
}
SrodRender::InitSDL::InitSDL()
{
    int nRet = SDL_Init(SDL_INIT_VIDEO);
    if (nRet < 0)
    {
        const char* pszErr = SDL_GetError();
        printf("%s line %d, error:%d %s\n", __FUNCTION__, __LINE__, nRet, pszErr);
        assert(nRet < 0);
    }
    //屏蔽sdl监听windows事件
    //SDL_EventState(SDL_WINDOWEVENT, SDL_IGNORE);
    printf("%s line %d, SDL_INIT_VIDEO success\n", __FUNCTION__, __LINE__);
}
SrodRender::InitSDL::~InitSDL()
{
    SDL_Quit();
}

SrodRender::SdlMutexAutoLock::SdlMutexAutoLock(SDL_mutex* p_sdlMutex)
    : m_sdlMutex(p_sdlMutex)
{
    if (NULL == m_sdlMutex)
        return;

    SDL_LockMutex(m_sdlMutex);
}

SrodRender::SdlMutexAutoLock::~SdlMutexAutoLock()
{
    if (NULL == m_sdlMutex)
        return;

    SDL_UnlockMutex(m_sdlMutex);
}

SrodRender::SrodRender(void* p_playWnd)
    : m_sdlWindow(NULL)
    , m_render(NULL)
    , m_sdlTexture(NULL)
    , m_pRenderDestRect(NULL)
    , m_imageWidth(0)
    , m_imageHeight(0)
    , m_hDisplayWindow(p_playWnd)
    , m_mutex(nullptr)
{
    //InitSDL::getInstance();
}

SrodRender::~SrodRender()
{
    close();
}

int SrodRender::initVideo(void* p_playWnd)
{
    printf("%s line %d, %p HWND:%p sdlWnd:%p\n", __FUNCTION__, __LINE__, this, m_hDisplayWindow, m_sdlWindow);
    while (NULL != m_sdlWindow)
    {
        if (m_hDisplayWindow != p_playWnd)
        {
            close();
            break;
        }

        //SDL_ShowWindow(m_sdlWindow);
        if (NULL == m_render)
            return createRenderer();

        return Srod::Error::SROD_ERR_SUCCESS;
    }
    SDL_Init(SDL_INIT_VIDEO);
    m_mutex = SDL_CreateMutex();
    m_sdlWindow = SDL_CreateWindowFrom(p_playWnd);
    if (NULL == m_sdlWindow)
    {
        const char* pszErr = SDL_GetError();
        printf("%s line %d, %p HWND:%p sdlWindow is Null. %s\n", __FUNCTION__, __LINE__, this, m_hDisplayWindow, pszErr);
        return Srod::Error::SROD_ERR_NOT_OPENED;
    }
    m_hDisplayWindow = p_playWnd;
    SDL_ShowWindow(m_sdlWindow);

    setFullScreenRect(0, 0);
    m_pRenderDestRect = &m_renderFullScreen;

    printf("%s line %d, %p CreateWindowFrom HWND:%p success, sdlWindow:%p\n", __FUNCTION__, __LINE__, this, m_hDisplayWindow, m_sdlWindow);

    int nRet = createRenderer();
    if (Srod::Error::SROD_ERR_SUCCESS != nRet)
        return nRet;

    printf("%s line %d, %p HWND:%p sdlWnd:%p renderer:%p\n", __FUNCTION__, __LINE__, this, m_hDisplayWindow, m_sdlWindow, m_render);
    return Srod::Error::SROD_ERR_SUCCESS;
}

void SrodRender::resizeWindow(int wndWidth, int wndHeight)
{
    LOCK_SDL_MUTEX(m_mutex);
    if (m_sdlWindow != NULL)
        SDL_SetWindowSize(m_sdlWindow, wndWidth, wndHeight);

    //int nWndW, nWndH;
    //int w = 1, h = 1;
    //SDL_GetRendererOutputSize(m_SrodRender, &w, &h);
    //SDL_GetWindowSize(m_sdlWindow, &nWndW, &nWndH);
    //SDL_Rect rect;
    //rect.w = wndWidth;
    //rect.h = wndHeight;
    //SDL_RenderGetViewport(m_SrodRender, &rect);
    //SDL_RenderSetViewport(m_SrodRender, &rect);
    setFullScreenRect(wndWidth, wndHeight);
    setImageScaleRect(m_imageWidth, m_imageHeight);
}

void SrodRender::setFullScreenRect(int w, int h)
{
    if (0 == w || 0 == h)
    {
        SDL_GetWindowSize(m_sdlWindow, &w, &h);
        printf("%s %d %p w:%d h:%d\n", __FUNCTION__, __LINE__, this, w, h);
    }
    m_renderFullScreen.x = 0;
    m_renderFullScreen.y = 0;
    m_renderFullScreen.w = w;
    m_renderFullScreen.h = h;
}
void SrodRender::setImageScaleRect(int w, int h)
{
    if (0 == w || 0 == h)
        return;

    int nWndWidth = 0;
    int nWndHeight = 0;
    SDL_GetWindowSize(m_sdlWindow, &nWndWidth, &nWndHeight);

    int newX = nWndWidth;
    int newY = nWndWidth * h / w;

    m_renderImageScale.x = 0;
    m_renderImageScale.y = (nWndHeight - newY) / 2;
    if (newY > nWndHeight)
    {
        newX = w * nWndHeight / h;
        newY = nWndHeight;

        m_renderImageScale.x = (nWndWidth - newX) / 2;
        m_renderImageScale.y = 0;
    }
    m_renderImageScale.w = newX;
    m_renderImageScale.h = newY;
}

int SrodRender::play(unsigned char** data, int* linesize, int imageWidth, int imageHeight)
{
    if (nullptr == m_sdlWindow)
        initVideo(m_hDisplayWindow);

    LOCK_SDL_MUTEX(m_mutex);
    if (imageWidth != m_imageWidth || imageHeight != m_imageHeight || NULL == m_sdlTexture)
    {
        int nRet = createTexture(imageWidth, imageHeight);
        if (Srod::Error::SROD_ERR_SUCCESS != nRet)
            return nRet;

        m_imageWidth = imageWidth;
        m_imageHeight = imageHeight;
    }

    int nRet = display(data, linesize);
    if (Srod::Error::SROD_ERR_SUCCESS != nRet)
    {
        SDL_DestroyTexture(m_sdlTexture);
        m_sdlTexture = NULL;
        createRenderer();
        return nRet;
    }
    return Srod::Error::SROD_ERR_SUCCESS;
}

int SrodRender::createRenderer()
{
    if (NULL != m_render)
    {
        SDL_DestroyRenderer(m_render);
        m_render = NULL;
    }

    if (g_enableHardwareAcceleration)
    {
        m_render = SDL_CreateRenderer(m_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
        if (NULL == m_render)
        {
            const char* pszErr = SDL_GetError();
            printf("%s line %d, %p CreateRenderer(ACCELERATED) failed.%s\n", __FUNCTION__, __LINE__, this, pszErr);
        }
        else
            printf("%s line %d, %p CreateRenderer(ACCELERATED) success.\n", __FUNCTION__, __LINE__, this);
    }

    if (NULL != m_render)
        return Srod::Error::SROD_ERR_SUCCESS;

    m_render = SDL_CreateRenderer(m_sdlWindow, -1, SDL_RENDERER_SOFTWARE);
    if (NULL == m_render)
    {
        const char* pszErr = SDL_GetError();
        printf("%s line %d, %p CreateRenderer(SOFTWARE) failed. %s\n", __FUNCTION__, __LINE__, this, pszErr);
        return Srod::Error::SROD_ERR_NOT_OPENED;
    }

    printf("%s line %d, %p CreateRenderer(SOFTWARE) success.\n", __FUNCTION__, __LINE__, this);
    return Srod::Error::SROD_ERR_SUCCESS;
}

int SrodRender::createTexture(int imageWidth, int imageHeight)
{
    if (NULL != m_sdlTexture)
    {
        SDL_DestroyTexture(m_sdlTexture);
        m_sdlTexture = NULL;
    }

    setImageScaleRect(imageWidth, imageHeight);

    m_sdlTexture = SDL_CreateTexture(m_render, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, imageWidth, imageHeight);
    if (NULL == m_sdlTexture)
    {
        const char* pszErr = SDL_GetError();
        printf("%s line %d, %p sdlTexture is Null. render:%p %s\n", __FUNCTION__, __LINE__, this, m_render, pszErr);
        return Srod::Error::SROD_ERR_NOT_OPENED;
    }
    printf("%s line %d, %p SDL_CreateTexture success\n", __FUNCTION__, __LINE__, this);
    return Srod::Error::SROD_ERR_SUCCESS;
}

void SrodRender::setStretch(bool p_bStretch)
{
    if (!p_bStretch)
        m_pRenderDestRect = &m_renderImageScale;
    else
        m_pRenderDestRect = &m_renderFullScreen;
}

int SrodRender::display(unsigned char** data, int* linesize)
{
    void* piexels = NULL;
    int pitch;

    int nRet = SDL_LockTexture(m_sdlTexture, NULL, &piexels, &pitch);
    if (nRet < 0)
    {
        const char* pszErr = SDL_GetError();
        printf("%s line %d, %p Texture:%p ret:%d %s\n", __FUNCTION__, __LINE__, this, m_sdlTexture, nRet, pszErr);
        return nRet;
    }
    uint8_t* yuv[3] =
    {
        (uint8_t*)piexels,
        (uint8_t*)piexels + pitch * m_imageHeight,
        (uint8_t*)piexels + pitch* m_imageHeight + ((pitch >> 1) * (m_imageHeight >> 1))
    };

    for (int i = 0; i < m_imageHeight; i++)
    {
        memcpy(yuv[0] + i * pitch, data[0] + i * linesize[0], linesize[0]);
        if (i % 2 == 0)
        {
            memcpy(yuv[1] + (i >> 1) * (pitch >> 1), data[2] + (i >> 1) * linesize[2], linesize[2]);
            memcpy(yuv[2] + (i >> 1) * (pitch >> 1), data[1] + (i >> 1) * linesize[1], linesize[1]);
        }
    }

    SDL_UnlockTexture(m_sdlTexture);
    nRet = SDL_RenderClear(m_render);
    if (0 != nRet)
    {
        const char* pszErr = SDL_GetError();
        printf("%s line %d, %p ret:%d %s\n", __FUNCTION__, __LINE__, this, nRet, pszErr);
        return nRet;
    }

    //nRet = SDL_RenderCopy(m_SrodRender, m_sdlTexture, NULL, m_pRenderDestRect);
    nRet = SDL_RenderCopyEx(m_render, m_sdlTexture, NULL, m_pRenderDestRect, 0, NULL, SDL_FLIP_NONE);
    if (0 != nRet)
    {
        const char* pszErr = SDL_GetError();
        printf("%s line %d, %p ret:%d %s\n", __FUNCTION__, __LINE__, this, nRet, pszErr);
        return nRet;
    }

    SDL_RenderPresent(m_render);
    return 0;
}

void SrodRender::close()
{
    //SDL_CloseAudio();
    if (nullptr != m_sdlTexture)
    {
        SDL_DestroyTexture(m_sdlTexture);
        m_sdlTexture = nullptr;
    }
    if (nullptr != m_render)
    {
        SDL_DestroyRenderer(m_render);
        m_render = nullptr;
    }
    if (nullptr != m_sdlWindow)
    {
        SDL_HideWindow(m_sdlWindow);
        SDL_DestroyWindow(m_sdlWindow);
        m_sdlWindow = nullptr;
    }
    if (nullptr != m_mutex)
    {
        SDL_DestroyMutex(m_mutex);
        m_mutex = nullptr;
    }

    //SDL_Quit();
    //m_hDisplayWindow = 0;
    m_pRenderDestRect = NULL;
    m_imageWidth = 0;
    m_imageHeight = 0;
}

#endif

