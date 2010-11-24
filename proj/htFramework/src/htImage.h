#pragma once

#include "htCommon.h"
#include "htRGB.h"

namespace hooktail
{

typedef htRGB<float> htPixel;

class htImage
{
public:
                                        htImage() : m_width(0), m_height(0), m_pPixels(NULL) {}
                                        htImage(const int in_width, const int in_height);
                                        ~htImage() { Cleanup(); }

    htImage(const htImage& src);
    htImage&                            operator= (const htImage& in_src);

    htPixel                             GetPixel(const int x, const int y) const;
    void                                SetPixel(const int x, const int y, const htPixel in_val);

    bool                                IsValid() const { return NULL != m_pPixels; }

    int                                 Width() const { return m_width; }
    int                                 Height() const { return m_height; }

    void                                Print();
    void                                ReadImage (const char* in_file);
    void                                WriteImage (const char* in_file) const;


private:

    void                                Init();
    void                                Cleanup();


    int                                 m_width;
    int                                 m_height;
    htPixel*                            m_pPixels;

};

inline
htImage::htImage(const int in_width, const int in_height)
    : m_width(in_width)
    , m_height(in_height)
{
    Init();
}

} // namespace hooktail