//=====================================================================
// Copyright (c) 2007-2014    Advanced Micro Devices, Inc. All rights reserved.
// Copyright (c) 2004-2006    ATI Technologies Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//=====================================================================

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <string>
#include <cstring>

#include "UseDefinitions.h"
#include "Compressonator.h"

using namespace std;

#pragma warning( push )
#pragma warning(disable:4244)
#include "half.h"
#pragma warning( pop )

#ifndef CMP_MAKEFOURCC
#define CMP_MAKEFOURCC(ch0, ch1, ch2, ch3)                              \
   ((CMP_DWORD)(CMP_BYTE)(ch0) | ((CMP_DWORD)(CMP_BYTE)(ch1) << 8) |   \
   ((CMP_DWORD)(CMP_BYTE)(ch2) << 16) | ((CMP_DWORD)(CMP_BYTE)(ch3) << 24 ))
#endif

typedef half                 CMP_HALF;   ///< A 16-bit floating point number class

#define QT_KEY_SPACE        0x20        // Qt::Key_Space = 0x20
#define QT_KEY_M            0x4d        // Qt::Key_M = 0x4d

#define UNREFERENCED_PARAMETER(P) (P)

typedef struct
{
    double    SSIM;            // Structural Similarity Index: Average of RGB Channels
    double    SSIM_Red;
    double    SSIM_Green;
    double    SSIM_Blue;

    double    PSNR;            // Peak Signal to Noise Ratio: Average of RGB Channels
    double    PSNR_Red;
    double    PSNR_Green;
    double    PSNR_Blue;

    double    MSE;             // Mean Square Error

} CMP_ANALYSIS_DATA;


struct CMP_CMIPS
{
    // User Configurable Print lines 
    int m_infolevel = 1;
    void PrintError(const char* Format, ... );
    void(*PrintLine)(char *) = nullptr;
    void Print(const char* Format, ...);

    CMP_MipLevel* GetMipLevel(const CMP_MipSet* pMipSet, CMP_INT nMipLevel, CMP_INT nFaceOrSlice=0);

    int  GetMaxMipLevels(CMP_INT nWidth, CMP_INT nHeight, CMP_INT nDepth);

    bool AllocateMipLevelTable(CMP_MipLevelTable** ppMipLevelTable, CMP_INT nMaxMipLevels, CMP_TextureType textureType, CMP_INT nDepth, CMP_INT& nLevelsToAllocate);

    bool AllocateAllMipLevels(CMP_MipLevelTable* pMipLevelTable, CMP_TextureType /*textureType*/, CMP_INT nLevelsToAllocate);

    bool AllocateMipSet(CMP_MipSet* pMipSet, CMP_ChannelFormat channelFormat, CMP_TextureDataType textureDataType, CMP_TextureType textureType, CMP_INT nWidth, CMP_INT nHeight, CMP_INT nDepth);

    bool AllocateMipLevelData(CMP_MipLevel* pMipLevel, CMP_INT nWidth, CMP_INT nHeight, CMP_ChannelFormat channelFormat, CMP_TextureDataType textureDataType);
    bool AllocateCompressedMipLevelData(CMP_MipLevel* pMipLevel, CMP_INT nWidth, CMP_INT nHeight, CMP_DWORD dwSize);

    void FreeMipSet(CMP_MipSet* pMipSet);

    bool AllocateCompressedDestBuffer(CMP_MipSet *SourceTexture, CMP_FORMAT format, CMP_MipSet *DestTexture);

    // Progress
    bool m_canceled = false;
    void(*SetProgressValue)(unsigned int, bool *canceled) = nullptr;
    void SetProgress(unsigned int value);

};

#define MAX_MIPLEVEL_SUPPORTED 20
#define MIPSET_PIN_DATA_ID     "69AEBDB3-5F67-436D-82C2-724FDC4972DA"

typedef CMP_CMIPS   CMIPS;


extern void(*PrintStatusLine)(char *);
extern void PrintInfo(const char* Format, ...);

#define MINIMUM_WEIGHT_VALUE 0.01f

#define AMD_CODEC_QUALITY_DEFAULT 0.05f  ///< This is the default value set for all Codecs (Gives fast Processing and lowest Quality)
#define AMD_CODEC_EXPOSURE_DEFAULT 0     ///< This is the default value set for exposure value of hdr/exr input image
#define AMD_CODEC_DEFOG_DEFAULT 0        ///< This is the default value set for defog value of hdr/exr input image
#define AMD_CODEC_KNEELOW_DEFAULT 0      ///< This is the default value set for kneelow value of hdr/exr input image
#define AMD_CODEC_KNEEHIGH_DEFAULT 5     ///< This is the default value set for kneehigh value of hdr/exr input image
#define AMD_CODEC_GAMMA_DEFAULT 2.2f     ///< This is the default value set for gamma value of hdr/exr input image

#define CMP_MESH_COMP_LEVEL 7         ///< This is the default value set for draco compress level for mesh compression
#define CMP_MESH_POS_BITS 14          ///< This is the default value set for draco position quantization bits for mesh compression
#define CMP_MESH_TEXC_BITS 12         ///< This is the default value set for draco texture coordinate quantization bits for mesh compression
#define CMP_MESH_NORMAL_BITS 10       ///< This is the default value set for draco normal quantization bits for mesh compression
#define CMP_MESH_GENERIC_BITS 8       ///< This is the default value set for draco generic quantization bits for mesh compression

#ifdef USE_3DMESH_OPTIMIZE
#define CMP_MESH_VCACHE_SIZE_DEFAULT 16       ///< This is the default value set for vertices cache size for mesh optimization
#define CMP_MESH_VCACHEFIFO_SIZE_DEFAULT 0    ///< This is the default value set for vertices FIFO cache size for mesh optimization
#define CMP_MESH_OVERDRAW_ACMR_DEFAULT 1.05f  ///< This is the default value set for ACMR(average cache miss ratio) for mesh overdraw optimization
#define CMP_MESH_SIMPLIFYMESH_LOD_DEFAULT 0   ///< This is the default value set for LOD(level of details) for mesh simplication.
#define CMP_MESH_OPTVFETCH_DEFAULT 1          ///< This is the default boolean value set for vertices fetch mesh optimization.
#endif

#define CMP_MIPSET_MAX_DEPTHS            6       ///< Maximum Depth (CubeMap Frames) for each MipSet

struct CMP_MAP_BYTES_SET
{
    CMP_BYTE B0;
    CMP_BYTE B1;
    CMP_BYTE B2;
    CMP_BYTE B3;
};

typedef enum _CodecType
{
    CT_Unknown = 0,
    CT_None,
    CT_DXT1,
    CT_DXT3,
    CT_DXT5,
    CT_DXT5_xGBR,
    CT_DXT5_RxBG,
    CT_DXT5_RBxG,
    CT_DXT5_xRBG,
    CT_DXT5_RGxB,
    CT_DXT5_xGxR,
    CT_ATI1N,
    CT_ATI2N,
    CT_ATI2N_XY,
    CT_ATI2N_DXT5,
    CT_ATC_RGB,
    CT_ATC_RGBA_Explicit,
    CT_ATC_RGBA_Interpolated,
    CT_ETC_RGB,
#ifdef SUPPORT_ETC_ALPHA
    CT_ETC_RGBA_Explicit,
    CT_ETC_RGBA_Interpolated,
#endif // SUPPORT_ETC_ALPHA
    CT_ETC2_RGB,
    CT_ETC2_SRGB,
    CT_ETC2_RGBA,
    CT_ETC2_RGBA1,
    CT_ETC2_SRGBA,
    CT_ETC2_SRGBA1,
    CT_BC6H,
    CT_BC6H_SF,
    CT_BC7,
    CT_ASTC,
    CT_GTC,
#ifdef USE_BASIS
    CT_BASIS,
#endif
    CODECS_AMD_INTERNAL
} CodecType;

typedef enum _CODECError
{
    CE_OK = 0,
    CE_Unknown,
    CE_Aborted,
} CodecError;



#endif  // !COMMON_H
