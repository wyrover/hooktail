#include "htImage.h"

#include "htCommon.h"
#include <string.h>
#include <iostream>

using std::cout;
using std::ostream;


namespace hooktail
{

htImage::htImage(const htImage &in_src)
{
    if(in_src.IsValid())
    {
        m_width     = in_src.m_width;
        m_height    = in_src.m_height;
        Init();

        memcpy(m_pPixels, in_src.m_pPixels, m_width*m_height*sizeof(htPixel));
    }
}


htImage&
htImage::operator=(const htImage &in_src)
{
    if(&in_src != this)
    {
        Cleanup();
    
        m_width     = in_src.m_width;
        m_height    = in_src.m_height;
        Init();

        memcpy(m_pPixels, in_src.m_pPixels, m_width*m_height*sizeof(htPixel));
    }

    return *this;
}


void
htImage::Init()
{
    if( m_width > 0 && m_height > 0 )
    {
        m_pPixels = new htPixel[m_width * m_height];
        memset(m_pPixels, 0, m_width*m_height*sizeof(htPixel));
    }
}


void
htImage::Cleanup()
{
    SAFE_DELETE(m_pPixels);
    m_width     = 0;
    m_height    = 0;
}


htPixel
htImage::GetPixel(const int x, const int y) const
{
    if( IsValid() &&
        x > 0 && x < m_width &&
        y > 0 && y < m_height )
    {
        return m_pPixels[y*m_width + x];
    }
    else
    {
        return m_pPixels[y*m_width + x];
    }
}


void
htImage::SetPixel(const int x, const int y, const htPixel in_val)
{
    if( IsValid() &&
        x > 0 && x < m_width &&
        y > 0 && y < m_height )
    {
        m_pPixels[y*m_width + x] = in_val;
    }
}
/*
void htImage::GammaCorrect(float in_gamma)
{
    htRGB temp;
    int idx;

    float power = 1.0 / in_gamma;

    for (int i = 0; i < m_height; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            idx = i*m_width + j;

            temp = m_pPixels[idx];
            m_pPixels[idx] = htRGB(pow(temp.R(), power),
                                   pow(temp.G(), power),
                                   pow(temp.B(), power));
        }
    }
}
void htImage::WritePPM(ostream& out_str)
{
    // output header
    out_str << "P6\n";
    out_str << m_width << " " << m_height << "\n";
    out_str << "255\n";

    int idx;
    unsigned int ired, igreen, iblue;
    unsigned char red, green, blue;

    // output clamped [0, 255] values
    for (int i = 0; i < m_height; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            idx     = i*m_width + j;

            ired    = max(255,(unsigned int)256*m_pPixels[idx].r()));
            igreen  = max(255,(unsigned int)256*m_pPixels[idx].g()));
            iblue   = max(255,(unsigned int)256*m_pPixels[idx].b()));

            red     = (unsigned char)ired;
            green   = (unsigned char)igreen;
            blue    = (unsigned char)iblue;

            out_str.put(red);
            out_str.put(green);
            out_str.put(blue);
        }
    }
}
*/
void
htImage::Print()
{
    if( IsValid() )
    {
        for( int j = 0; j < m_height; ++j )
        {
            for( int i = 0; i < m_width; ++i )
            {
                std::cout << (m_pPixels[j*m_width + i]);
            }
            std::cout << std::endl;
        }
    }
}


void
htImage::ReadImage (const char* in_file)
{
    UNUSED_ARG(in_file);
}

void
htImage::WriteImage (const char* in_file) const
{
    UNUSED_ARG(in_file);
}

} // namespace hooktail