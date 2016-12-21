// =============================================================================
//
// Copyright (c) 2013-2015 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once
#include "BaseCodes.h"

class EscPosCommands
{
public:
    EscPosCommands();
    virtual ~EscPosCommands();

    virtual std::size_t setCharacterSet(BaseCodes::CharacterSet charSet);
    virtual std::size_t setCharacterCodePage(BaseCodes::CodePage codePage);
    virtual std::size_t setInvert(bool enable);
    virtual std::size_t setUnderline(BaseCodes::TextUnderline underline);
    virtual std::size_t setEmphasis(bool bEnable);
    virtual std::size_t setFont(BaseCodes::TextFont font);
    virtual std::size_t setColor(BaseCodes::TextColor color);
    virtual std::size_t setCharacterSize(BaseCodes::TextMagnification horizontal,
                                         BaseCodes::TextMagnification vertical);
    virtual std::size_t setCharacterSmoothing(bool enable);
    virtual std::size_t setAlign(byte align);
	virtual std::size_t setLineSpacing(byte n);
	virtual std::size_t setAbusoluteLeft(int nOrgx);

	virtual int queryStatus(byte n);

	virtual std::size_t initialize();
	virtual std::size_t openDrawer(byte nID,byte nOnTimes,byte nOffTimes);
	virtual std::size_t cutPaper(BaseCodes::PaperCut type,byte numDotsToFeed);
	virtual std::size_t printImage(int left,const byte* bmp,int width,int height,int threshold);
	virtual std::size_t printBarcode(const char* barcode,int left,int width,int height);

	virtual std::size_t writeBytes(const byte* buffer, std::size_t size){ return 0;};
};
