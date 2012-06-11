#ifndef NEF_DECODER_H
#define NEF_DECODER_H

#include "RawDecoder.h"
#include "LJpegPlain.h"
#include "TiffIFD.h"
#include "BitPumpPlain.h"
#include "TiffParser.h"
#include "NikonDecompressor.h"
/* 
    RawSpeed - RAW file decoder.

    Copyright (C) 2009 Klaus Post

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

    http://www.klauspost.com
*/

namespace RawSpeed {

class NefDecoder :
  public RawDecoder
{
public:
  NefDecoder(TiffIFD *rootIFD, FileMap* file);
  virtual ~NefDecoder(void);
  virtual RawImage decodeRawInternal();
  virtual void decodeMetaData(CameraMetaData *meta);
  virtual void checkSupport(CameraMetaData *meta);
  TiffIFD *mRootIFD;
private:
  bool D100IsCompressed(uint32 offset);
  void DecodeUncompressed();
  void DecodeD100Uncompressed();
  void readCoolpixMangledRaw(ByteStream &input, iPoint2D& size, iPoint2D& offset, int inputPitch);
  void readCoolpixSplitRaw(ByteStream &input, iPoint2D& size, iPoint2D& offset, int inputPitch);
  TiffIFD* FindBestImage(vector<TiffIFD*>* data);
};

class NefSlice {
public:
  NefSlice() { h = offset = count = 0;};
  ~NefSlice() {};
  uint32 h;
  uint32 offset;
  uint32 count;
};

} // namespace RawSpeed
#endif
// vim: shiftwidth=2 expandtab tabstop=2 cindent
// kate: tab-indents: off; indent-width 2; replace-tabs on; indent-mode cstyle; remove-trailing-space on;
