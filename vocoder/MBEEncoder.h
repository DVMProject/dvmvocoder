// SPDX-License-Identifier: GPL-2.0-only
/*
 * Digital Voice Modem - MBE Vocoder
 * GPLv2 Open Source. Use is subject to license terms.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 *  Copyright (C) 2019-2021 Doug McLain
 *  Copyright (C) 2021 Bryan Biedenkapp, N2PLL
 *
 */
/**
 * @file MBEEncoder.h
 * @ingroup vocoder
 * @file MBEEncoder.cpp
 * @ingroup vocoder
 */
#if !defined(__MBE_ENCODER_H__)
#define __MBE_ENCODER_H__

#include "Defines.h"
#include "mbe.h"
#include "imbe/imbe_vocoder.h"

#include <stdint.h>

namespace vocoder
{
    // ---------------------------------------------------------------------------
    //  Constants
    // ---------------------------------------------------------------------------

    /**
     * @brief Vocoder Encoding Mode
     */
    enum MBE_ENCODER_MODE {
        ENCODE_DMR_AMBE,    //! DMR AMBE
        ENCODE_88BIT_IMBE,  //! 88-bit IMBE (P25)
    };

    // ---------------------------------------------------------------------------
    //  Class Declaration
    // ---------------------------------------------------------------------------

    /**
     * @brief Implements MBE audio encoding.
     */
    class HOST_SW_API MBEEncoder {
    public:
        /**
         * @brief Initializes a new instance of the MBEEncoder class.
         * @param mode Encoder mode.
         */
        MBEEncoder(MBE_ENCODER_MODE mode);

        /**
         * @brief Encodes the given MBE bits to deinterleaved MBE bits using the encoder mode.
         * @param[in] bits 
         * @param[out] codeword 
         */
        void encodeBits(uint8_t* bits, uint8_t* codeword);

        /**
         * @brief Encodes the given PCM samples using the encoder mode to MBE codewords.
         * @param[in] samples PCM samples (in short format)
         * @param[out] codeword MBE codewords.
         */
        void encode(int16_t* samples, uint8_t* codeword);

    private:
        imbe_vocoder m_vocoder;
        mbe_parms m_curMBEParms;
        mbe_parms m_prevMBEParms;

        MBE_ENCODER_MODE m_mbeMode;

    public:
        /**
         * @brief Gain adjustment.
         */
        __PROPERTY(float, gainAdjust, GainAdjust);
    };

    // Extern methods for C#/C++ interop
    extern "C" {
#ifdef _WIN32
        // Windows MBE Encoder Functions
        __declspec(dllexport) MBEEncoder* MBEEncoder_Create(MBE_ENCODER_MODE mode);
        __declspec(dllexport) void MBEEncoder_Encode(MBEEncoder* pEncoder, int16_t* samples, uint8_t* codeword);
        __declspec(dllexport) void MBEEncoder_EncodeBits(MBEEncoder* pEncoder, uint8_t* bits, uint8_t* codeword);
        __declspec(dllexport) void MBEEncoder_Delete(MBEEncoder* pEncoder);
#else
        MBEEncoder* MBEEncoder_Create(MBE_ENCODER_MODE mode);
        void MBEEncoder_Encode(MBEEncoder* pEncoder, int16_t* samples, uint8_t* codeword);
        void MBEEncoder_EncodeBits(MBEEncoder* pEncoder, uint8_t* bits, uint8_t* codeword);
        void MBEEncoder_Delete(MBEEncoder* pEncoder);
#endif
    }

} // namespace vocoder

#endif // __MBE_ENCODER_H__
